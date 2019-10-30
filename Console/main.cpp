﻿#include "pch.h"

using namespace winrt;
using namespace TestComponent;

int main()
{
    try
    {
        init_apartment();
        TestRunner::TestSelf();
        puts("Test passed!");
    }
    catch (hresult_error const& e)
    {
        printf("Test failed: %ls\n", e.message().c_str());
    }
}