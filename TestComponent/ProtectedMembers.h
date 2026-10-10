#pragma once
#include "ProtectedMembers.g.h"

namespace winrt::TestComponent::implementation
{
    struct ProtectedMembers : ProtectedMembersT<ProtectedMembers>
    {
    private:
        int32_t m_value{};

    public:
        ProtectedMembers() = default;
        ProtectedMembers(int32_t initial);

        int32_t ProtectedValue();
        void ProtectedValue(int32_t value);
        int32_t ProtectedMethod();

        virtual int32_t OverridableValue();
        int32_t ReadOverridableValue();
    };
}

namespace winrt::TestComponent::factory_implementation
{
    struct ProtectedMembers : ProtectedMembersT<ProtectedMembers, implementation::ProtectedMembers>
    {
    };
}
