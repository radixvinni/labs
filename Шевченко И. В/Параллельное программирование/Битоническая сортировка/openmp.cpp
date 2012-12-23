#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <omp.h>

int a[1<<21];
int n=1<<21;
int iter=0;

void o(){
	for(int i=0;i<n;i++)printf("%i ",a[i]);
	printf("\n");
}
//применение полуочистителя k
void half_cleaner(int start, int end, bool asc, int k){
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
void all_sort() {
	half_cleaner_alter(2);
	int k=4;
	for(;k<=n/4;k<<=1)
#pragma omp parallel firstprivate(k) shared(a,n)
		{
			bool asc=omp_get_thread_num()%2;
#pragma omp for 
			for(int i=0;i<=n-k;i+=k)
			{
				bitonic_sort(i,i+k,asc,k);
				asc=!asc;
			}
		}

	for(;k<=n;k<<=1){bool asc=false;
	for(int i=0;i+k<=n;i+=k)
	{
		bitonic_sort(i,i+k,asc,k);
		asc=!asc;
	}}
}

//bool desc (int i,int j) { return (i>j); }
int main(int argc, char* argv[])
{
	for(int i=0;i<n;++i)a[i]=rand()%100;
	//std::vector<int> myvector (a, a+n);
	//sort(myvector.begin(), myvector.begin()+n/2);
	//sort(myvector.begin()+n/2, myvector.begin()+n,desc);
	//memcpy( a, &myvector[0], sizeof( int ) * myvector.size() );
	
	time_t start=clock();
	all_sort();
	time_t end = clock();
	
	bool ok=true;
	for(int i=1;i<n;++i)if(a[i-1]>a[i])ok=false;
	double workTime = end-start;
	workTime /= CLOCKS_PER_SEC;
	if(ok)printf("Iter: %i, Calculation takes: %.5f sec\n", 4*iter, workTime);
	return 0;
}

