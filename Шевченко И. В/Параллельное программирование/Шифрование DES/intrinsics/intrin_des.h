/*#ifdef __MMX__
#include <mmintrin.h>
#endif
 
#ifdef __SSE__
#include <xmmintrin>
#endif
 
#ifdef __SSE3__
#include <pmmintrin>
#endif
 
#ifdef __SSSE3__
#include <tmmintrin.h>
#endif
 
#if defined (__SSE4_2__) || defined (__SSE4_1__)
#include <smmintrin>
#endif*/

#ifdef __SSE2__
#include <emmintrin.h>

#ifdef __GNUC__
#define uint64 long long
#define inline __attribute__((always_inline))
#define aligned __attribute__((aligned(16)))
#endif

typedef __m128i KTYPE;

extern KTYPE KCONST_0, KCONST_1, KCONST_2;

KTYPE inline n(const KTYPE &a);
KTYPE inline eqxor(KTYPE &a, const KTYPE &b);
KTYPE inline eqand(KTYPE &a, const KTYPE &b);
bool eq( KTYPE &a,  KTYPE &b);
bool neq( KTYPE &a,  KTYPE &b);
KTYPE inline x(const KTYPE &a, const KTYPE &b);
KTYPE inline o(const KTYPE &a, const KTYPE &b);
KTYPE inline a(const KTYPE &a, const KTYPE &b);


//note: эти операции сдвигают слова по 64 бита
KTYPE inline lsh(const KTYPE &a, const int &b);
KTYPE inline rsh(const KTYPE &a, const int &b);
KTYPE inline eqrsh(KTYPE &a, const int &b);


#else
#define KTYPE unsigned long
#define KCONST_0 0
#define KCONST_1 ~0UL
#define KCONST_2 1

KTYPE inline n(const KTYPE &a) { return ~a;}
KTYPE inline eqxor(KTYPE &a, const KTYPE &b) { return a^=b;}
KTYPE inline eqand(KTYPE &a, const KTYPE &b) { return a&=b;}
bool eq( KTYPE &a,  KTYPE &b) { return a==b;}
bool neq( KTYPE &a,  KTYPE &b) { return a!=b;}
KTYPE inline x(const KTYPE &a, const KTYPE &b) { return a^b;}
KTYPE inline o(const KTYPE &a, const KTYPE &b) { return a|b;}
KTYPE inline a(const KTYPE &a, const KTYPE &b) { return a&b;}


//note: эти операции сдвигают слова по 64 бита
KTYPE inline lsh(const KTYPE &a, const int &b) { return a<<b;}
KTYPE inline rsh(const KTYPE &a, const int &b) { return a>>b;}
KTYPE inline eqrsh(KTYPE &a, const int &b) { return a>>=b;}

#endif




//KTYPE	deseval (const KTYPE *p, const KTYPE *c, const KTYPE *k);

void set_bitlength (void);
int odd_parity (int	n);
void
key_found (
	KTYPE	slice,
	KTYPE	*keybits
);

void
increment_key (
	KTYPE	*key
);

void
set_low_keys (
	KTYPE	*key
);
void
set_high_keys (
	KTYPE	*key,
	int num,
	unsigned int my_num
);
void
test_speed (
	const KTYPE	*p,
	const KTYPE	*c,
	KTYPE	*k
);
int
keysearch (
	const KTYPE	*p,
	const KTYPE	*c,
	KTYPE	*k
);

void
unroll_bits (
	KTYPE		*p,
	KTYPE		*c,
	KTYPE		*k,
	const unsigned char	*ivc,
	const unsigned char	*pc,
	const unsigned char	*cc,
	const unsigned char	*kc
);
void
build_samples (
	KTYPE	*p,
	KTYPE	*c,
	KTYPE	*k,
	int		practice_flag
);

