#include "stdafx.h"

#define TEST_CASE(fun) \
	std::cout << #fun " begins:" << std::endl; \
	fun(); \
	std::cout << #fun " ends:" << std::endl << std::endl

int main()
{
	TEST_CASE(Case01);
	TEST_CASE(Case02);
	TEST_CASE(Case03);
	TEST_CASE(Case04);
    TEST_CASE(Case05);
    TEST_CASE(Case06);
    TEST_CASE(Case07);

	return EXIT_SUCCESS;
}
