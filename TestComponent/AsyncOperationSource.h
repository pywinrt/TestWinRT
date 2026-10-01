#pragma once
#include "AsyncOperationSource.g.h"
#include "ControlledAsync.h"

namespace winrt::TestComponent::implementation
{
    struct AsyncOperationSource : AsyncOperationSourceT<AsyncOperationSource>,
        controlled_async_source<Windows::Foundation::IAsyncOperation<int32_t>, Windows::Foundation::AsyncOperationCompletedHandler<int32_t>>
    {
        AsyncOperationSource() = default;

        void Complete(int32_t result);
    };
}

namespace winrt::TestComponent::factory_implementation
{
    struct AsyncOperationSource : AsyncOperationSourceT<AsyncOperationSource, implementation::AsyncOperationSource>
    {
    };
}
