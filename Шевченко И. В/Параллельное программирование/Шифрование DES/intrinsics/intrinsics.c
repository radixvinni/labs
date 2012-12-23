#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "intrin_des.h"
 
int main (
	int		argc,
	char		*argv[]
) {
	int		i;
	int		speed_flag = 0;
	int		practice_flag = 0;
	KTYPE		p[64], c[64], k[56];

#ifdef __SSE2__
	KCONST_0=_mm_setzero_si128();
	KCONST_2=_mm_setr_epi32(0,1,0,1);
	KCONST_1=_mm_set1_epi32(-1);
	printf("p=%u, c=%u, k=%u\nc0=%u, c1=%u, c2=%u\n", p, c, k, &KCONST_0, &KCONST_1, &KCONST_2);
#endif

	set_bitlength ();

	for (i=1; i<argc; i++) {
	    if (argv[i][0] != '-')
		continue;

	    if (argv[i][1] == 'S')
		speed_flag = 1;
	    else if (argv[i][1] == 'P')
		practice_flag = 1;
	}

	build_samples (p, c, k, practice_flag);
	set_low_keys(k);
		
	if (speed_flag)
	    test_speed (p, c, k);
	else
	    keysearch (p, c, k);

	return 0;
}
