#include "pch.h"
#include "Override.h"
#include "Override.g.cpp"

using namespace winrt;
using namespace Windows::Foundation;

namespace winrt::TestComponent::implementation
{
    void Override::CallProtected()
    {
        OnProtected();
    }

    void Override::OnProtected()
    {
        m_protected_called_event(*this, nullptr);
    }

    event_token Override::ProtectedCalled(EventHandler<IInspectable> const& handler)
    {
        return m_protected_called_event.add(handler);
    }

    void Override::ProtectedCalled(event_token token) noexcept
    {
        m_protected_called_event.remove(token);
    }

    void Override::CallOverridable()
    {
		overridable().OnOverridable();
    }

    void Override::OnOverridable()
    {
        m_overridable_called_event(*this, nullptr);
    }

    event_token Override::OverridableCalled(EventHandler<IInspectable> const& handler)
    {
        return m_overridable_called_event.add(handler);
    }

    void Override::OverridableCalled(event_token token) noexcept
    {
        m_overridable_called_event.remove(token);
    }
}
