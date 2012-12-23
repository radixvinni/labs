#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <pthread.h>
#define NUM_THREADS 4

int a[1<<21];
int n=1<<21;
int iter = 0;

void o(){
	for(int i=0;i<n;i++)printf("%i ",a[i]);
	printf("\n");
}
//применение полуочистителя k
void half_cleaner(const int start, const int end, const bool asc, const int k){
	for(int i=start;i<end;i+=k)
		for(int j=0;(j<k/2)&&(i+j+k/2<end);++j)
			if((a[i+j]<a[i+j+k/2])==asc){
				int t=a[i+j];
				a[i+j]=a[i+j+k/2];
				a[i+j+k/2]=t;
			}
	iter++;
}
//применение полуочистителя k с чередованием направления упорядочивания
void half_cleaner_alter(int k){
	bool asc=false;
	for(int i=0;i<n;i+=k)
	{	for(int j=0;(j<k/2)&&(i+j+k/2<n);++j)
			if((a[i+j]<a[i+j+k/2])==asc){
				int t=a[i+j];
				a[i+j]=a[i+j+k/2];
				a[i+j+k/2]=t;
			}
		asc=!asc;
	}
}
//сортировка битоническим слянием k
void bitonic_sort(int s,int e,bool a,int k)
{
	while(k!=1) {
		half_cleaner(s,e,a,k);
		k=(k/2);
	}
}
void rest_sort() {
	for(int k=2*n/NUM_THREADS;k<=n;k<<=1){bool asc=false;
	for(int i=0;i+k<=n;i+=k)
	{
		bitonic_sort(i,i+k,asc,k);
		asc=!asc;
	}}
}

void* all_sort(void* p) {
	int num = *((int *) p);
	int k=4;
	for(;k<=n/NUM_THREADS;k<<=1){
		bool asc=num%2;
		for(int i=num*n/NUM_THREADS;i+k<=(num+1)*n/NUM_THREADS;i+=k)
		{
			bitonic_sort(i,i+k,asc,k);
			asc=!asc;
		}
	}
}

int main(int argc, char* argv[])
{
	pthread_t threads[NUM_THREADS];
	int thread_args[NUM_THREADS];
	for(int i=0;i<n;++i)a[i]=rand()%100;
	
	time_t start=clock();
	half_cleaner_alter(2);
	for (int i=0; i<NUM_THREADS; ++i) {
		thread_args[i] = i;
		pthread_create(&threads[i], NULL, all_sort, (void *) &thread_args[i]);
	}
	for (int i=0; i<NUM_THREADS; ++i)
		pthread_join(threads[i], NULL);
	rest_sort();
	time_t end = clock();
	
	bool ok=true;
	for(int i=1;i<n;++i)if(a[i-1]>a[i])ok=false;
	double workTime = end-start;
	workTime /= CLOCKS_PER_SEC;
	if(ok)printf("Iter: %i, Calculation takes: %.5f sec\n", NUM_THREADS*iter, workTime);
	return 0;
}

