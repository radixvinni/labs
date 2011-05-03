//Zadacha 2 po matlogike
//Perevod iz dvoichnoy sistemu ischisleniya v lubuyu
#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <string.h>
void Zad02(void)
     {
      clrscr();
      char bin[255]; int h; char eCh[255];
      cout<<"Zadacha 2 po MatLogike\n";
      cout<<"Vvidite binarnoe chislo: ";
      cin>>bin;
      cout<<"Vvidite razmernost h: ";
      cin>>h;
      unsigned int d=0,l,qb,qn,tp,t,i;
	     for(l=strlen(bin);l>0;l--)
		d+=(bin[l-1]-48)*pow(2,strlen(bin)-l);
	     t=log(d)/log(h);
	     qb=d;
	     for(i=0;i<=t;i++)
		{
			qn=qb/h;
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
