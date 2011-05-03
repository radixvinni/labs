// Zadacha 1 po matlogike
//var 18
#include <conio.h>
#include <iostream.h>
#include <math.h>
void Zad03(void)
   {
   int qb,qn,tp,t,i,d,h;
   char eCh[255];
   clrscr(); Mstart03:
   cout<<"Zadacha 3 po MatLogike\n";
   cout<<"Vvedite desyatichnoe chislo: ";
   cin>>d;
   cout<<"Vvedite razmernost h: ";
   cin>>h;
   if (d<=0)
      {
      cout<<"Chislo dolzno but bolshe nulya!\n";
      goto Mstart03;
      };
   if (h<=1)
      {
      cout<<"razmernost dolzna but bolshe 1!\n";
      goto Mstart03;
      };
   t=int(log(d)/log(h));
   qb=d;
   for(i=0;i<=t;i++)
      {
      qn=int(qb/h);
      tp=qb-qn*h;
      if (tp<10) eCh[t-i]=char(48+tp);
      else eCh[t-i]=char(55+tp);
      qb=qn;
      }
   eCh[t+1]=0;
   cout<<"Rezultat: ";
   for (i=0;i<=t;i++)
      cout<<eCh[i];
   cout<<"\nEND";
   }
