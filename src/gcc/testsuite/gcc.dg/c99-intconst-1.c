/* Test for integer constant types.  */

/* Origin: Joseph Myers <jsm28@cam.ac.uk>.  */
/* { dg-do compile } */
/* { dg-options "-std=iso9899:1999 -pedantic-errors" } */
/* { dg-prune-output "In file included from" } */
/* { dg-prune-output "#include_next" } */

#include <limits.h>

/* Assertion that constant C is of type T.  */
#define ASSERT_CONST_TYPE(C, T)			\
	do {					\
	  typedef T type;			\
	  typedef type **typepp;		\
	  typedef __typeof__((C)) ctype;	\
	  typedef ctype **ctypepp;		\
	  typepp x = 0;				\
	  ctypepp y = 0;			\
	  x = y;				\
	  y = x;				\
	} while (0)

/* (T *) if E is zero, (void *) otherwise.  */
#define type_if_not(T, E) __typeof__(0 ? (T *)0 : (void *)(E))

/* (T *) if E is nonzero, (void *) otherwise.  */
#define type_if(T, E) type_if_not(T, !(E))

/* Combine pointer types, all but one (void *).  */
#define type_comb2(T1, T2) __typeof__(0 ? (T1)0 : (T2)0)
#define type_comb3(T1, T2, T3) type_comb2(T1, type_comb2(T2, T3))
#define type_comb4(T1, T2, T3, T4)				\
	type_comb2(T1, type_comb2(T2, type_comb2(T3, T4)))
#define type_comb6(T1, T2, T3, T4, T5, T6)				   \
	type_comb2(T1,							   \
		   type_comb2(T2,					   \
			      type_comb2(T3,				   \
					 type_comb2(T4,			   \
						    type_comb2(T5, T6)))))

/* (T1 *) if E1, otherwise (T2 *) if E2.  */
#define first_of2p(T1, E1, T2, E2) type_comb2(type_if(T1, (E1)),	   \
					     type_if(T2, (!(E1) && (E2))))
/* (T1 *) if E1, otherwise (T2 *) if E2, otherwise (T3 *) if E3.  */
#define first_of3p(T1, E1, T2, E2, T3, E3)			\
	type_comb3(type_if(T1, (E1)),				\
		   type_if(T2, (!(E1) && (E2))),		\
		   type_if(T3, (!(E1) && !(E2) && (E3))))
/* (T1 *) if E1, otherwise (T2 *) if E2, otherwise (T3 *) if E3, otherwise
   (T4 *) if E4.  */
#define first_of4p(T1, E1, T2, E2, T3, E3, T4, E4)			\
	type_comb4(type_if(T1, (E1)),					\
		   type_if(T2, (!(E1) && (E2))),			\
		   type_if(T3, (!(E1) && !(E2) && (E3))),		\
		   type_if(T4, (!(E1) && !(E2) && !(E3) && (E4))))
/* (T1 *) if E1, otherwise (T2 *) if E2, otherwise (T3 *) if E3, otherwise
   (T4 *) if E4, otherwise (T5 *) if E5, otherwise (T6 *) if E6.  */
#define first_of6p(T1, E1, T2, E2, T3, E3, T4, E4, T5, E5, T6, E6)	    \
	type_comb6(type_if(T1, (E1)),					    \
		   type_if(T2, (!(E1) && (E2))),			    \
		   type_if(T3, (!(E1) && !(E2) && (E3))),		    \
		   type_if(T4, (!(E1) && !(E2) && !(E3) && (E4))),	    \
		   type_if(T5, (!(E1) && !(E2) && !(E3) && !(E4) && (E5))), \
		   type_if(T6, (!(E1) && !(E2) && !(E3)			    \
				&& !(E4) && !(E5) && (E6))))

/* Likewise, but return the original type rather than a pointer type.  */
#define first_of2(T1, E1, T2, E2)			\
	__typeof__(*((first_of2p(T1, (E1), T2, (E2)))0))
#define first_of3(T1, E1, T2, E2, T3, E3)				\
	__typeof__(*((first_of3p(T1, (E1), T2, (E2), T3, (E3)))0))
#define first_of4(T1, E1, T2, E2, T3, E3, T4, E4)			    \
	__typeof__(*((first_of4p(T1, (E1), T2, (E2), T3, (E3), T4, (E4)))0))
