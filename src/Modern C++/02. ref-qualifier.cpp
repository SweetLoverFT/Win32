#include "stdafx.h"
#include "02. ref-qualifier.h"

void AClass::f() & { std::cout << "f() &" << std::endl; }

void AClass::f() && { std::cout << "f() &&" << std::endl; }

void Case02()
{
	AClass aClass;
	aClass.f();
	AClass().f();
}
