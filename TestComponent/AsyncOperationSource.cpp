#include "pch.h"
#include "AsyncOperationSource.h"
#include "AsyncOperationSource.g.cpp"

namespace winrt::TestComponent::implementation
{
    void AsyncOperationSource::Complete(int32_t result)
    {
        finish(Windows::Foundation::AsyncStatus::Completed, {}, result);
    }
}
