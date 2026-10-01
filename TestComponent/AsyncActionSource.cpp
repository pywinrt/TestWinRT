#include "pch.h"
#include "AsyncActionSource.h"
#include "AsyncActionSource.g.cpp"

namespace winrt::TestComponent::implementation
{
    void AsyncActionSource::Complete()
    {
        finish(Windows::Foundation::AsyncStatus::Completed, {}, 0);
    }
}
