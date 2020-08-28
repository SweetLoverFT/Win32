#include "stdafx.h"
#include "07. auto.h"
#include <vector>

void Case07()
{
    auto answer = AutoAdd(3, 6.6);
    std::cout << typeid(answer).name() << std::endl;
    auto result = AutoAdd(3, 4);
    std::cout << typeid(result).name() << std::endl;
    // We can't use auto to deduce the type of arrays
    // auto arr[] = { 1, 2, .3 };
    // But we can use it as an iterator to traverse arrays as below
    double arr[] = { 1, 2, .3 };
    for (auto &&i : arr)
        std::cout << i << " ";
    std::cout << std::endl;
    // Beware of the container combined with bool type
    std::vector<bool> v;
    v.push_back(false);
    auto val = v[0];
    std::cout << typeid(val).name() << std::endl;
    // "auto" also can be regarded as "decltype(auto)", let me explain it below
    int i = 0;
    auto a = i;
    decltype(auto) b = i;
    std::cout << typeid(a).name() << std::endl;
    std::cout << typeid(b).name() << std::endl;
}
