#pragma once
#include "AsyncActionSource.g.h"
#include "ControlledAsync.h"

namespace winrt::TestComponent::implementation
{
    struct AsyncActionSource : AsyncActionSourceT<AsyncActionSource>,
        controlled_async_source<Windows::Foundation::IAsyncAction, Windows::Foundation::AsyncActionCompletedHandler>
    {
        AsyncActionSource() = default;

        void Complete();
    };
}

namespace winrt::TestComponent::factory_implementation
{
    struct AsyncActionSource : AsyncActionSourceT<AsyncActionSource, implementation::AsyncActionSource>
    {
    };
}
