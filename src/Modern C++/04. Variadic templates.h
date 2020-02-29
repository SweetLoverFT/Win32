#pragma once

template <typename T, typename... Types>
void PrintTypeNumber(T firstArg, Types... args)
{
	std::cout << sizeof...(Types) << std::endl;
	std::cout << sizeof...(args) << std::endl;
}

// The final calling function for PrintAll(T, Types...)
template <typename T>
void PrintAll(T arg)
{
	std::cout << arg << std::endl;
}

template <typename T>
void PrintDatas(T t)
{
	std::cout << t << " ";
}

template <typename T, typename... Types>
void PrintAll(T firstArg, Types... args)
{
	std::cout << firstArg << " ";
	// Line 32 can't run because of compile-time decision
	// if (sizeof...(args) > 0)
	if constexpr (sizeof...(args) > 0)		// C++ 17
		PrintAll(args...);
}

template <typename... Types>
void PrintDatas(Types... args)
{
	// ... is a kind of operator which is used to expand the expression
	// It's the same as (PrintAllData(args1), 0), (PrintAllData(args2), 0)...
	int arr[] = { (PrintDatas(args), 0)... };
}
