//#include "intrin_des.h"

#ifdef __SSE2__
#include <emmintrin.h>
#ifdef __GNUC__
#define uint64 long long
#define inline __attribute__((always_inline))
#define aligned __attribute__((aligned(16)))
#endif

typedef __m128i KTYPE;
aligned KTYPE KCONST_0, KCONST_1, KCONST_2;

KTYPE inline n(const KTYPE &a)
{
        KTYPE result;
        result = _mm_andnot_si128(a, KCONST_1);
        return result;
}
KTYPE inline eqxor(KTYPE &a, const KTYPE &b)
{
        a = _mm_xor_si128(a, b);
        return a;
}
KTYPE inline eqand(KTYPE &a, const KTYPE &b)
{
        a = _mm_and_si128(a, b);
        return a;
}

bool eq( KTYPE &a,  KTYPE &b)
{
	long long* a0 = reinterpret_cast<long long *>(&a);
	long long* b0 = reinterpret_cast<long long *>(&b);
	if(*a0!=*b0)return false;
	
        a0 = a0+1;
	b0 = b0+1;
	if(*a0!=*b0)return false;
	
	return true;
}
bool neq( KTYPE &a,  KTYPE &b)
{
	long long* a0 = reinterpret_cast<long long *>(&a);
	long long* b0 = reinterpret_cast<long long *>(&b);
	if(*a0!=*b0)return true;
	
        a0 = a0+1;
	b0 = b0+1;
	if(*a0!=*b0)return true;
	
        return false;
}
KTYPE inline x(const KTYPE &a, const KTYPE &b)
{
        KTYPE result;
        result = _mm_xor_si128(a, b);
        return result;
}
KTYPE inline o(const KTYPE &a, const KTYPE &b)
{
        KTYPE result;
        result = _mm_or_si128(a, b);
        return result;
} 
KTYPE inline a(const KTYPE &a, const KTYPE &b)
{
        KTYPE result;
        result = _mm_and_si128(a, b);
        return result;
}


//note: эти операции сдвигают слова по 64 бита
KTYPE inline lsh(const KTYPE &a, const int &b)
{
        KTYPE result;
        result = _mm_slli_epi64(a, b);
        return result;
}
KTYPE inline rsh(const KTYPE &a, const int &b)
{
        KTYPE result;
        result = _mm_srli_epi64(a, b);
        return result;
}
KTYPE inline eqrsh(KTYPE &a, const int &b)
{
        a=_mm_srli_epi64(a, b);
        return a;
}


#endif
