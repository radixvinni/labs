#include <conio.h>
#include <iostream.h>
#include <math.h>
void Zad06(void)
   {
   clrscr();
   cout<<"Vvedite chislo v desyatichnoy sisteme izmereniya.\n";
   cout<<"n= ";
   long n=0;
   cin>>n;
   while (1)
   {
   clrscr();
   cout<<"Vvedite chislo v desyatichnoy sisteme izmereniya.\n";
   cout<<"n= "<<n<<endl;
   cout<<"V kakoy sisteme izmeremiya vu hotite uznat, skoko tsifr zaymet chislo?\n";
   cout<<"e= ";
   int e=0;
   cin>>e;
   int c=0;
   c=log(n)/log(e);
   c++;
   cout<<"V sisteme "<<e<<" chislo desyatichnoe chislo "<<n<<" zaymet\n";
   cout<<c<<" tsifr.\n"; repError:
   cout<<"\nPovtorit zadachu dlya chisla "<<n<<"?[y/n]: ";
   char rep;
   rep=getch();
   cout<<rep;
   if (rep=='n')
     goto repno;
   if((rep!='n')&&(rep!='y'))
     goto repError;
   }         repno:

   }