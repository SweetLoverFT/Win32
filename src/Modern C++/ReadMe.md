# Modern C++

Introduce the new language features, we use Microsoft compiler **"cl.exe"** to confirm it, you can refer to **[this link](https://zh.cppreference.com/w/cpp)** for C\+\+ language features and **[another link](https://docs.microsoft.com/en-us/previous-versions/hh567368(v=vs.140))** for features supported by **cl.exe**. I will summarize a document about the new features of C\+\+ 11 so you can refer to the following items:

1. **[Modern C++ Specification](doc\Modern-C++-Specification.pdf)** downloaded from **[this link](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3337.pdf)**
2. **[Support For C\+\+11/14/17 Features (Modern C\+\+)](https://docs.microsoft.com/en-us/previous-versions/hh567368(v=vs.140)#c11feature-list)** from MSDN

## C++ 11 Features list

1. **Rvalue references**: Used to improve the performance of the program by unnecessary duplication
2. **ref-qualifiers**: Used for member functions in a class for L-value & R-value callers
3. **Non-static data member initializers**: Used to initialize the member objects **before** constructors, please use **<code>{}</code>** operator
4. **Variadic templates**: Used for overloaded functions with uncertain number and types of parameters
5. **Initializer lists**: 
6. **<code>static_assert</code>**: 
7. **<code>auto</code>**: 
8. **Trailing return types**: 
9. **Lambdas**: 
10. **decltype**: 
11. **Right angle brackets**: 
12. **Default template arguments for function templates**: 
13. **Expression SFINAE**: 
14. **Alias templates**:
15. **Extern templates**: 
16. **<code>nullptr</code>**: 
17. **Strongly typed enums**:
18. **Forward declared enums**: 
19. **Attributes**: 
20. **<code>constexpr</code>**: 
21. **Alignment**:
22. **Delegating constructors**: 
23. **Inheriting constructors**:
24. **Explicit conversion operators**: 
25. **<code>char16_t</code>/<code>char32_t</code>**: 
26. **Unicode string literals**: 
27. **Raw string literals**: 
28. **Universal character names in literals**: 
29. **User-defined literals**: 
30. **Standard-layout and trivial types**: 
31. **Defaulted and deleted functions**: 
32. **Extended friend declarations**: 
33. **Extended sizeof**: 
34. **Inline namespaces**: 
35. **Unrestricted unions**: 
36. **Local and unnamed types as template arguments**: 
37. **Range-based for-loop**: 
38. **<code>override</code> and <code>final</code>**: 
39. **Minimal GC support**: 
40. **<code>noexcept</code>**: 

### C++ 11 Core Language Features Table: Concurrency

1. **Reworded sequence points**: 
2. **Atomics**: 
3. **Strong compare and exchange**: 
4. **Bidirectional fences**: 
5. **Memory model**: 
6. **Data-dependency ordering**: 
7. **Data-dependency ordering: function annotation**: 
8. **exception_ptr**: 
9. **<code>quick_exit</code>**:
10. **Atomics in signal handlers**: 
11. **Thread-local storage**: 
12. **Magic statics**: 

### C++ 11 Core Language Features: C99

1. **<code>__func__</code>**: 
2. **C99 preprocessor**: 
3. **<code>long long</code>**: 
4. **Extended integer types**: 

## C++ 14 Core Language Features

1. **Tweaked wording for contextual conversions**: 
2. **Binary literals**: 
3. **auto and decltype(auto) return types**: 
4. **init-captures**: 
5. **Generic lambdas**: 
6. **Variable templates**: 
7. **Extended constexpr**: 
8. **NSDMIs for aggregates**: 
9. **Avoiding/fusing allocations**: 
10. **[[deprecated]] attributes**: 
11. **Sized allocation**: 
12. **Digit separators**: 

## C++ 17 Core Language Features

1. **New rules for auto with braced-init-lists**: 
2. **Terse static assert**: 
3. **typename in template template-parameters**: 
4. **Removing trigraphs**: 
5. **Nested namespace definitions**: 
6. **N4259 <code>std::uncaught_exceptions()</code>**: 
7. **N4261 Fixing qualification conversions**: 
8. **N4266 Attributes for namespaces and enumerators**: 
9. **N4267 u8 character literals**: 
10. **N4268 Allowing more non-type template args**: 
11. **N4295 Fold expressions**: 
12. **<code>await</code>/<code>resume</code>**: 
