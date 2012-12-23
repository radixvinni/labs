CFLAGS="-O2"
all: mpi nompi openmp pthreads

mpi: des.c des.h deseval.c mpi.c
	mpicxx des.c des.h deseval.c mpi.c -o mpi

nompi: des.c des.h deseval.c nompi.c

openmp: openmp.c des.c des.h deseval.c
	$(CC) $(CFLAGS) -fopenmp openmp.c des.c des.h deseval.c -o openmp

pthreads: pthreads.c des.c des.h deseval.c
	$(CC) $(CFLAGS) -lpthread pthreads.c des.c des.h deseval.c -o pthreads

test:
	mpiexec -n 4 ~/mpi -S
	./nompi -S
	./openmp -S
	./pthreads -S

clean:
	rm mpi nompi openmp pthreads
