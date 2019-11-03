#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
// Feature #1: "cl.exe" doesn't support operator "alignof"
// #include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
// Feature #13: structure "struct timespec", macro "TIME_UTC" and function "timespec_get"
#include <time.h>
// Feature #12: Macros to enhance complex and floating point, "cl.exe" doesn't support <tgmath.h>
#include <complex.h>
// #include <tgmath.h>
#include <math.h>
#include <assert.h>
// Feature #8: "cl.exe" doesn't support "_Thread_local"
// #include <threads.h>
// Feature #9: "cl.exe" doesn't support "_Atomic"
// #include <stdatomic.h>
// Feature 10: Improved Unicode support
#include <uchar.h>
#include <locale.h>
// Feature #2: "cl.exe" doesn't support modifier "_Noreturn"
// #include <stdnoreturn.h>

/*
// Feature #2: "cl.exe" doesn't support modifier "_Noreturn"
// 在 i <= 0 时导致未定义行为
// 在 i > 0 时退出
_Noreturn void stop_now(int i) // 或 _Noreturn void stop_now(int i)
{
	if (i > 0) exit(i);
}
*/

// Feature #7: Anonymous structure and union
struct Person
{
	char *name;
	int age;
	struct
	{
		char *areaCode;
		char *phoneNumber;
	};
};

void f1(void)
{
	OutputDebugString("pushed first\n");
	puts("pushed first\n");
	fflush(stdout);
}

void f2(void)
{
	OutputDebugString("pushed second\n");
	puts("pushed second\n");
}

