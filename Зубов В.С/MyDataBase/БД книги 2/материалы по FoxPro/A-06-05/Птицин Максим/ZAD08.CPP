#include<conio.h>
#include<iostream.h>
long long nod(long long  a,long long b)
   {
   if (a<b) return nod(b,a);
   if (b==0) return a;
   return nod(b,a-(a/b)*b);
   }

long long nok(long long a, long long b)
   {
   return (a*b/nod(a,b));
   }

void Zad08(void)
   {
   clrscr();
   cout<<"Nahozdenie naibolshego obshego delitelya.\n";
   cout<<"Naimenshego obshego kratnogo.\n";
   cout<<"Vedite 2 chisla:\n";
   long long a,b;
   cout<<"a= "; cin>>a;
   cout<<"b= "; cin>>b;
   long long NODab=nod(a,b);
   cout<<"NOD(a,b)= "<<NODab;
   long long NOKab=nok(a,b);
   cout<<"\nNOK(a,b)= "<<NOKab; 
   }