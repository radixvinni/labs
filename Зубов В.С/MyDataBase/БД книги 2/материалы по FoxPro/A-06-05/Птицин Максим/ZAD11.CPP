#include<conio.h>
#include<iostream.h>

void Zad11 (void)
   {
   clrscr();
   cout<<"Zadacha 11 po matlogike\n";
   cout<<"Vuchislenie a^k(mod n)\n";
   cout<<"Vvedite a,k,n:\n";
   long a,k,n,i=0;
   cout<<"a= "; cin>>a;
   cout<<"k= "; cin>>k;
   cout<<"n= "; cin>>n;
   cout<<"a^k(mod n)= ";
   int kbin[255],t=0;
 //  for(i=0;i<256; i++)
  //    kbin[i]=0;
   int k1=k;
   while(k!=0)
      {
      kbin[t]=k-((int)k/2)*2;
      k=k/2;
      t++;
      };
//   for (i=0;i<t;i++)
  //    cout<<endl<<kbin[i];
   long b=1;
   long A=a;
   if (k1==0) cout<<b; else
      {
      for (i=1; i<t;i++)
	 {
	 A=A*A;
	 A=A-(A/n)*n;
	 if  (kbin[i]==1)
	    {
	    b=A*b;
	    b=b-(b/n)*n;
	    };
	 };
      cout<<b;
      };
   }