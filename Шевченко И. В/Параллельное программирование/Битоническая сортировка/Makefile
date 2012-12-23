CXXFLAGS=-O3 -fopenmp
all:posled parallel pthread openmp intrin

pthread:pthread.cpp

openmp:openmp.cpp

posled:posled.cpp

intrin:intrin.cpp
	$(CXX) -O3 -msse2 intrin.cpp -o intrin

parallel:parallel.cpp
	mpicxx parallel.cpp -o parallel
test:parallel
	mpiexec -n 4 ~/.mpi/parallel
clean:
	if [ -f posled ];then rm posled;fi
	if [ -f parallel ];then rm parallel;fi
	if [ -f openmp ];then rm openmp;fi
	if [ -f pthread ];then rm pthread;fi
	if [ -f intrin ];then rm intrin;fi
	
