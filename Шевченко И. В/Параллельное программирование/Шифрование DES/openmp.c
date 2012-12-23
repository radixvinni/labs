#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "des.h"
#include <omp.h>
extern int abor;
int
main (
	int		argc,
	char		*argv[]
) {
	int		i;
	int		speed_flag = 0;
	int		practice_flag = 0;
	unsigned long	p[64], c[64], k[56];
	
	struct timeval	start_tv, end_tv;
	omp_set_num_threads(8);
	set_bitlength ();

	for (i=1; i<argc; i++) {
	    if (argv[i][0] != '-')
		continue;

	    if (argv[i][1] == 'S')
		speed_flag = 1;
	    else if (argv[i][1] == 'P')
		practice_flag = 1;
	}
	abor=1;
	build_samples (p, c, k, practice_flag);
	set_low_keys(k);
	gettimeofday (&start_tv, NULL);
	#pragma omp parallel shared(p, c) firstprivate(k)
	{
		set_high_keys(k, omp_get_num_threads(), omp_get_thread_num());
		if (speed_flag)
		    test_speed (p, c, k);
		else
		    if(keysearch (p, c, k)) abor=0;
	}
	gettimeofday (&end_tv, NULL);
	double tt = (double)(end_tv.tv_sec - start_tv.tv_sec)
				+ (double)(end_tv.tv_usec - start_tv.tv_usec)/1000000;
	if (speed_flag)
	printf("time:%f\nspeed:%f\n",tt, (double) 8*1000000/tt);
	
	return 0;
}
