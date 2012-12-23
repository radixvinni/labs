#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <emmintrin.h>

short* a;
int n=1<<21;
int iter=0;

void o(){
	for(int i=0;i<n;i++)printf("%i ",a[i]);
	printf("\n");
}
//применение полуочистителя k
//k=4, k=2
void half_cleaner(const int start, const int end, const bool asc, const int k){
	for(int i=start;i<end;i+=k)
		for(int j=0;(j<k/2)&&(i+j+k/2<end);++j)
			if((a[i+j]<a[i+j+k/2])==asc){
				short t=a[i+j];
				a[i+j]=a[i+j+k/2];
				a[i+j+k/2]=t;
			}
	iter++;
}
//k=8
void half_cleaner_8(const int start, const int end, const bool asc){
	for(int i=start;i+7<end;i+=8)
	{
		__m64 t = *(__m64*)&a[i];
		__m64 d = *(__m64*)&a[i+4];
		__m64 mn = _mm_min_pi16(t,d);
		__m64 mx = _mm_max_pi16(t,d);
		if (asc) {
			*(__m64*)&a[i]=mx;
			*(__m64*)&a[i+4]=mn;
		}
		else {
			*(__m64*)&a[i]=mn;
			*(__m64*)&a[i+4]=mx;
		}	
	}
	iter++;
}
//k=16
void half_cleaner_16(const int start, const int end, const bool asc){
	for(int i=start;i+15<end;i+=16)
	{
		//кстати a[i] здесь выравнено под 16, поэтому можно без u, но времени это не прибавляет
		__m128i t = _mm_loadu_si128((__m128i*)&a[i]);
		__m128i d = _mm_loadu_si128((__m128i*)&a[i+8]);
		__m128i mn = _mm_min_epi16(t,d);
		__m128i mx = _mm_max_epi16(t,d);
		if (asc) {
			_mm_storeu_si128((__m128i*)&a[i],mx);
			_mm_storeu_si128((__m128i*)&a[i+8],mn);
		}
		else {
			_mm_storeu_si128((__m128i*)&a[i],mn);
			_mm_storeu_si128((__m128i*)&a[i+8],mx);
		}	
	}
	iter++;
}
//k>16
void half_cleaner_gt16(const int start, const int end, const bool asc, const int k){
	for(int i=start;i<end;i+=k)
	{
		for(int j=0;(j<k/2)&&(i+j+k/2<end);j+=8)
		{
			__m128i t = _mm_loadu_si128((__m128i*)&a[i+j]);
			__m128i d = _mm_loadu_si128((__m128i*)&a[i+j+k/2]);
			__m128i mn = _mm_min_epi16(t,d);
			__m128i mx = _mm_max_epi16(t,d);
			if (asc) {
				_mm_storeu_si128((__m128i*)&a[i+j],mx);
				_mm_storeu_si128((__m128i*)&a[i+j+k/2],mn);
			}
			else {
				_mm_storeu_si128((__m128i*)&a[i+j],mn);
				_mm_storeu_si128((__m128i*)&a[i+j+k/2],mx);
			}
			/*for(int j=0;(j<k/2)&&(i+j+k/2<end);++j)
			if((a[i+j]<a[i+j+k/2])==asc){
				int t=a[i+j];
				a[i+j]=a[i+j+k/2];
				a[i+j+k/2]=t;
			}*/
		}
	
	}
	iter++;
}
//применение полуочистителя k с чередованием направления упорядочивания
// k=2
void half_cleaner_alter(int k){
	bool asc=false;
	for(int i=0;i<n;i+=k)
	{	for(int j=0;(j<k/2)&&(i+j+k/2<n);++j)
			if((a[i+j]<a[i+j+k/2])==asc){
				short t=a[i+j];
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
		if(k>16) half_cleaner_gt16(s,e,a,k);
		else if(k<8) half_cleaner(s,e,a,k);
		else if(k==8) half_cleaner_8(s,e,a);
		else if(k==16) half_cleaner_16(s,e,a);
		else half_cleaner(s,e,a,k);
		k=(k/2);
	}
}

void all_sort() {
	//можно ускорить, если сделать шаг "пилы" не 2, а 16: применять bitonic_sort_16elems отсюда:
	//github.com/hayamiz/sse-practice-sort/blob/master/sse-practice.c
	half_cleaner_alter(2);
	for(int k=4;k<=n;k<<=1){
		bool asc=false;
		for(int i=0;i+k<=n;i+=k)
		{
			bitonic_sort(i,i+k,asc,k);
			asc=!asc;
		}
	}
}
#ifdef __GNUC__
#define MALLOC(pplist,num)\
	posix_memalign(pplist, 16, sizeof(short) * num)
#else
#include <malloc.h>
#define MALLOC(pplist,num)\
	*(pplist)=_aligned_malloc(sizeof(short) * num, 16)
#endif

int main(int argc, char* argv[])
{
	MALLOC((void**)&a,n);
	for(int i=0;i<n;++i)a[i]=rand()%100;
	
	time_t start=clock();
	all_sort();
	time_t end = clock();
	
	bool ok=true;
	for(int i=1;i<n;++i)if(a[i-1]>a[i])ok=false;
	double workTime = end-start;
	workTime /= CLOCKS_PER_SEC;
	if(ok)printf("Iter: %i, Calculation takes: %.5f sec\n", iter, workTime);
	return 0;
}