#define first_of6(T1, E1, T2, E2, T3, E3, T4, E4, T5, E5, T6, E6)	\
	__typeof__(*((first_of6p(T1, (E1), T2, (E2), T3, (E3),		\
				 T4, (E4), T5, (E5), T6, (E6)))0))

/* Types of constants according to the C99 rules.  */
#define C99_UNSUF_DEC_TYPE(C)				\
	first_of3(int, (C) <= INT_MAX,			\
		  long int, (C) <= LONG_MAX,		\
		  long long int, (C) <= LLONG_MAX)
#define C99_UNSUF_OCTHEX_TYPE(C)				\
	first_of6(int, (C) <= INT_MAX,				\
		  unsigned int, (C) <= UINT_MAX,		\
		  long int, (C) <= LONG_MAX,			\
		  unsigned long int, (C) <= ULONG_MAX,		\
		  long long int, (C) <= LLONG_MAX,		\
		  unsigned long long int, (C) <= ULLONG_MAX)
#define C99_SUFu_TYPE(C)					\
	first_of3(unsigned int, (C) <= UINT_MAX,		\
		  unsigned long int, (C) <= ULONG_MAX,		\
		  unsigned long long int, (C) <= ULLONG_MAX)
#define C99_SUFl_DEC_TYPE(C)				\
	first_of2(long int, (C) <= LONG_MAX,		\
		  long long int, (C) <= LLONG_MAX)
#define C99_SUFl_OCTHEX_TYPE(C)					\
	first_of4(long int, (C) <= LONG_MAX,			\
		  unsigned long int, (C) <= ULONG_MAX,		\
		  long long int, (C) <= LLONG_MAX,		\
		  unsigned long long int, (C) <= ULLONG_MAX)
#define C99_SUFul_TYPE(C)					\
	first_of2(unsigned long int, (C) <= ULONG_MAX,		\
		  unsigned long long int, (C) <= ULLONG_MAX)
#define C99_SUFll_OCTHEX_TYPE(C)				\
	first_of2(long long int, (C) <= LLONG_MAX,		\
		  unsigned long long int, (C) <= ULLONG_MAX)

/* Checks that constants have correct type.  */
#define CHECK_UNSUF_DEC_TYPE(C) ASSERT_CONST_TYPE((C), C99_UNSUF_DEC_TYPE((C)))
#define CHECK_UNSUF_OCTHEX_TYPE(C)				\
	ASSERT_CONST_TYPE((C), C99_UNSUF_OCTHEX_TYPE((C)))
#define CHECK_SUFu_TYPE(C) ASSERT_CONST_TYPE((C), C99_SUFu_TYPE((C)))
#define CHECK_SUFl_DEC_TYPE(C) ASSERT_CONST_TYPE((C), C99_SUFl_DEC_TYPE((C)))
#define CHECK_SUFl_OCTHEX_TYPE(C)				\
	ASSERT_CONST_TYPE((C), C99_SUFl_OCTHEX_TYPE((C)))
#define CHECK_SUFul_TYPE(C) ASSERT_CONST_TYPE((C), C99_SUFul_TYPE((C)))
#define CHECK_SUFll_DEC_TYPE(C) ASSERT_CONST_TYPE((C), long long int)
#define CHECK_SUFll_OCTHEX_TYPE(C)				\
	ASSERT_CONST_TYPE((C), C99_SUFll_OCTHEX_TYPE((C)))
#define CHECK_SUFull_TYPE(C) ASSERT_CONST_TYPE((C), unsigned long long int)

