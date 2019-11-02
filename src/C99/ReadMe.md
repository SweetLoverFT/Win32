# C99

Introduce the new language features, we use Microsoft compiler **"cl.exe"** to confirm it, you can refer to **[this link](https://blog.csdn.net/lengye7/article/details/80255833)** in **Chinese** and **[this link](https://www.xuebuyuan.com/622362.html)** about library functions. I'll save this 2 pages, so you can refer to the following items:
1. **[Library functions](doc\Library-functions.docx)**
2. **[Changes in C99](doc\Changes-in-C99.docx)** in **Chinese**

## Features list

1. **Inline function:** The keyword is **"__inline"**
2. **Mixed declarations and code:** It's allowed to declare a variable after declaration section when this variable is a static variable or assigned an initial value.
3. **New library functions, data types and headers:** These keywords are **"__int64"**, **"_Bool"** and **_Dcomplex**, the related functions are in header files, such as **&lt;complex.h&gt;**, **&lt;fenv.h&gt;**, **&lt;inttypes.h&gt;**, **&lt;stdbool.h&gt;**, **&lt;stdint.h&gt;** and **&lt;tgmath.h&gt;**. **&lt;tgmath.h&gt;** defines type-generic mathematical functions that will choose functions by different data type from incoming parameters, so this is one kind of generic programming, and **&lt;fenv.h&gt;** is used to handle floating point data with improvement.
4. **Variable-length array:** Although subsequently downgraded to conditional features in C11 without implementation
5. **Flexible array member:** A variable-length array member in a structure
6. **Support for single-line comments starting with "//":** Such as BCPL, C++, and Java
7. **Specified initializer:** Like **"int count[] = { 0, [5] = 7, 9, 10 };"**
8. **Compound structure:** Like **"double *fp = (double[]) {1.1, 2.2, 3.3};"** and call function by **"func((struct Rectangle){ 0, 0, 1920, 1080 };"**
9. **Macro with variable number of parameters:** Use built-in macro and **"..."** 
10. **The keyword "restrict" allows for more aggressive code optimization, eliminating FORTRAN's previous compile-time array access advantages reserved in ANSI C:**" E.g, _Src and _Dst can be accessed at compile-time, so author of standard library will enable to check if they are the same by **"void *memcpy(void *restrict _Src, const void *restrict _Dst, size_t _Size);"**, and the keyword **"restrict"** also leads to a limitation that only pointers can access addresses
11. **A universal character name:** Allows user variables to contain characters other than the standard character set
12. **The keyword "static" used in an array as an incoming parameter:** It means that this array will perform as a variable length array that contains declared number of elements **at least**