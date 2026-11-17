#include "pch.h"
#include "CountedFactory.h"
#include "CountedFactory.g.cpp"

#include <atomic>

namespace winrt::TestComponent::implementation
{
    void CountedFactory::StaticMethod()
    {
    }
}

namespace winrt::TestComponent::factory_implementation
{
    // Factories are made and released on whatever thread asks for them.
    static std::atomic<uint32_t> s_count;

    CountedFactory::CountedFactory() noexcept
    {
        ++s_count;
    }

    CountedFactory::~CountedFactory()
    {
        --s_count;
    }

    uint32_t CountedFactory::Count() noexcept
    {
        return s_count;
    }
}