/* Check a decimal value, with all suffixes.  */
#define CHECK_DEC_CONST(C)			\
	CHECK_UNSUF_DEC_TYPE(C);		\
	CHECK_SUFu_TYPE(C##u);			\
	CHECK_SUFu_TYPE(C##U);			\
	CHECK_SUFl_DEC_TYPE(C##l);		\
	CHECK_SUFl_DEC_TYPE(C##L);		\
	CHECK_SUFul_TYPE(C##ul);		\
	CHECK_SUFul_TYPE(C##uL);		\
	CHECK_SUFul_TYPE(C##Ul);		\
	CHECK_SUFul_TYPE(C##UL);		\
	CHECK_SUFll_DEC_TYPE(C##ll);		\
	CHECK_SUFll_DEC_TYPE(C##LL);		\
	CHECK_SUFull_TYPE(C##ull);		\
	CHECK_SUFull_TYPE(C##uLL);		\
	CHECK_SUFull_TYPE(C##Ull);		\
	CHECK_SUFull_TYPE(C##ULL);

/* Check an octal or hexadecimal value, with all suffixes.  */
#define CHECK_OCTHEX_CONST(C)			\
	CHECK_UNSUF_OCTHEX_TYPE(C);		\
	CHECK_SUFu_TYPE(C##u);			\
	CHECK_SUFu_TYPE(C##U);			\
	CHECK_SUFl_OCTHEX_TYPE(C##l);		\
	CHECK_SUFl_OCTHEX_TYPE(C##L);		\
	CHECK_SUFul_TYPE(C##ul);		\
	CHECK_SUFul_TYPE(C##uL);		\
	CHECK_SUFul_TYPE(C##Ul);		\
	CHECK_SUFul_TYPE(C##UL);		\
	CHECK_SUFll_OCTHEX_TYPE(C##ll);		\
	CHECK_SUFll_OCTHEX_TYPE(C##LL);		\
	CHECK_SUFull_TYPE(C##ull);		\
	CHECK_SUFull_TYPE(C##uLL);		\
	CHECK_SUFull_TYPE(C##Ull);		\
	CHECK_SUFull_TYPE(C##ULL);

#define CHECK_OCT_CONST(C) CHECK_OCTHEX_CONST(C)
#define CHECK_HEX_CONST(C)			\
	CHECK_OCTHEX_CONST(0x##C);		\
	CHECK_OCTHEX_CONST(0X##C);

/* True iff "long long" is at least B bits.  This presumes that (B-2)/3 is at
   most 63.  */
#define LLONG_AT_LEAST(B)			\
	(LLONG_MAX >> ((B)-2)/3 >> ((B)-2)/3	\
	 >> ((B)-2 - ((B)-2)/3 - ((B)-2)/3))

#define LLONG_HAS_BITS(B) (LLONG_AT_LEAST((B)) && !LLONG_AT_LEAST((B) + 1))

void
foo (void)
{
  /* Decimal.  */
  /* Check all 2^n and 2^n - 1 up to 2^71 - 1.  */
  CHECK_DEC_CONST(1);
  CHECK_DEC_CONST(2);
  CHECK_DEC_CONST(3);
  CHECK_DEC_CONST(4);
  CHECK_DEC_CONST(7);
  CHECK_DEC_CONST(8);
  CHECK_DEC_CONST(15);
  CHECK_DEC_CONST(16);
  CHECK_DEC_CONST(31);
  CHECK_DEC_CONST(32);
  CHECK_DEC_CONST(63);
  CHECK_DEC_CONST(64);
  CHECK_DEC_CONST(127);
  CHECK_DEC_CONST(128);
  CHECK_DEC_CONST(255);
  CHECK_DEC_CONST(256);
  CHECK_DEC_CONST(511);
  CHECK_DEC_CONST(512);
  CHECK_DEC_CONST(1023);
  CHECK_DEC_CONST(1024);
  CHECK_DEC_CONST(2047);
  CHECK_DEC_CONST(2048);
  CHECK_DEC_CONST(4095);
  CHECK_DEC_CONST(4096);
  CHECK_DEC_CONST(8191);
  CHECK_DEC_CONST(8192);
  CHECK_DEC_CONST(16383);
  CHECK_DEC_CONST(16384);
  CHECK_DEC_CONST(32767);
  CHECK_DEC_CONST(32768);
  CHECK_DEC_CONST(65535);
  CHECK_DEC_CONST(65536);
  CHECK_DEC_CONST(131071);
  CHECK_DEC_CONST(131072);
  CHECK_DEC_CONST(262143);
  CHECK_DEC_CONST(262144);
  CHECK_DEC_CONST(524287);
  CHECK_DEC_CONST(524288);
  CHECK_DEC_CONST(1048575);
  CHECK_DEC_CONST(1048576);
  CHECK_DEC_CONST(2097151);
  CHECK_DEC_CONST(2097152);
  CHECK_DEC_CONST(4194303);
  CHECK_DEC_CONST(4194304);
  CHECK_DEC_CONST(8388607);
  CHECK_DEC_CONST(8388608);
  CHECK_DEC_CONST(16777215);
  CHECK_DEC_CONST(16777216);
  CHECK_DEC_CONST(33554431);
  CHECK_DEC_CONST(33554432);
  CHECK_DEC_CONST(67108863);
  CHECK_DEC_CONST(67108864);
  CHECK_DEC_CONST(134217727);
  CHECK_DEC_CONST(134217728);
  CHECK_DEC_CONST(268435455);
  CHECK_DEC_CONST(268435456);
  CHECK_DEC_CONST(536870911);
  CHECK_DEC_CONST(536870912);
  CHECK_DEC_CONST(1073741823);
  CHECK_DEC_CONST(1073741824);
  CHECK_DEC_CONST(2147483647);
  CHECK_DEC_CONST(2147483648);
  CHECK_DEC_CONST(4294967295);
  CHECK_DEC_CONST(4294967296);
  CHECK_DEC_CONST(8589934591);
  CHECK_DEC_CONST(8589934592);
  CHECK_DEC_CONST(17179869183);
  CHECK_DEC_CONST(17179869184);
  CHECK_DEC_CONST(34359738367);
  CHECK_DEC_CONST(34359738368);
  CHECK_DEC_CONST(68719476735);
  CHECK_DEC_CONST(68719476736);
  CHECK_DEC_CONST(137438953471);
  CHECK_DEC_CONST(137438953472);
  CHECK_DEC_CONST(274877906943);
  CHECK_DEC_CONST(274877906944);
  CHECK_DEC_CONST(549755813887);
  CHECK_DEC_CONST(549755813888);
  CHECK_DEC_CONST(1099511627775);
  CHECK_DEC_CONST(1099511627776);
  CHECK_DEC_CONST(2199023255551);
  CHECK_DEC_CONST(2199023255552);
  CHECK_DEC_CONST(4398046511103);
  CHECK_DEC_CONST(4398046511104);
  CHECK_DEC_CONST(8796093022207);
  CHECK_DEC_CONST(8796093022208);
  CHECK_DEC_CONST(17592186044415);
  CHECK_DEC_CONST(17592186044416);
  CHECK_DEC_CONST(35184372088831);
  CHECK_DEC_CONST(35184372088832);
  CHECK_DEC_CONST(70368744177663);
  CHECK_DEC_CONST(70368744177664);
  CHECK_DEC_CONST(140737488355327);
  CHECK_DEC_CONST(140737488355328);
  CHECK_DEC_CONST(281474976710655);
  CHECK_DEC_CONST(281474976710656);
  CHECK_DEC_CONST(562949953421311);
  CHECK_DEC_CONST(562949953421312);
  CHECK_DEC_CONST(1125899906842623);
  CHECK_DEC_CONST(1125899906842624);
  CHECK_DEC_CONST(2251799813685247);
  CHECK_DEC_CONST(2251799813685248);
  CHECK_DEC_CONST(4503599627370495);
  CHECK_DEC_CONST(4503599627370496);
  CHECK_DEC_CONST(9007199254740991);
  CHECK_DEC_CONST(9007199254740992);
  CHECK_DEC_CONST(18014398509481983);
  CHECK_DEC_CONST(18014398509481984);
  CHECK_DEC_CONST(36028797018963967);
  CHECK_DEC_CONST(36028797018963968);
  CHECK_DEC_CONST(72057594037927935);
  CHECK_DEC_CONST(72057594037927936);
  CHECK_DEC_CONST(144115188075855871);
  CHECK_DEC_CONST(144115188075855872);
  CHECK_DEC_CONST(288230376151711743);
  CHECK_DEC_CONST(288230376151711744);
  CHECK_DEC_CONST(576460752303423487);
  CHECK_DEC_CONST(576460752303423488);
  CHECK_DEC_CONST(1152921504606846975);
  CHECK_DEC_CONST(1152921504606846976);
  CHECK_DEC_CONST(2305843009213693951);
  CHECK_DEC_CONST(2305843009213693952);
  CHECK_DEC_CONST(4611686018427387903);
  CHECK_DEC_CONST(4611686018427387904);
  CHECK_DEC_CONST(9223372036854775807);
#if LLONG_AT_LEAST(65)
  CHECK_DEC_CONST(9223372036854775808);
  CHECK_DEC_CONST(18446744073709551615);
#endif
#if LLONG_AT_LEAST(66)
  CHECK_DEC_CONST(18446744073709551616);
  CHECK_DEC_CONST(36893488147419103231);
#endif
#if LLONG_AT_LEAST(67)
  CHECK_DEC_CONST(36893488147419103232);
  CHECK_DEC_CONST(73786976294838206463);
#endif
#if LLONG_AT_LEAST(68)
  CHECK_DEC_CONST(73786976294838206464);
  CHECK_DEC_CONST(147573952589676412927);
#endif
#if LLONG_AT_LEAST(69)
  CHECK_DEC_CONST(147573952589676412928);
  CHECK_DEC_CONST(295147905179352825855);
#endif
#if LLONG_AT_LEAST(70)
  CHECK_DEC_CONST(295147905179352825856);
  CHECK_DEC_CONST(590295810358705651711);
#endif
#if LLONG_AT_LEAST(71)
  CHECK_DEC_CONST(590295810358705651712);
  CHECK_DEC_CONST(1180591620717411303423);
#endif
#if LLONG_AT_LEAST(72)
  CHECK_DEC_CONST(1180591620717411303424);
  CHECK_DEC_CONST(2361183241434822606847);
#endif
  /* Octal and hexadecimal.  */
  /* Check all 2^n and 2^n - 1 up to 2^72 - 1.  */
  CHECK_OCT_CONST(0);
  CHECK_HEX_CONST(0);
  CHECK_OCT_CONST(01);
  CHECK_HEX_CONST(1);
  CHECK_OCT_CONST(02);
  CHECK_HEX_CONST(2);
  CHECK_OCT_CONST(03);
  CHECK_HEX_CONST(3);
  CHECK_OCT_CONST(04);
  CHECK_HEX_CONST(4);
  CHECK_OCT_CONST(07);
  CHECK_HEX_CONST(7);
  CHECK_OCT_CONST(010);
  CHECK_HEX_CONST(8);
  CHECK_OCT_CONST(017);
  CHECK_HEX_CONST(f);
  CHECK_OCT_CONST(020);
  CHECK_HEX_CONST(10);
  CHECK_OCT_CONST(037);
  CHECK_HEX_CONST(1f);
  CHECK_OCT_CONST(040);
  CHECK_HEX_CONST(20);
  CHECK_OCT_CONST(077);
  CHECK_HEX_CONST(3f);
  CHECK_OCT_CONST(0100);
  CHECK_HEX_CONST(40);
  CHECK_OCT_CONST(0177);
  CHECK_HEX_CONST(7f);
  CHECK_OCT_CONST(0200);
  CHECK_HEX_CONST(80);
  CHECK_OCT_CONST(0377);
  CHECK_HEX_CONST(ff);
  CHECK_OCT_CONST(0400);
  CHECK_HEX_CONST(100);
  CHECK_OCT_CONST(0777);
  CHECK_HEX_CONST(1ff);
  CHECK_OCT_CONST(01000);
  CHECK_HEX_CONST(200);
  CHECK_OCT_CONST(01777);
  CHECK_HEX_CONST(3ff);
  CHECK_OCT_CONST(02000);
  CHECK_HEX_CONST(400);
  CHECK_OCT_CONST(03777);
  CHECK_HEX_CONST(7ff);
  CHECK_OCT_CONST(04000);
  CHECK_HEX_CONST(800);
  CHECK_OCT_CONST(07777);
  CHECK_HEX_CONST(fff);
  CHECK_OCT_CONST(010000);
  CHECK_HEX_CONST(1000);
  CHECK_OCT_CONST(017777);
  CHECK_HEX_CONST(1fff);
  CHECK_OCT_CONST(020000);
  CHECK_HEX_CONST(2000);
  CHECK_OCT_CONST(037777);
  CHECK_HEX_CONST(3fff);
  CHECK_OCT_CONST(040000);
  CHECK_HEX_CONST(4000);
  CHECK_OCT_CONST(077777);
  CHECK_HEX_CONST(7fff);
  CHECK_OCT_CONST(0100000);
  CHECK_HEX_CONST(8000);
  CHECK_OCT_CONST(0177777);
  CHECK_HEX_CONST(ffff);
  CHECK_OCT_CONST(0200000);
  CHECK_HEX_CONST(10000);
  CHECK_OCT_CONST(0377777);
  CHECK_HEX_CONST(1ffff);
  CHECK_OCT_CONST(0400000);
  CHECK_HEX_CONST(20000);
  CHECK_OCT_CONST(0777777);
  CHECK_HEX_CONST(3ffff);
  CHECK_OCT_CONST(01000000);
  CHECK_HEX_CONST(40000);
  CHECK_OCT_CONST(01777777);
  CHECK_HEX_CONST(7ffff);
  CHECK_OCT_CONST(02000000);
  CHECK_HEX_CONST(80000);
  CHECK_OCT_CONST(03777777);
  CHECK_HEX_CONST(fffff);
  CHECK_OCT_CONST(04000000);
  CHECK_HEX_CONST(100000);
  CHECK_OCT_CONST(07777777);
  CHECK_HEX_CONST(1fffff);
  CHECK_OCT_CONST(010000000);
  CHECK_HEX_CONST(200000);
  CHECK_OCT_CONST(017777777);
  CHECK_HEX_CONST(3fffff);
  CHECK_OCT_CONST(020000000);
  CHECK_HEX_CONST(400000);
  CHECK_OCT_CONST(037777777);
  CHECK_HEX_CONST(7fffff);
  CHECK_OCT_CONST(040000000);
  CHECK_HEX_CONST(800000);
  CHECK_OCT_CONST(077777777);
  CHECK_HEX_CONST(ffffff);
  CHECK_OCT_CONST(0100000000);
  CHECK_HEX_CONST(1000000);
  CHECK_OCT_CONST(0177777777);
  CHECK_HEX_CONST(1ffffff);
  CHECK_OCT_CONST(0200000000);
  CHECK_HEX_CONST(2000000);
  CHECK_OCT_CONST(0377777777);
  CHECK_HEX_CONST(3ffffff);
  CHECK_OCT_CONST(0400000000);
  CHECK_HEX_CONST(4000000);
  CHECK_OCT_CONST(0777777777);
  CHECK_HEX_CONST(7ffffff);
  CHECK_OCT_CONST(01000000000);
  CHECK_HEX_CONST(8000000);
  CHECK_OCT_CONST(01777777777);
  CHECK_HEX_CONST(fffffff);
  CHECK_OCT_CONST(02000000000);
  CHECK_HEX_CONST(10000000);
  CHECK_OCT_CONST(03777777777);
  CHECK_HEX_CONST(1fffffff);
  CHECK_OCT_CONST(04000000000);
  CHECK_HEX_CONST(20000000);
  CHECK_OCT_CONST(07777777777);
  CHECK_HEX_CONST(3fffffff);
  CHECK_OCT_CONST(010000000000);
  CHECK_HEX_CONST(40000000);
  CHECK_OCT_CONST(017777777777);
  CHECK_HEX_CONST(7fffffff);
  CHECK_OCT_CONST(020000000000);
  CHECK_HEX_CONST(80000000);
  CHECK_OCT_CONST(037777777777);
  CHECK_HEX_CONST(ffffffff);
  CHECK_OCT_CONST(040000000000);
  CHECK_HEX_CONST(100000000);
  CHECK_OCT_CONST(077777777777);
  CHECK_HEX_CONST(1ffffffff);
  CHECK_OCT_CONST(0100000000000);
  CHECK_HEX_CONST(200000000);
  CHECK_OCT_CONST(0177777777777);
  CHECK_HEX_CONST(3ffffffff);
  CHECK_OCT_CONST(0200000000000);
  CHECK_HEX_CONST(400000000);
  CHECK_OCT_CONST(0377777777777);
  CHECK_HEX_CONST(7ffffffff);
  CHECK_OCT_CONST(0400000000000);
  CHECK_HEX_CONST(800000000);
  CHECK_OCT_CONST(0777777777777);
  CHECK_HEX_CONST(fffffffff);
  CHECK_OCT_CONST(01000000000000);
  CHECK_HEX_CONST(1000000000);
  CHECK_OCT_CONST(01777777777777);
  CHECK_HEX_CONST(1fffffffff);
  CHECK_OCT_CONST(02000000000000);
  CHECK_HEX_CONST(2000000000);
  CHECK_OCT_CONST(03777777777777);
  CHECK_HEX_CONST(3fffffffff);
  CHECK_OCT_CONST(04000000000000);
  CHECK_HEX_CONST(4000000000);
  CHECK_OCT_CONST(07777777777777);
  CHECK_HEX_CONST(7fffffffff);
  CHECK_OCT_CONST(010000000000000);
  CHECK_HEX_CONST(8000000000);
  CHECK_OCT_CONST(017777777777777);
  CHECK_HEX_CONST(ffffffffff);
  CHECK_OCT_CONST(020000000000000);
  CHECK_HEX_CONST(10000000000);
  CHECK_OCT_CONST(037777777777777);
  CHECK_HEX_CONST(1ffffffffff);
  CHECK_OCT_CONST(040000000000000);
  CHECK_HEX_CONST(20000000000);
  CHECK_OCT_CONST(077777777777777);
  CHECK_HEX_CONST(3ffffffffff);
  CHECK_OCT_CONST(0100000000000000);
  CHECK_HEX_CONST(40000000000);
  CHECK_OCT_CONST(0177777777777777);
  CHECK_HEX_CONST(7ffffffffff);
  CHECK_OCT_CONST(0200000000000000);
  CHECK_HEX_CONST(80000000000);
  CHECK_OCT_CONST(0377777777777777);
  CHECK_HEX_CONST(fffffffffff);
  CHECK_OCT_CONST(0400000000000000);
  CHECK_HEX_CONST(100000000000);
  CHECK_OCT_CONST(0777777777777777);
  CHECK_HEX_CONST(1fffffffffff);
  CHECK_OCT_CONST(01000000000000000);
  CHECK_HEX_CONST(200000000000);
  CHECK_OCT_CONST(01777777777777777);
  CHECK_HEX_CONST(3fffffffffff);
  CHECK_OCT_CONST(02000000000000000);
  CHECK_HEX_CONST(400000000000);
  CHECK_OCT_CONST(03777777777777777);
  CHECK_HEX_CONST(7fffffffffff);
  CHECK_OCT_CONST(04000000000000000);
  CHECK_HEX_CONST(800000000000);
  CHECK_OCT_CONST(07777777777777777);
  CHECK_HEX_CONST(ffffffffffff);
  CHECK_OCT_CONST(010000000000000000);
  CHECK_HEX_CONST(1000000000000);
  CHECK_OCT_CONST(017777777777777777);
  CHECK_HEX_CONST(1ffffffffffff);
  CHECK_OCT_CONST(020000000000000000);
  CHECK_HEX_CONST(2000000000000);
  CHECK_OCT_CONST(037777777777777777);
  CHECK_HEX_CONST(3ffffffffffff);
  CHECK_OCT_CONST(040000000000000000);
  CHECK_HEX_CONST(4000000000000);
  CHECK_OCT_CONST(077777777777777777);
  CHECK_HEX_CONST(7ffffffffffff);
  CHECK_OCT_CONST(0100000000000000000);
  CHECK_HEX_CONST(8000000000000);
  CHECK_OCT_CONST(0177777777777777777);
  CHECK_HEX_CONST(fffffffffffff);
  CHECK_OCT_CONST(0200000000000000000);
  CHECK_HEX_CONST(10000000000000);
  CHECK_OCT_CONST(0377777777777777777);
  CHECK_HEX_CONST(1fffffffffffff);
  CHECK_OCT_CONST(0400000000000000000);
  CHECK_HEX_CONST(20000000000000);
  CHECK_OCT_CONST(0777777777777777777);
  CHECK_HEX_CONST(3fffffffffffff);
  CHECK_OCT_CONST(01000000000000000000);
  CHECK_HEX_CONST(40000000000000);
  CHECK_OCT_CONST(01777777777777777777);
  CHECK_HEX_CONST(7fffffffffffff);
  CHECK_OCT_CONST(02000000000000000000);
  CHECK_HEX_CONST(80000000000000);
  CHECK_OCT_CONST(03777777777777777777);
  CHECK_HEX_CONST(ffffffffffffff);
  CHECK_OCT_CONST(04000000000000000000);
  CHECK_HEX_CONST(100000000000000);
  CHECK_OCT_CONST(07777777777777777777);
  CHECK_HEX_CONST(1ffffffffffffff);
  CHECK_OCT_CONST(010000000000000000000);
  CHECK_HEX_CONST(200000000000000);
  CHECK_OCT_CONST(017777777777777777777);
  CHECK_HEX_CONST(3ffffffffffffff);
  CHECK_OCT_CONST(020000000000000000000);
  CHECK_HEX_CONST(400000000000000);
  CHECK_OCT_CONST(037777777777777777777);
  CHECK_HEX_CONST(7ffffffffffffff);
  CHECK_OCT_CONST(040000000000000000000);
  CHECK_HEX_CONST(800000000000000);
  CHECK_OCT_CONST(077777777777777777777);
  CHECK_HEX_CONST(fffffffffffffff);
  CHECK_OCT_CONST(0100000000000000000000);
  CHECK_HEX_CONST(1000000000000000);
  CHECK_OCT_CONST(0177777777777777777777);
  CHECK_HEX_CONST(1fffffffffffffff);
  CHECK_OCT_CONST(0200000000000000000000);
  CHECK_HEX_CONST(2000000000000000);
  CHECK_OCT_CONST(0377777777777777777777);
  CHECK_HEX_CONST(3fffffffffffffff);
  CHECK_OCT_CONST(0400000000000000000000);
  CHECK_HEX_CONST(4000000000000000);
  CHECK_OCT_CONST(0777777777777777777777);
  CHECK_HEX_CONST(7fffffffffffffff);
  CHECK_OCT_CONST(01000000000000000000000);
  CHECK_HEX_CONST(8000000000000000);
  CHECK_OCT_CONST(01777777777777777777777);
  CHECK_HEX_CONST(ffffffffffffffff);
#if LLONG_AT_LEAST(65)
  CHECK_OCT_CONST(02000000000000000000000);
  CHECK_HEX_CONST(10000000000000000);
  CHECK_OCT_CONST(03777777777777777777777);
  CHECK_HEX_CONST(1ffffffffffffffff);
#endif
#if LLONG_AT_LEAST(66)
  CHECK_OCT_CONST(04000000000000000000000);
  CHECK_HEX_CONST(20000000000000000);
  CHECK_OCT_CONST(07777777777777777777777);
  CHECK_HEX_CONST(3ffffffffffffffff);
#endif
#if LLONG_AT_LEAST(67)
  CHECK_OCT_CONST(010000000000000000000000);
  CHECK_HEX_CONST(40000000000000000);
  CHECK_OCT_CONST(017777777777777777777777);
  CHECK_HEX_CONST(7ffffffffffffffff);
#endif
#if LLONG_AT_LEAST(68)
  CHECK_OCT_CONST(020000000000000000000000);
  CHECK_HEX_CONST(80000000000000000);
  CHECK_OCT_CONST(037777777777777777777777);
  CHECK_HEX_CONST(fffffffffffffffff);
#endif
#if LLONG_AT_LEAST(69)
  CHECK_OCT_CONST(040000000000000000000000);
  CHECK_HEX_CONST(100000000000000000);
  CHECK_OCT_CONST(077777777777777777777777);
  CHECK_HEX_CONST(1fffffffffffffffff);
#endif
#if LLONG_AT_LEAST(70)
  CHECK_OCT_CONST(0100000000000000000000000);
  CHECK_HEX_CONST(200000000000000000);
  CHECK_OCT_CONST(0177777777777777777777777);
  CHECK_HEX_CONST(3fffffffffffffffff);
#endif
#if LLONG_AT_LEAST(71)
  CHECK_OCT_CONST(0200000000000000000000000);
  CHECK_HEX_CONST(400000000000000000);
  CHECK_OCT_CONST(0377777777777777777777777);
  CHECK_HEX_CONST(7fffffffffffffffff);
#endif
#if LLONG_AT_LEAST(72)
  CHECK_OCT_CONST(0400000000000000000000000);
  CHECK_HEX_CONST(800000000000000000);
  CHECK_OCT_CONST(0777777777777777777777777);
  CHECK_HEX_CONST(ffffffffffffffffff);
#endif
}