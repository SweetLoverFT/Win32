#include "stdafx.h"
#include "04. Variadic templates.h"

void Case04()
{
	PrintAll(1);
	PrintTypeNumber(0, 'a', "Hello, world!", 5.8);
	PrintAll(0, 'a', "Hello, world!", 5.8);
	PrintDatas(0, 'a', "Hello, world!", 5.8);
}
