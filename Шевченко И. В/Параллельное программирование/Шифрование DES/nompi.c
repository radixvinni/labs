#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "des.h"
int
main (
	int		argc,
	char		*argv[]
) {
	int		i;
	int		speed_flag = 0;
	int		practice_flag = 0;
	unsigned long	p[64], c[64], k[56];

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
