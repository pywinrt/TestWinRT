#pragma once
#include "FactoryCounter.g.h"

namespace winrt::TestComponent::implementation
{
    struct FactoryCounter
    {
        FactoryCounter() = default;

        static uint32_t CountedFactoryCount();
    };
}

namespace winrt::TestComponent::factory_implementation
{
    struct FactoryCounter : FactoryCounterT<FactoryCounter, implementation::FactoryCounter>
    {
    };
}
