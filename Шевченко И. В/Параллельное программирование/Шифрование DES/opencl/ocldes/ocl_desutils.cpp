#include <stdio.h>
#include <stdlib.h>

#define bitlength 64

void
increment_key (
	unsigned long	*key
) {
	unsigned long	*kp = &key[55 - 6];

	while (*kp != 0)
	    *kp-- = 0;

	*kp = ~0UL;
}

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

