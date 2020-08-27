#include "stdafx.h"
#include "05. Initializer lists.h"
#include <vector>

void Case05()
{
    // In fact, this statement is: std::vector<int> vec = initialize_list<int>{ 1, 2, 3, 4, 5 };
    std::vector<int> vec{ 1, 2, 3, 4, 5 };
    for (auto const &i : vec)
        std::cout << i << " ";
    std::cout << std::endl;
}