int main()
{	
/*
	// Feature #1: "cl.exe" doesn't support
	printf("alignof(double) = %d\n", alignof(double));
	int *p1 = malloc(10 * sizeof *p1);
	printf("default-aligned addr:   %p\n", (void*)p1);
	free(p1);

	int *p2 = aligned_alloc(1024, 10 * sizeof *p2);
	printf("1024-byte aligned addr: %p\n", (void*)p2);
	free(p2);
*/

/*
	puts("Preparing to stop...");
	stop_now(2);
	puts("This code is never executed.");
*/

/*
	// Feature #4: _Static_assert(), it's a little different in "cl.exe"
	// This will generate error at compiling time
	_STATIC_ASSERT(sizeof(int) < sizeof(char), "this program requires that int is less than char");
*/
	// Microsoft uses the value of expression as the size of an array 
	// while it's disabled to define an array which size is 0, 
	// _STATIC_ASSERT(sizeof(int) < sizeof(char));

/*
	// Feature #6: "cl.exe" doesn't support create or open file in exclusive mode
	FILE *fp1 = NULL, *fp2 = NULL;
	if (0 == fopen_s(&fp1, "doc\\Changes-in-C11.docx", "rbx"))
	{
		printf("Open file \"doc\\Changes-in-C11.docx\" successfully!\n");
		if (0 == fopen_s(&fp2, "doc\\Changes-in-C11.docx", "rb"))
		{
			printf("Open file \"doc\\Changes-in-C11.docx\" successfully!\n");
			fclose(fp2);
		}
		else
		{
			fclose(fp1);
			printf("Must close the file pointer \"fp1\" at first\n");
		}
	}
*/

	// Feature #7: Anonymous structure and union
	struct Person p = { "SweetLover", 28, { "zh-CN", "123-4567-8910" } };
	printf("Area code is: %s\n", p.areaCode);

	// Feature #9: "cl.exe" doesn't support "_Atomic"
	// atomic_int acnt;

	// Feature #10: Improved Unicode support, limited support by "cl.exe"
	char s1[] = "a猫?"; // 或 "a\u732B\U0001F34C"
	char s2[] = u8"a猫?";
	char16_t s3[] = u"a猫?";
	char32_t s4[] = U"a猫?";
	wchar_t s5[] = L"a猫?";

	setlocale(LC_ALL, "en_US.utf8");
	printf("  \"%s\" is a char[%zu] holding { ", s1, sizeof s1 / sizeof *s1);
	for (size_t n = 0; n < sizeof s1 / sizeof *s1; ++n)
		printf("%#x ", +(unsigned char)s1[n]);
	puts(" }");
	printf("u8\"%s\" is a char[%zu] holding { ", s2, sizeof s2 / sizeof *s2);
	for (size_t n = 0; n < sizeof s2 / sizeof *s2; ++n)
		printf("%#x ", +(unsigned char)s2[n]);
	puts(" }");
	printf(" u\"a猫?\" is a char16_t[%zu] holding { ", sizeof s3 / sizeof *s3);
	for (size_t n = 0; n < sizeof s3 / sizeof *s3; ++n)
		printf("%#x ", s3[n]);
	puts(" }");
	printf(" U\"a猫?\" is a char32_t[%zu] holding { ", sizeof s4 / sizeof *s4);
	for (size_t n = 0; n < sizeof s4 / sizeof *s4; ++n)
		printf("%#x ", s4[n]);
	puts(" }");
	printf(" L\"%ls\" is a wchar_t[%zu] holding { ", s5, sizeof s5 / sizeof *s5);
	for (size_t n = 0; n < sizeof s5 / sizeof *s5; ++n)
		printf("%#x ", (unsigned)s5[n]);
	puts(" }");

	// Feature #12: Macros to enhance complex and floating point
	_Fcomplex z1 = _FCmulcc(I, I);
	printf("I * I = %.1f%+.1fi\n", crealf(z1), cimagf(z1));

	_Fcomplex cnt = { 2.0, 0 };
	_Fcomplex z2 = cpowf(I, cnt);
	printf("pow(I, 2) = %.1f%+.1fi\n", crealf(z2), cimagf(z2));

	double fPI = acos(-1);
	_Fcomplex _fcPI = { fPI, 0 };
	_Fcomplex z3 = cexpf(_FCmulcc(I, _fcPI)); // Euler's formula
	printf("exp(I*PI) = %.1f%+.1fi\n", crealf(z3), cimagf(z3));

	_Fcomplex z4 = { 1, 0 }, z5 = { 1, 0}, z6 = _FCmulcc(cnt, I);
	// z4 and z5 are conjugated with each other after below 2 steps (conjugated means "共轭")
	// In fact, we'd like to construct z4 and z5 as "z4 = 1 + 2i" and "z5 = 1 - 2i"
	// but "cl.exe" doesn't support operator overloading for "+"/"-" in C language
	z4._Val[0] += z6._Val[0], z4._Val[1] += z6._Val[1];
	z4._Val[0] += z6._Val[0], z4._Val[1] += z6._Val[1];
	z6 = _FCmulcc(z4, z5);
	printf("(1+2i)*(1-2i) = %.1f%+.1fi\n", crealf(z6), cimagf(z6));

	// Feature #13: structure "struct timespec", macro "TIME_UTC" and function "timespec_get"
	printf("[time(NULL)]: %ld\n", time(NULL));
	struct timespec ts;
	// clock_gettime(CLOCK_REALTIME, &ts);		// This is in GNU/GCC
	timespec_get(&ts, TIME_UTC);
	printf("timespec_get: tv_sec=%ld, tv_nsec=%ld\n", ts.tv_sec, ts.tv_nsec);

	struct tm t1;
	char date_time[64];
	// "localtime_r" is in GNU/GCC
	strftime(date_time, sizeof(date_time), "%Y-%m-%d %H:%M:%S", localtime(&ts.tv_sec));
	printf("strftime: date_time=%s, tv_nsec=%ld\n", date_time, ts.tv_nsec);


	printf("[time(NULL)]: %ld\n", time(NULL));
	struct timeval us;
	// gettimeofday(&us, NULL);					// This is in GNU/GCC	
	// printf("gettimeofday: tv_sec=%ld, tv_usec=%ld\n", us.tv_sec, us.tv_usec);

	time_t timer;
	struct tm *tblock;
	timer = time(NULL);
	tblock = localtime(&timer);
	printf("localtime(const time_t *const time) = %s", asctime(tblock));

	struct tm t2;
	// "localtime_r" is in GNU/GCC and "cl.exe" can't obtain current time for "struct timeval"
	// strftime(date_time, sizeof(date_time), "%Y-%m-%d %H:%M:%S", localtime(&us.tv_sec));
	printf("strftime: date_time=%s, tv_nsec=%ld\n", date_time, ts.tv_nsec);
	timer = time(NULL);
	tblock = localtime(&timer);
	printf("localtime(const time_t *const time) = %s", asctime(tblock));

	// Feature #11: "quick_exit()" to exit if "exit()" failed, in <stdlib.h>
	at_quick_exit(f1);
	at_quick_exit(f2);
	quick_exit(0);

	return 0;
}
