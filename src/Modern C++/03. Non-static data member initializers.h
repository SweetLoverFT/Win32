#pragma once

/**
 * Please refer to the following links:
 *     1. https://blog.csdn.net/qq_25327609/article/details/89373967
 *     2. https://stackoverflow.com/questions/34878803/c-non-static-data-member-initializers-just-a-little-bit-confused
 * Beware the differences between Non-static data member initializers and constructor initializers
 */

class InitializerTest
{
public:
	InitializerTest() : _a(10) { std::cout << "a = " << _a << std::endl; }
	InitializerTest(int a) : _a(a) { std::cout << "a = " << _a << std::endl; }
	InitializerTest(const InitializerTest& obj) { std::cout << "a = " << _a << std::endl; }
private:
	int _a{ 5 };
	// Don't use the following syntax:
	// T a(5);		// Will call the copy constructor
	// T a = 5;		// Will alsoe call the copy constructor as above when there's a constructor
					// with only 1 parameter in T without keyword "explicit"
};
