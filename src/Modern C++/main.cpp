#include "stdafx.h"

#define TEST_CASE(fun) \
	std::cout << #fun " begins:" << std::endl; \
	fun(); \
	std::cout << #fun " ends:" << std::endl << std::endl

int main()
{
	TEST_CASE(Case01);
	TEST_CASE(Case02);

	return EXIT_SUCCESS;
}
