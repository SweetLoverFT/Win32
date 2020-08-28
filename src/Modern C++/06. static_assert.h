#pragma once

#define TEST_STATIC_ASSERT 1

// This operation is only available for integers
template <typename T>
void LimitedSwap(T &a, T &b)
{
    // Usually, static_assert is used at compilation time,
    // but it can be used before runtime for template
    static_assert(std::is_same<T, int>::value, "T must be integer");
    T tmp = a;
    a = b;
    b = tmp;
}
