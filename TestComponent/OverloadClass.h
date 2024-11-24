#pragma once
#include "OverloadClass.g.h"

namespace winrt::TestComponent::implementation
{
    struct OverloadClass : OverloadClassT<OverloadClass>
    {
        OverloadClass() = default;

        void Overload();
        void Overload(int a);
        void Overload(int a, int b);
        void Overload(int a, int b, int c);
    };
}
namespace winrt::TestComponent::factory_implementation
{
    struct OverloadClass : OverloadClassT<OverloadClass, implementation::OverloadClass>
    {
    };
}
