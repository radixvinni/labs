CXXFLAGS=-O2

all:posled parallel Makefile

posled:posled.cpp

parallel:parallel.cpp
	mpicxx parallel.cpp -o parallel
test:
	mpiexec -n 4 ~/.mpi/parallel
clean:
	if [ -f posled ];then rm posled;fi
	if [ -f parallel ];then rm parallel;fi
