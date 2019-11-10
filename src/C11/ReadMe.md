# C11

Introduce the new language features, we use Microsoft compiler **"cl.exe"** to confirm it, you can refer to **[this link](https://blog.csdn.net/u012611878/article/details/79090793)** in **Chinese**. I'll save this page, so you can refer to the following items:
1. **[Changes in C11](doc\Changes-in-C11.docx)** in **Chinese**
2. **[Welcome-to-Pelles-C.chm](doc\Welcome-to-Pelles-C.chm)**
**Notice:** You can check "unlock" in the property of the "*.chm" file to see the content, please refer to **[this documentation](doc\How-to-unlock-dot-chm-file.docx)** if you still don't know how to deal with it

## Features list

1. Operator **<code>alignof</code>** is used to process alignment, please refer to **section 7.15** about function **<code>aligned_alloc()</code>** in header file **&lt;stdalign.h&gt;**
2. Mark **"<code>_Noreturn</code>"** is similar to **<code>__attribute__((noreturn))</code>** in **gcc** for functions. E.g, **<code>_Noreturn void thrd_exit(int res);</code>**
3. Keyword **<code>_Generic</code>** is similar to **<code>typeof</code>** in **gcc**
4. Static assertions are processed after **<code>#if</code>** and **<code>#error</code>** are interpreted. E.g, **<code>_Static_assert(FOO > 0, "FOO has a wrong value");</code>**
5. The function **<code>gets()</code>** is deprecated, please use function **<code>gets_s()</code>** instead
6. New mode for function **<code>fopen()</code>** like **"...x"** such as **"rbx" (read in binary and extended mode)**, it's similar to **<code>O_CREAT | O_EXCL</code>** in **POSIX** and usually used in file locks
7. **Anonymous struct/union** is already in **gcc**, please refer to **section 6.7.2.1** at page 13
8. **Supports for multi-threads**, such as **<code>_Thread_local</code>** for local thread, **<code>thrd_create()</code>**, **<code>thrd_exit()</code>** and mutex like **<code>mtx_lock()</code>** and **<code>mtx_unlock()</code>**", etc for thread creation and management functions, please refer to **section 7.26**
9. **<code>_Atomic</code>** type modifier in header file **&lt;stdatomic.h&gt;**, please refer to **section 7.17**
10. New **safe** functions that make **"Bounds-checking"**, such as **<code>fopen_s()</code>**, **<code>strcat_s()</code>**, etc. Please refer to **Annex K**
11. **Improved Unicode support**, e.g, new header file **&lt;uchar.h&gt;**, etc.
12. Add function **<code>quick_exit()</code>** as the optional way to terminate the program with minimal cleanup when <code>exit()</code> fails, please refer to **section 7.22.4.7**
13. Add macro **<code>CMPLX()</code>** to create complex, please refer to **section 7.3.9.3**
14. **More macros to handle floating point types:** E.g, query the characteristics of floating point types, concern subnormal floating point numbers and count the number of decimal digits the type is able to store
15. In header file **&lt;time.h&gt;:** We can use structure **<code>struct timespec</code>**, macro **<code>TIME_UTC</code>** and function **<code>timespec_get</code>** to support time process