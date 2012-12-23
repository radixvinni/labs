#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <vector>

int* a = new int[1<<21];
int* b = new int[1<<21];
int  n = 	 1<<21;
int 	ProcNum,	/* Количество процессов */ 
		ProcRank;	/* Ранк Процесса */
int 	recvsize;

int start=0, end=n;
bool asc;

void o(){
	for(int i=0;i<n;i++)printf("%i ",a[i]);
	printf("\n");
}
void oo(){
	for( int i = 0; i < ProcNum; ++i ) {
		MPI_Barrier( MPI_COMM_WORLD );
		if ( i == ProcRank ) {
			printf("%i: ",ProcRank);
			for(int j=0;j<recvsize;j++)printf("%i ",b[j]);
			printf("\n");
		}
	}
}
//применение полуочистителя k
void half_cleaner(int k){
	for(int i=start;i<end;i+=k)
		for(int j=0;(j<k/2)&&(i+j+k/2<end);++j)
			if((a[i+j]<a[i+j+k/2])==asc){
				int t=a[i+j];
				a[i+j]=a[i+j+k/2];
				a[i+j+k/2]=t;
			}
}
void half_cleaner_parallel(int k){
	for(int i=start;i<end;i+=k)
		for(int j=0;(j<k/2)&&(i+j+k/2<end);++j)
			if((b[i+j]<b[i+j+k/2])==asc){
				int t=b[i+j];
				b[i+j]=b[i+j+k/2];
				b[i+j+k/2]=t;
			}
}

//применение полуочистителя k с чередованием направления упорядочивания
void half_cleaner_alter(int k){
	bool asc=false;
	for(int i=0;i<recvsize;i+=k)
	{	for(int j=0;(j<k/2)&&(i+j+k/2<recvsize);++j)
			if((b[i+j]<b[i+j+k/2])==asc){
				int t=b[i+j];
				b[i+j]=b[i+j+k/2];
				b[i+j+k/2]=t;
			}
		asc=!asc;
	}
}

//сортировка битоническим слянием k
void bitonic_sort(int k)
{
	while(k!=1) {
		half_cleaner(k);
		k=(k/2);
	}
	
}
void bitonic_sort_parallel(int k)
{
	while(k!=1) {
		half_cleaner_parallel(k);
		k=(k/2);
	}
	
}
void all_sort() {
	if(MPI_Scatter(a, recvsize, MPI_INT, b, recvsize, MPI_INT, 0, MPI_COMM_WORLD)!=MPI_SUCCESS)return;
	
	half_cleaner_alter(2);
	int k=4;
	for(;k<=n/ProcNum;k<<=1){
		asc=ProcRank%2;
		for(int i=0;i+k<=n/ProcNum;i+=k)
		{
			
			start=i;
			end=i+k;
			bitonic_sort_parallel(k);
			asc=!asc;
		}
	}
	if(MPI_Gather(b, recvsize, MPI_INT, a, recvsize, MPI_INT, 0, MPI_COMM_WORLD)!=MPI_SUCCESS)return;
	if(ProcRank==0)
	for(;k<=n;k<<=1){
		asc=false;
		for(int i=0;i+k<=n;i+=k)
		{
			
			start=i;
			end=i+k;
			bitonic_sort(k);
			asc=!asc;
		}
	}
	
}

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
	
	if(ProcRank==0){
		for(int i=0;i<n;++i)a[i]=rand()%100;
	}
	recvsize=n/ProcNum;
	time_t start=clock();
	all_sort();
	time_t end = clock();
	
	if(ProcRank==0){
		bool ok=true;
		for(int i=1;i<n;++i)if(a[i-1]>a[i])ok=false;
		double workTime = end-start;
		workTime /= CLOCKS_PER_SEC;
		if(ok)printf("Calculation takes: %.5f sec\n", workTime);
	}
	MPI_Finalize();
	return 0;
}

