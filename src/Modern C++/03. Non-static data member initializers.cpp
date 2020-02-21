#include "stdafx.h"
#include "03. Non-static data member initializers.h"

void Case03()
{
	InitializerTest test1, test2(7), test3(test1);
}
