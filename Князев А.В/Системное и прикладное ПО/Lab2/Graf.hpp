#pragma once

#define _CRT_SECURE_NO_WARNINGS

#pragma warning( disable : 4996 )

#include <memory.h>
#include <stdio.h>

class Graf
{
	bool contact[100][100];  //use: contact[max(i,j)][min(i,j)]
	unsigned m;
	public:
	unsigned n;
	Graf() : n(0), m(0) { memset(contact,0,10000); }
	Graf(Graf &a) : n(a.n), m(a.m) { memcpy(contact,a.contact,10000); }
	~Graf() {}
	void clear() { memset(contact,0,10000); m=0; }
	void setAB(unsigned a, unsigned b) { contact[a>b?a:b][a>b?b:a]=true;m++; }
	bool touchingAB(unsigned a, unsigned b){ return contact[a>b?a:b][a>b?b:a]; }
	unsigned newA() {return n++;}
	void fload(char filename[255])
	{
		FILE* f = fopen(filename,"rb");
		if(!f)return;
		fread(contact,10000,1,f);
		fread(&n,sizeof(n),1,f);
		fread(&m,sizeof(m),1,f);
		fclose(f);
	}
	void fsave(char filename[255])
	{
		FILE* f = fopen(filename,"wb");
		if(!f)return;
		fwrite(contact,10000,1,f);
		fwrite(&n,sizeof(n),1,f);
		fwrite(&m,sizeof(m),1,f);
		fclose(f);
	}
	int R[101]; // temp array
	template <class GrafDrawer> bool searchAB(GrafDrawer &dr, unsigned a, unsigned b)
	{
		//поиск в ширину, если нужен
		//ищет путь из a в b 
		unsigned fifo[101];
		for(int i=0;i<101;i++)
		R[i]=-1;
		int i=0,k=0;
		R[a]=-2;
		fifo[0]=a;
		do
		{
			unsigned t=fifo[i++];
			for(int j=0;j<n;j++)
			if (touchingAB(t,j)&&R[j]==-1)
			if (j==b)
			{
				R[j]=t;
				//draw lines
				for(int l=b;R[l]!=-2;l=R[l])
					dr.nodeline(l,R[l]);
				return true;
			}
			else
			{
				R[j]=t;
				fifo[++k]=j;
			}
		}
		while (k>=i);
		return false;
	}
	template <class GrafDrawer> int searchPath(GrafDrawer &dr,unsigned a, unsigned c, unsigned d)
	{
		//поиск в длину по заданию
		//а-вершина, с:d- ребро
		int kk=0;
		int r[101];
		for(int i=0;i<101;i++)
		r[i]=-1;
		unsigned lifo[101];
		r[a]=-2;
		unsigned t=a;
		lifo[0]=a;
		int k=1;
		unsigned j=0;
		bool wasCD = false;
		do
		{
			if(j<n)
			for(;j<n;j++)
			if(touchingAB(t,j)) break;
			if(j<n)
			{
				if(r[j]==-1)
				{
					//found. step forward.
					lifo[k++]=t;
					r[j]=t;
					t=j;
					j=(unsigned)(-1);
					if(t==c&&wasCD==false)
					{
						lifo[k++]=t;
						r[d]=t;
						t=d;
						j=(unsigned)(-1);
						wasCD=true;
					}
					if(t==d&&wasCD==false)
					{
						lifo[k++]=t;
						r[c]=t;
						t=c;
						j=(unsigned)(-1);
						wasCD=true;
					}
				}
				if(j==a&&k>kk&&wasCD)
				{
					kk=k+1;
					for(int m=0;m<k;m++)
						R[m]=lifo[m];
					R[k]=t;
					R[k+1]=a;
				}
				j++;
			}
			else
			{
				//nothing found. step back.
				r[t]=-1;
				j=t+1;
				if(t==c)wasCD=false;
				if(t==d)wasCD=false;
				t=lifo[--k];
			}
		}
		while (k>0);
		if(kk>0)
		{
			for(int m=0;m<kk;m++)
				dr.nodeline(R[m],R[m+1]);
		}
		return kk;
	}
};
