// Notice: To enable unsupported features in Visual Studio, you should install component Clang/C2
#include <stdio.h>
// Feature #3: New library functions, data types and headers: "__int64", "_Bool" and "complex"
#include <stdbool.h>
#include <complex.h>
// #include <malloc.h>
// Feature #9: Macro with variable number of parameters
#include <stdarg.h>

double Sum(int n, ...)
{
	double sum = 0.0;
	va_list argptr;
	va_start(argptr, n); // Initialize argptr
	for (int i = 0; i < n; ++i)
		sum += va_arg(argptr, double);
	va_end(argptr);
	return sum;
}
#define MyPrintf(fmt, ...)  printf(fmt, __VA_ARGS__)  

// Feature #1: __inline
// Feature #10: The keyword "restrict" isn't supported by "cl.exe" in C99
__inline void Swap(int*/* restrict*/ pSrc, int*/* restrict*/ pDest)
{
	int tmp = *pSrc;
	*pSrc = *pDest;
	*pDest = tmp;
}

typedef struct Node
{
	int val;
	// Feature #5: Flexible array member used as a placeholder but not supported by cl.exe
	struct Node *p[];
}Node;

int main()
{
	// Here "bool" is a macro replaced by the keyword "_Bool", please refer to <stdbool.h>
	bool a = true;
	printf("a = %d\n", a);

	__int64 b = 2147483649;

	printf("__STDC_HOSTED__ = %d", __STDC_HOSTED__);
//	#if __STDC_VERSION__> = 199901L		// The built-in macro "__STDC_VERSION__" isn't supported by "cl.exe"
	// The keyword "_Fcomplex" is only used by Microsoft compiler
	_Fcomplex f = { 1.0f, 2.0f };
	_Dcomplex d = { f._Val[0], f._Val[1] };
	double real = creal(d);		// Can't use "(_Dcomplex)f" to cast a float complex to a double complex
	printf("The real part in _Dcomplex d is: %lf\n", real);
/*
	// cl.exe doesn't support feature #4: Variable-length array
	int row = 3, column = 2;
	int data[row][column];
*/
	// Feature #7: Specified initializer
	int count[] = { 0, [5] = 7, 9, 10 };

	printf("sizeof(count) = %d, count[] is:", (int)sizeof(count));
	for (int i = 0; i < sizeof(count) / sizeof(int); ++i)
		printf(" %d", count[i]);
	printf("\n");

/*
	// cl.exe doesn't support feature #5: Flexible array member
	// sizeof(Node) = sizeof(int) because the member "p" is just a placeholder
	// that pointed to the assigned address at runtime [WHEN THIS FEATURE IS SUPPORTED]
	Node* pNode = (Node*)malloc(sizeof(Node) + sizeof(Node) * 5);
	pNode->val = 0;
	for (int i = 0; i < 5; ++i)
		pNode->p[i]->val = i;
	printf("sizeof(Node) = %d, p->val = %d\n", sizeof(Node), pNode->val);
	printf("p contains:");
	for (int i = 0; i < 5; ++i)
		printf(" each p[%d]->val = %d", i, pNode->p[i]->val);
	printf("\n");
	free(pNode);
	pNode = NULL;
*/

	// Feature #8: Compound structure
	// Feature #11: A universal character name
	double *浮点数 = (double[]) { 1.1, 2.2, 3.3 };
	printf("浮点数 =");
	for (int i = 0; i < 3; ++i)
		printf(" %.2lf", 浮点数[i]);
	printf("\n");

	// Feature #9: Macro with variable number of parameters
	MyPrintf("Sum(5, ...) = %.2lf\n", Sum(5, 1.0, 2.0, 3.0, 4.0, 5.0));

	return 0;
}
