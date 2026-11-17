#pragma once
#include "CountedFactory.g.h"

namespace winrt::TestComponent::implementation
{
    struct CountedFactory : CountedFactoryT<CountedFactory>
    {
        CountedFactory() = default;

        static void StaticMethod();
    };
}

namespace winrt::TestComponent::factory_implementation
{
    struct CountedFactory : CountedFactoryT<CountedFactory, implementation::CountedFactory>
    {
        CountedFactory() noexcept;
        ~CountedFactory();

        // How many of these exist.
        static uint32_t Count() noexcept;
    };
}
