#include<iostream.h>
#include<conio.h>
#include"ZAD01.CPP";
#include "ZAD02.CPP";
#include "ZAD03.CPP";
#include "ZAD06.CPP";
#include "ZAD07.CPP";
#include "ZAD08.CPP";
#include "ZAD09.CPP";
#include "ZAD11.CPP";

int main(void)
   {
   int n;
   char rep;
   while (1)
      { Mstart:
      clrscr();
      cout<<"Group        : A-06-05;\n";
      cout<<"Name         : Ptitsin Maximus Ivanovich;\n";
      cout<<"Project      : Tipovoy raschet po matlogike.\n";
      cout<<"Nomera zadach:\n";
      cout<<"Vuberite nomer zadachi, ili vuberite 0 dlya vuhoda.\n";
      cout<<"01: Nahozdenie q1,q2,r1,r2 iz formul a=b*q1+r1 i -a=b*q2+r1\n";
      cout<<"02: Perevod chisel iz 02sistemu izmereniya v h\n";
      cout<<"03: Perevod chisel iz 10sistemu izmereniya v h\n";
      cout<<"06: Vuvod kol-va tsifr 10nogo chisla v sisteme izmereniya h\n";
      cout<<"07: Kol-vo deliteley. I razlozenie na prostue mnoziteli\n";
      cout<<"08: NOD(a,b) and NOK(a,b)\n";
      cout<<"09: nepreruvnaya drob dlya a/b\n";
      cout<<"11: Vuchislenie a^k(mod n)\n";
      cout<<"Vubor: ";
      cin>>n;
      switch (n)
	 {
	 case 0:
	   clrscr();
	   cout<<"Vuhod iz programmu";
	   return 0;
	 case 1:
	    Mzad01:
	    Zad01();
	    break;
	 case 2:
	    Mzad02:
	    Zad02();
	    break;
	 case 3:
	    Mzad03:
	    Zad03();
	    break;
	 case 6:
	    Mzad06:
	    Zad06();
	    break;
	 case 7:
	    Mzad07:
	    Zad07();
	    break;
	 case 8:
	    Mzad08:
	    Zad08();
	    break;
	 case 9:
	    Mzad09:
	    Zad09();
	    break;
	 case 11:
	    Mzad11:
	    Zad11();
	    break;
	 default: goto Mstart;
	 };
      rep='0';
      while ((rep!='y')&&(rep!='n'))
      {
	 cout<<"\nPovtorit "<<n<<" zadanie?[y/n]? ";
	 rep=getch();
	 cout<<rep;
      };
      if (rep=='y')
	 switch (n)
	 {
	 case 1: goto Mzad01;
	 case 2: goto Mzad02;
	 case 3: goto Mzad03;
	 case 6: goto Mzad06;
	 case 7: goto Mzad07;
	 case 8: goto Mzad08;
	 case 9: goto Mzad09;
	 case 11: goto Mzad11;
	 };
      };

   }