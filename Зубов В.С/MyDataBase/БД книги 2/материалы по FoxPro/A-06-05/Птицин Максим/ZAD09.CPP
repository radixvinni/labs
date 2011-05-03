#include<conio.h>
#include<iostream.h>
void Zad09(void)
   {
   clrscr();
   cout<<"Nepreruvnaya drob dlya  a / b.\n";MerrorVVD:
   cout<<"a= ";
   long a;
   cin>>a;
   cout<<"b= ";
   long b;
   cin>>b;
   if (a<b)
      {
      cout<<"oshibka vvoda a i b:a<b.\nPovtorite vvod, a>b:\n";
      goto MerrorVVD;
      };
   cout<<"a/b=";
   long d,ost;
   int skob=0;
   while (a-(a/b)*b)
      {
      d=a/b;
      ost=a-d*b;
      cout<<"("<<d<<"+1/";
      skob++;
      a=b;
      b=ost;
      };
   cout<<a/b;
   for(int i=0; i<skob;i++)
      cout<<")";
   }