#include "pch.h"
#include "ProtectedMembers.h"
#include "ProtectedMembers.g.cpp"

namespace winrt::TestComponent::implementation
{
    ProtectedMembers::ProtectedMembers(int32_t initial) : m_value(initial)
    {
    }

    int32_t ProtectedMembers::ProtectedValue()
    {
        return m_value;
    }

    void ProtectedMembers::ProtectedValue(int32_t value)
    {
        m_value = value;
    }

    int32_t ProtectedMembers::ProtectedMethod()
    {
        return m_value;
    }

    int32_t ProtectedMembers::OverridableValue()
    {
        return m_value;
    }

    int32_t ProtectedMembers::ReadOverridableValue()
    {
        return overridable().OverridableValue();
    }
}
