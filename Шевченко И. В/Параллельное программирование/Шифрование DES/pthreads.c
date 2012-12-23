#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include "des.h"
#include <pthread.h>

#include <sys/time.h>

#define NUM_THREADS     32
extern int abor;
struct thread_data{
   int  tid;
   int 	speed_flag;
   unsigned long *p, *c;
   unsigned long k[56];//thread-safe
};
struct thread_data thread_data_array[NUM_THREADS];

void *parallel(void* tdata)
{
	struct thread_data *td=(struct thread_data *)tdata;
	set_high_keys(td->k, NUM_THREADS, td->tid);
	if (td->speed_flag)
	    test_speed (td->p, td->c, td->k);
	else
	    if(keysearch (td->p, td->c, td->k)) abor=0;
	//pthread_exit(NULL);
}

int
main (
	int		argc,
	char		*argv[]
) {
	int		i;
	int		speed_flag = 0;
	int		practice_flag = 0;
	unsigned long	p[64], c[64], k[56];
	pthread_t 	threads[NUM_THREADS];
	
	struct timeval	start_tv, end_tv;
	
	//pthread_attr_t 	attr;
	//pthread_attr_init(&attr);
	//pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	
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
	
	gettimeofday (&start_tv, NULL);
	for(i=0; i<NUM_THREADS; i++)
	{
		thread_data_array[i].tid = i;
		thread_data_array[i].p=p;
		thread_data_array[i].c=c;
		thread_data_array[i].speed_flag=speed_flag;
		memcpy(thread_data_array[i].k,k,sizeof(k));
		if (pthread_create(&threads[i], NULL, parallel, (void*)&thread_data_array[i]))
		{
			exit(-1);//exit сам завершает все потоки
		}
	}
	for (i=0; i<NUM_THREADS; ++i) {
		pthread_join(threads[i], NULL);
	}
	gettimeofday (&end_tv, NULL);
	double tt = (double)(end_tv.tv_sec - start_tv.tv_sec)
				+ (double)(end_tv.tv_usec - start_tv.tv_usec)/1000000;
	if (speed_flag)
	printf("time:%f\nspeed:%f\n",tt, (double) NUM_THREADS*1000000/tt);
	
	//pthread_attr_destroy(&attr);
	//pthread_exit(NULL);
	return 0;
}
