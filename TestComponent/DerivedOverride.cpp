#include "pch.h"
#include "DerivedOverride.h"
#include "DerivedOverride.g.cpp"

using namespace winrt;
using namespace Windows::Foundation;

namespace winrt::TestComponent::implementation
{
    void DerivedOverride::CallDerivedOverridable()
    {
        overridable().OnDerivedOverridable();
    }

    void DerivedOverride::OnDerivedOverridable()
    {
        m_derived_overridable_called_event(*this, nullptr);
    }

    event_token DerivedOverride::DerivedOverridableCalled(EventHandler<IInspectable> const& handler)
    {
        return m_derived_overridable_called_event.add(handler);
    }

    void DerivedOverride::DerivedOverridableCalled(event_token token) noexcept
    {
        m_derived_overridable_called_event.remove(token);
    }
}
