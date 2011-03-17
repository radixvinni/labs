#pragma once
#include <memory.h>
#include <stdio.h>

//typedef void (__clrcall *LNPROC)(int, int);

class myGraf
{
        bool contact[100][100];  //use: contact[max(i,j)][min(i,j)]
        unsigned m;
        public:
        unsigned n;
        myGraf() : n(0), m(0) { memset(contact,0,10000); }
        myGraf(myGraf &a) : n(a.n), m(a.m) { memcpy(contact,a.contact,10000); }
        ~myGraf() {}
		void Clear() {memset(contact,0,10000);n=0,m=0;}
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
        //bool validR;
        bool searchAB(unsigned a, unsigned b)
        {
                unsigned fifo[101];
                for(int i=0;i<101;i++)
                        R[i]=-1;
                int i=0,k=0;
                R[a]=-2;
                fifo[0]=a;
                do
                {
                        //LNPROC lnp;
						//lnp = (LNPROC)lnptr;

						unsigned t=fifo[i++];
                        for(int j=0;j<n;j++)
                        if (touchingAB(t,j)&&R[j]==-1)
                        if (j==b)
                        {
                                R[j]=t;
                                //draw lines
                                for(int l=b;R[l]!=-2;l=R[l])
                                        //lnp(l,R[l]);
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
        template <class GrafDrawer> bool drawR(GrafDrawer &dr, unsigned b)
        {
                for(int l=b;l!=-2;l=R[l])
                        dr.node(l);
        }
        void clearR()
        {
                for(int i=0;i<101;i++)
                        R[i]=-2;
        }
        template <class GrafDrawer> int searchABnotR(GrafDrawer &dr,unsigned a, unsigned b, unsigned c, unsigned d)
        {
                int kk=0;
                int r[101];
                for(int i=0;i<101;i++)
                        r[i]=-1;
                for(unsigned i=d;i!=-2;i=R[i])
                        r[i]=-3;
                unsigned lifo[101];
                r[a]=-2;
                unsigned t=a;
                lifo[0]=a;
                int k=1;
                int j=0;
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
                                        j=-1;
                                        if(t==b)
                                        {
                                                kk++;
                                                for(int l=b;r[l]!=-2;l=r[l])
                                                        dr.nodeline(l,r[l]);
                                        }
                                }
                                j++;
                        }
                        else
                        {
                                //nothing found. step back.
                                r[t]=-1;
                                j=t+1;
                                t=lifo[--k];
                        }
                }
                while (k>0);
                return kk;
        }
};
