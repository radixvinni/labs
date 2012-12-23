//mpicc.mpich2 -o ~/prog
//mpiexec.mpich2 -n 4 ~/prog
#include <mpi.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "des.h"

int main(int argc, char *argv[])
{
	int 	numprocs;
	int 	myid;
	int		i;
	int		speed_flag = 0;
	int		practice_flag = 0;
	unsigned long	p[64], c[64], k[56];

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 
	MPI_Comm_rank(MPI_COMM_WORLD,&myid); 
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
	set_high_keys(k, numprocs, myid);
	MPI_Barrier(MPI_COMM_WORLD);
	double t=MPI_Wtime();
	if (speed_flag)
		test_speed (p, c, k);
	else
		if(keysearch (p, c, k)) MPI_Abort(MPI_COMM_WORLD, 0);
	MPI_Barrier(MPI_COMM_WORLD);
	double t2=MPI_Wtime();
	if(myid==0)printf("time:%f\nspeed:%f\n",t2-t, (double)numprocs*1000000/(t2-t));
	MPI_Finalize();
	return 0;
}

