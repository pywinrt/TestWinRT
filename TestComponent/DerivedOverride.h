#pragma once
#include "DerivedOverride.g.h"
#include "Override.h"

using namespace winrt;
using namespace Windows::Foundation;

namespace winrt::TestComponent::implementation
{
    struct DerivedOverride : DerivedOverrideT<DerivedOverride, TestComponent::implementation::Override>
    {
    private:
        event<EventHandler<IInspectable>> m_derived_overridable_called_event;

    public:
        DerivedOverride() = default;

        void CallDerivedOverridable();
        virtual void OnDerivedOverridable();
        event_token DerivedOverridableCalled(EventHandler<IInspectable> const& handler);
        void DerivedOverridableCalled(event_token token) noexcept;
    };
}

namespace winrt::TestComponent::factory_implementation
{
    struct DerivedOverride : DerivedOverrideT<DerivedOverride, implementation::DerivedOverride>
    {
    };
}
