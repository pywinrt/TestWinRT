#pragma once
#include "TestRunner.g.h"

namespace winrt::TestComponent::implementation
{
    struct TestRunner
    {
        TestRunner() = default;

        static void TestProducer(ITests const& callee);
        static uint32_t TestConsumer(TestHandler const& caller);
        static void TestSelf();
        static ITests MakeTests();
        static Windows::Foundation::Collections::IVector<int32_t> CreateInt32Vector();
        static Windows::Foundation::Collections::IVector<hstring> CreateStringVector();
        static Windows::Foundation::Collections::IVector<Windows::Foundation::IStringable> CreateStringableVector();
        static Windows::Foundation::TimeSpan CreateTimeSpan(uint32_t milliseconds);
        static Windows::Foundation::IAsyncAction CreateAsyncAction(uint32_t milliseconds);
        static Windows::Foundation::IAsyncAction CreateAsyncActionWithError(uint32_t milliseconds, int32_t error);
        static Windows::Foundation::IAsyncOperation<int32_t> CreateAsyncOperation(uint32_t milliseconds, int32_t result);
        static Windows::Foundation::IAsyncOperation<int32_t> CreateAsyncOperationWithError(uint32_t milliseconds, int32_t error, int32_t result);
        static Windows::Foundation::IAsyncActionWithProgress<int32_t> CreateAsyncActionWithProgress(uint32_t milliseconds, Windows::Foundation::Collections::IVectorView<int32_t> const items) ;
        static Windows::Foundation::IAsyncActionWithProgress<int32_t> CreateAsyncActionWithProgressWithError(uint32_t milliseconds, Windows::Foundation::Collections::IVectorView<int32_t> const items, int32_t error);
        static Windows::Foundation::IAsyncOperationWithProgress<int32_t, int32_t> CreateAsyncOperationWithProgress(uint32_t milliseconds, Windows::Foundation::Collections::IVectorView<int32_t> const items, int32_t result);
        static Windows::Foundation::IAsyncOperationWithProgress<int32_t, int32_t> CreateAsyncOperationWithProgressWithError(uint32_t milliseconds, Windows::Foundation::Collections::IVectorView<int32_t> const items, int32_t error, int32_t result);
        static hstring ExpectObject(Windows::Foundation::IInspectable const& value);
    };
}

namespace winrt::TestComponent::factory_implementation
{
    struct TestRunner : TestRunnerT<TestRunner, implementation::TestRunner>
    {
    };
}
