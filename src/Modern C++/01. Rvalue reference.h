#pragma once

/**
 * Please refer to the following links:
 *     1. https://zhuanlan.zhihu.com/p/85668787
 *     2. https://www.jianshu.com/p/31cea1b6ee24
 *     3. https://blog.csdn.net/erice_s/article/details/90745784
 * Reasons to use Rvalue reference:
 *     1. To use temporary symbols for reading and writing.
 *     2. Improve the efficiency by reducing unnecessary coping while calling copy
 *        constructor for the incoming massive objects
 * What are left values and right values?
 *     1. Left values own names and we can get the addresses from them
 *     2. Right values are expiring values and pure right values, they can be
 *        literal constants and anonymous temporary objects like "5.3" and "a + b"
 */

class CValue
{
public:
	CValue(int index) : _index(index)
	{
		++singleCounter;
		std::cout << "Call constructor: CValue(int index)" << std::endl;
	}
	CValue(const CValue& val)
	{
		++copyCounter;
		std::cout << "Call constructor: CValue(const CValue& val)" << std::endl;
	}
	CValue(const CValue&& val)
	{
		++moveCounter;
		std::cout << "Warning: val is invalid when out of the scope" << std::endl
			<< "Call constructor: CValue(const CValue&& val)" << std::endl;
	}
	CValue& operator =(const CValue& val)
	{
		++assignCounter;
		_index = val._index;
		std::cout << "Call assign operator: CValue& operator =(const CValue& val)" << std::endl;
		return *this;
	}
private:
	int _index;
public:
	static void PrintStatus()
	{
		std::cout << "singleCounter = " << singleCounter << std::endl
			<< "copyCounter = " << copyCounter << std::endl
			<< "moveCounter = " << moveCounter << std::endl
			<< "assignCounter = " << assignCounter << std::endl;
	}
public:
	static int singleCounter;
	static int copyCounter;
	static int moveCounter;
	static int assignCounter;
};
