#pragma once

#include <memory>
#include <type_traits>

// An async operation that finishes only when its source says so, and the
// source that says so. AsyncActionSource and AsyncOperationSource are the two
// instances of it that TestComponent exposes.

namespace winrt::TestComponent::implementation
{
    // What an operation and its source both read and write.
    struct controlled_async_state
    {
        slim_mutex lock;
        Windows::Foundation::AsyncStatus status{ Windows::Foundation::AsyncStatus::Started };
        hresult error{};
        int32_t result{};
        uint32_t cancel_requests{};
        bool defers_handler{};
        bool handler_released{};
    };

    // An IAsyncAction or IAsyncOperation<Int32> that keeps its completed
    // handler for as long as it exists, as C++/WinRT's coroutines do.
    template <typename Async, typename Handler>
    struct controlled_async : implements<controlled_async<Async, Handler>, Async, Windows::Foundation::IAsyncInfo>
    {
        explicit controlled_async(std::shared_ptr<controlled_async_state> state) :
            m_state(std::move(state))
        {
        }

        uint32_t Id() const noexcept
        {
            return 1;
        }

        Windows::Foundation::AsyncStatus Status()
        {
            slim_lock_guard const guard{ m_state->lock };
            return m_state->status;
        }

        hresult ErrorCode()
        {
            slim_lock_guard const guard{ m_state->lock };

            switch (m_state->status)
            {
            case Windows::Foundation::AsyncStatus::Error:
                return m_state->error;
            case Windows::Foundation::AsyncStatus::Canceled:
                return impl::error_canceled;
            default:
                return {};
            }
        }

        // A request, which the operation answers when its source finishes it.
        void Cancel()
        {
            slim_lock_guard const guard{ m_state->lock };
            m_state->cancel_requests++;
        }

        void Close()
        {
            slim_lock_guard const guard{ m_state->lock };

            if (m_state->status == Windows::Foundation::AsyncStatus::Started)
            {
                throw hresult_illegal_state_change();
            }
        }

        void Completed(Handler const& handler)
        {
            {
                slim_lock_guard const guard{ m_state->lock };

                if (m_completed)
                {
                    throw hresult_illegal_delegate_assignment();
                }

                m_completed = handler;
            }

            // An operation that has already finished calls its handler at once.
            invoke_completed();
        }

        Handler Completed()
        {
            slim_lock_guard const guard{ m_state->lock };
            return m_completed;
        }

        auto GetResults()
        {
            slim_lock_guard const guard{ m_state->lock };

            switch (m_state->status)
            {
            case Windows::Foundation::AsyncStatus::Error:
                throw hresult_error(m_state->error);
            case Windows::Foundation::AsyncStatus::Canceled:
                throw hresult_canceled();
            case Windows::Foundation::AsyncStatus::Started:
                throw hresult_illegal_method_call();
            default:
                break;
            }

            if constexpr (!std::is_same_v<Async, Windows::Foundation::IAsyncAction>)
            {
                return m_state->result;
            }
        }

        bool has_completed_handler()
        {
            slim_lock_guard const guard{ m_state->lock };
            return static_cast<bool>(m_completed);
        }

        // Calls the completed handler once the operation has finished, it has
        // a handler and the source is not holding the call back, and only once.
        void invoke_completed()
        {
            Handler handler;
            Windows::Foundation::AsyncStatus status{};

            {
                slim_lock_guard const guard{ m_state->lock };

                if (m_invoked || !m_completed)
                {
                    return;
                }

                if (m_state->status == Windows::Foundation::AsyncStatus::Started)
                {
                    return;
                }

                if (m_state->defers_handler && !m_state->handler_released)
                {
                    return;
                }

                m_invoked = true;
                handler = m_completed;
                status = m_state->status;
            }

            handler(*this, status);
        }

    private:
        std::shared_ptr<controlled_async_state> m_state;
        Handler m_completed;
        bool m_invoked{};
    };

    // The members AsyncActionSource and AsyncOperationSource share. The source
    // holds the operation only weakly, so that a test can see when the
    // consumer has let go of it.
    template <typename Async, typename Handler>
    struct controlled_async_source
    {
        using operation_type = controlled_async<Async, Handler>;

        Async Operation()
        {
            slim_lock_guard const guard{ m_lock };

            if (auto operation = m_operation.get())
            {
                return operation.template as<Async>();
            }

            if (m_made)
            {
                throw hresult_illegal_method_call(L"the operation has been released");
            }

            auto operation = make_self<operation_type>(m_state);
            m_operation = operation->get_weak();
            m_made = true;

            return operation.template as<Async>();
        }

        bool IsOperationAlive()
        {
            return static_cast<bool>(m_operation.get());
        }

        uint32_t CancelRequestCount()
        {
            slim_lock_guard const guard{ m_state->lock };
            return m_state->cancel_requests;
        }

        bool HasCompletedHandler()
        {
            auto operation = m_operation.get();
            return operation && operation->has_completed_handler();
        }

        bool DefersCompletedHandler()
        {
            slim_lock_guard const guard{ m_state->lock };
            return m_state->defers_handler;
        }

        void DefersCompletedHandler(bool value)
        {
            slim_lock_guard const guard{ m_state->lock };
            m_state->defers_handler = value;
        }

        void Fail(int32_t error)
        {
            finish(Windows::Foundation::AsyncStatus::Error, hresult(error), 0);
        }

        void Cancel()
        {
            finish(Windows::Foundation::AsyncStatus::Canceled, {}, 0);
        }

        void InvokeCompletedHandler()
        {
            {
                slim_lock_guard const guard{ m_state->lock };
                m_state->handler_released = true;
            }

            if (auto operation = m_operation.get())
            {
                operation->invoke_completed();
            }
        }

    protected:
        void finish(Windows::Foundation::AsyncStatus status, hresult error, int32_t result)
        {
            {
                slim_lock_guard const guard{ m_state->lock };

                if (m_state->status != Windows::Foundation::AsyncStatus::Started)
                {
                    throw hresult_illegal_state_change();
                }

                m_state->status = status;
                m_state->error = error;
                m_state->result = result;
            }

            if (auto operation = m_operation.get())
            {
                operation->invoke_completed();
            }
        }

    private:
        slim_mutex m_lock;
        std::shared_ptr<controlled_async_state> m_state{ std::make_shared<controlled_async_state>() };
        weak_ref<operation_type> m_operation;
        bool m_made{};
    };
}
