/*
 * Test the automatically-generated DES implementation.
 *
 * Key should be - 5e d9 20 4f ec e0 b9 67
 *
 * Written by Matthew Kwan - April 1997.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "des.h"

		/* External functions */
extern unsigned long	deseval (const unsigned long *p,
			const unsigned long *c, const unsigned long *k);

int	bitlength = 32;
int	bitlength_log2 = 5;

void
set_bitlength (void)
{
	unsigned long	x = ~0UL;

	bitlength = 0;
	for (x = ~0UL; x != 0; x >>= 1)
	    bitlength++;

	printf ("%d-bit machine\n", bitlength);

	if (bitlength == 64)
	    bitlength_log2 = 6;
	else if (bitlength == 32)
	    bitlength_log2 = 5;
	else {
	    fprintf (stderr, "Cannot handle %d-bit machines\n", bitlength);
	    exit (1);
	}
}


/*
 * Return an odd parity bit for a number.
 */

int
odd_parity (
	int	n
) {
	int	parity = 1;

	while (n != 0) {
	    if ((n & 1) != 0)
		parity ^= 1;
	    n >>= 1;
	}

	return (parity);
}


/*
 * The key has been found.
 * Turn the value into something readable, and print it out.
 */

void
key_found (
	unsigned long	slice,
	unsigned long	*keybits
) {
	int		i;

	printf ("Key:");

	for (i=0; i<8; i++) {
	    int		j, kc = 0;

	    for (j=0; j<7; j++)
		if ((keybits[49 - i*7 + j] & slice) != 0)
		    kc |= (1 << j);

	    kc = (kc << 1) | odd_parity (kc);

	    printf (" %02x", kc);
	}

	printf ("\n");
}


/*
 * Using the first 56 - bitlength_log2 entries of the key as a counter,
 * iterate to the next value.
 */

void
increment_key (
	unsigned long	*key
) {
	register unsigned long	*kp = &key[55 - bitlength_log2];

	while (*kp != 0)
	    *kp-- = 0;

	*kp = ~0UL;
}


/*
 * Set the bit slice pattern on the low key bits.
 */

void
set_low_keys (
	unsigned long	*key
) {
	int	w = 1;
	int	bp = 55;

	while (w < bitlength) {
	    int		i = 0;

	    while (i < bitlength) {
		int	j;

		for (j=0; j<w; j++)
		    key[bp] = (key[bp] << 1);
		for (j=0; j<w; j++)
		    key[bp] = (key[bp] << 1) | 1;

		i += 2*w;
	    }

	    w *= 2;
	    bp--;
	}
}
void
set_high_keys (
	unsigned long	*key,
	int num,
	unsigned int my_num
) {
	int i;
	if(num<2) return;
	int num_bits=0;
	if(num<=32) num_bits=5;	
	if(num<=16) num_bits=4;	
	if(num<=8) num_bits=3;	
	if(num<=4) num_bits=2;	
	if(num==2) num_bits=1;	
	
	unsigned int mask=1;
	for(i=0;i<num_bits;i++)
	{
		if(my_num&mask) key[i] = ~0UL;
		else key[i] = 0;
		mask=mask<<1;
	}
}


/*
 * Test the DES key evaluation routine for speed.
 */

void
test_speed (
	const unsigned long	*p,
	const unsigned long	*c,
	unsigned long	*k
) {
	int		i, t;
	double		td;
	unsigned long	*key=k;
	struct timeval	start_tv, end_tv;
	const int	n = 1000000;

		/* Do a dummy run to get the function loaded into memory */
	deseval (p, c, key);

		/* Begin the actual run */
	gettimeofday (&start_tv, NULL);

	for (i=0; i<n; i++) {
	    unsigned long	res = deseval (p, c, key);

	    if (res != 0)
		key_found (res, key);

	    increment_key (key);
	}

	gettimeofday (&end_tv, NULL);

	t = (end_tv.tv_sec - start_tv.tv_sec) * 1000000
				+ (end_tv.tv_usec - start_tv.tv_usec);
	td = (double) t / 1000000.0;

	printf ("Searched %i keys in %.1f seconds\n", n, (double) td);
}


/*
 * Iterate through all 2^56 DES keys.
 */
int abor=1;
int
keysearch (
	const unsigned long	*p,
	const unsigned long	*c,
	unsigned long	*k
) {
	unsigned long	*key=k;

	for (;abor;) {
	    unsigned long	res = deseval (p, c, key);

	    if (res != 0)
		{key_found (res, key);return res;}

	    increment_key (key);
	}
	return 0;
}


/*
 * Unroll the bits contained in the plaintext, ciphertext, and key values.
 */

void
unroll_bits (
	unsigned long		*p,
	unsigned long		*c,
	unsigned long		*k,
	const unsigned char	*ivc,
	const unsigned char	*pc,
	const unsigned char	*cc,
	const unsigned char	*kc
) {
	int			i;
	unsigned char		ptext[8];

	for (i=0; i<8; i++)
	    ptext[i] = ivc[i] ^ pc[i];

	for (i=0; i<64; i++)
	    if ((ptext[i/8] & (128 >> (i % 8))) != 0)
		p[63 - i] = ~0UL;
	    else
		p[63 - i] = 0;

	for (i=0; i<64; i++)
	    if ((cc[i/8] & (128 >> (i % 8))) != 0)
		c[63 - i] = ~0UL;
	    else
		c[63 - i] = 0;

	if (kc != NULL) {
	    for (i=0; i<56; i++)
		if ((kc[i/7] & (128 >> (i % 7))) != 0)
		    k[55 - i] = ~0UL;
		else
		    k[55 - i] = 0;
	} else {
	    for (i=0; i<56; i++)
		k[i] = 0;
	}
}


/*
 * Set up the sample plaintext, ciphertext and key values.
 */

void
build_samples (
	unsigned long	*p,
	unsigned long	*c,
	unsigned long	*k,
	int		practice_flag
) {
	unsigned char	iv_p[8]
			= {0xa2, 0x18, 0x5a, 0xbf, 0x45, 0x96, 0x60, 0xbf};
	unsigned char	pt_p[8]
			= {0x54, 0x68, 0x65, 0x20, 0x75, 0x6e, 0x6b, 0x6e};
	unsigned char	ct_p[8]
			= {0x3e, 0xa7, 0x86, 0xf9, 0x1d, 0x76, 0xbb, 0xd3};
	unsigned char	key_p[8]
			= {0x5e, 0xd9, 0x20, 0x4f, 0xec, 0xe0, 0xb9, 0x67};

	unsigned char	iv_s[8]
			= {0x99, 0xe9, 0x7c, 0xbf, 0x4f, 0x7a, 0x6e, 0x8f};
	unsigned char	pt_s[8]
			= {0x54, 0x68, 0x65, 0x20, 0x75, 0x6e, 0x6b, 0x6e};
	unsigned char	ct_s[8]
			= {0x79, 0x45, 0x81, 0xc0, 0xa0, 0x6e, 0x40, 0xa2};

	if (practice_flag)
	    unroll_bits (p, c, k, iv_p, pt_p, ct_p, key_p);
	else
	    unroll_bits (p, c, k, iv_s, pt_s, ct_s, NULL);
}

