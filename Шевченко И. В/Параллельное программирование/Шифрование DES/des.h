extern unsigned long	deseval (const unsigned long *p,
			const unsigned long *c, const unsigned long *k);

void set_bitlength (void);
int odd_parity (int	n);
void
key_found (
	unsigned long	slice,
	unsigned long	*keybits
);

void
increment_key (
	unsigned long	*key
);

void
set_low_keys (
	unsigned long	*key
);
void
set_high_keys (
	unsigned long	*key,
	int num,
	unsigned int my_num
);
void
test_speed (
	const unsigned long	*p,
	const unsigned long	*c,
	unsigned long	*k
);
int
keysearch (
	const unsigned long	*p,
	const unsigned long	*c,
	unsigned long	*k
);

void
unroll_bits (
	unsigned long		*p,
	unsigned long		*c,
	unsigned long		*k,
	const unsigned char	*ivc,
	const unsigned char	*pc,
	const unsigned char	*cc,
	const unsigned char	*kc
);
void
build_samples (
	unsigned long	*p,
	unsigned long	*c,
	unsigned long	*k,
	int		practice_flag
);

