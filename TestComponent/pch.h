#pragma once
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/TestComponent.h>
#include <Windows.h>

// Refuses a null that is about to be used, as Windows' own components do: with
// E_POINTER, naming what was null.
template <typename T>
T not_null(T const& value, wchar_t const* name)
{
    if (!value)
    {
        throw winrt::hresult_error(E_POINTER, name);
    }

    return value;
}
