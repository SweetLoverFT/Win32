# C11

Introduce the new language features, we use Microsoft compiler **"cl.exe"** to confirm it, you can refer to **[this link](https://blog.csdn.net/u012611878/article/details/79090793)** in **Chinese**. I'll save this page, so you can refer to the following items:
1. **[Changes in C11](doc\Changes-in-C11.docx)** in **Chinese**
2. **[Welcome-to-Pelles-C.chm](doc\Welcome-to-Pelles-C.chm)**
**Notice:** You can check "unlock" in the property of the "*.chm" file to see the content, please refer to **[this documentation](doc\How-to-unlock-dot-chm-file.docx)** if you still don't know how to deal with it

## Features list

1. Operator **"alignof"** is used to process alignment, please refer to **section 7.15** about function **aligned_alloc()** in header file **&lt;stdalign.h&gt;**
2. Mark **"_Noreturn"** is similar to **"__attribute__((noreturn))"** in gcc for functions. E.g, **_Noreturn void thrd_exit(int res);**
3. Keyword **"_Generic"** is similar to **"typeof"** in gcc
4. Static assertions are processed after **#if** and **#error** are interpreted. E.g, **"_Static_assert(FOO > 0, "FOO has a wrong value");"**
5. The function **"gets()"** is deprecated, please use function **"gets_s()"** instead
6. New mode for function **"fopen()"** like **"...x"**, it's similar to **"O_CREAT | O_EXCL"** in **POSIX** and usually used in file locks
7. **Anonymous struct/union** is already in gcc, please refer to **section 6.7.2.1** at page 13
8. **Supports for multi-threads**, such as **"_Thread_local"** for local thread, **thrd_create()**, **thrd_exit()** and mutex like **"mtx_lock()"** and **"mtx_unlock()**", etc for thread creation and management functions, please refer to **section 7.26**
9. **"_Atomic"** type modifier in header file **&lt;stdatomic.h&gt;**, please refer to **section 7.17**
10. New **safe** functions that make **"Bounds-checking"**, such as **"fopen_s()"**, **"strcat_s()"**, etc. Please refer to **Annex K**
11. **Improved Unicode support**, e.g, new header file **&lt;uchar.h&gt;**, etc.
12. Add function **"quick_exit()"** as the optional way to terminate the program with minimal cleanup when exit() fails, please refer to **section 7.22.4.7**
13. Add macro **"CMPLX()"** to create complex, please refer to **section 7.3.9.3**
14. **More macros to handle floating point types:** E.g, query the characteristics of floating point types, concern subnormal floating point numbers and count the number of decimal digits the type is able to store
15. In header file **&lt;time.h&gt;:** We can use structure **"struct timespec"**, macro **"TIME_UTC"** and function **"timespec_get"** to support time process