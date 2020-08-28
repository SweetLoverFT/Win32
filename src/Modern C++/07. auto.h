#pragma once

/* In C++ 11, we have to define the template like this:
template <class T, class U>
auto AutoAdd(const T &t, const U &u) -> decltype(t + u)
{
    return t + u;
}
 * However, from C++ 14, we can simply define it as below
 */


template <class T, class U>
auto AutoAdd(const T &t, const U &u)
{
    return t + u;
}
