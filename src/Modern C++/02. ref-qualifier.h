#pragma once

/**
 * Please refer to this link: https://www.jianshu.com/p/5da58ce48f92
 * ref-qualifier is used for member functions in a class for L-value & R-value callers
 */

class AClass
{
public:
	// Can be invoked by L-value
	void f() & ;
	// Can be invoked by R-value
	void f() && ;
};
