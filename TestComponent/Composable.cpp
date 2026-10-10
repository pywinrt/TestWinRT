#include "pch.h"
#include "Composable.h"
#include "Composable.g.cpp"

namespace winrt::TestComponent::implementation
{
    Composable::Composable(int32_t init) :
        m_value(init)
    {
    }

    int32_t Composable::Value()
    {
        return m_value;
    }

    void Composable::Value(int32_t value)
    {
        m_value = value;
    }

    int32_t Composable::One()
    {
        return 1;
    }

    int32_t Composable::Two()
    {
        return 2;
    }

    int32_t Composable::Three()
    {
        return 3;
    }

    int32_t Composable::Four()
    {
        return 4;
    }

    int32_t Composable::ExpectComposable(TestComponent::Composable const& t)
    {
        return not_null(t, L"t").Value();
    }

    int32_t Composable::ExpectRequiredOne(TestComponent::IRequiredOne const& t)
    {
        return not_null(t, L"t").One();
    }

    int32_t Composable::ExpectRequiredTwo(TestComponent::IRequiredTwo const& t)
    {
        return not_null(t, L"t").Two();
    }

    int32_t Composable::ExpectRequiredThree(TestComponent::IRequiredThree const& t)
    {
        return not_null(t, L"t").Three();
    }

    int32_t Composable::ExpectRequiredFour(TestComponent::IRequiredFour const& t)
    {
        return not_null(t, L"t").Four();
    }
}
