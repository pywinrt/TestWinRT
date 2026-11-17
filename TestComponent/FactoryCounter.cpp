#include "pch.h"
#include "FactoryCounter.h"
#include "FactoryCounter.g.cpp"
#include "CountedFactory.h"

namespace winrt::TestComponent::implementation
{
    uint32_t FactoryCounter::CountedFactoryCount()
    {
        return factory_implementation::CountedFactory::Count();
    }
}
