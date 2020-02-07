#include "stdafx.h"
#include "01. Rvalue reference.h"

int CValue::singleCounter = 0;
int CValue::copyCounter = 0;
int CValue::moveCounter = 0;
int CValue::assignCounter = 0;

static CValue fun1(CValue val)
{
	return val;
}

static CValue& fun2(CValue& val)
{
	return val;
}

void Case01()
{
	CValue a(10);
	CValue::PrintStatus();

	CValue b(a);
	CValue::PrintStatus();

	CValue c = a;
	CValue::PrintStatus();

	CValue d(20);
	CValue::PrintStatus();
	d = c;
	CValue::PrintStatus();

	CValue e = fun1(a);
	CValue::PrintStatus();
	fun1(a);
	CValue::PrintStatus();

	CValue f = fun2(a);
	CValue::PrintStatus();

	CValue g(std::move(f));
	CValue::PrintStatus();
}
