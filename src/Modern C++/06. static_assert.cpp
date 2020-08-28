#include "stdafx.h"
#include "06. static_assert.h"

void Case06()
{
    static_assert(TEST_STATIC_ASSERT == 1, "TEST_STATIC_ASSERT should be 1");
    int a = 3, b = 4;
    LimitedSwap(a, b);
    // double x = 6.0, y = 7.0;
    // LimitedSwap(x, y);
}
