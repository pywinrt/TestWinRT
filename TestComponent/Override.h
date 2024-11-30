#pragma once
#include "Override.g.h"

using namespace winrt;
using namespace Windows::Foundation;

namespace winrt::TestComponent::implementation
{
    struct Override : OverrideT<Override>
    {
    private:
        event<EventHandler<IInspectable>> m_protected_called_event;
        event<EventHandler<IInspectable>> m_overridable_called_event;

    public:
        Override() = default;

        void CallProtected();
        void OnProtected();
        event_token ProtectedCalled(EventHandler<IInspectable> const& handler);
        void ProtectedCalled(event_token token) noexcept;

        void CallOverridable();
        virtual void OnOverridable();
        event_token OverridableCalled(EventHandler<IInspectable> const& handler);
        void OverridableCalled(event_token token) noexcept;
    };
}

namespace winrt::TestComponent::factory_implementation
{
    struct Override : OverrideT<Override, implementation::Override>
    {
    };
}
