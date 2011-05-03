//Zadacha 7 po matlogike
//Kol-vo deliteley. I razlozenie na prostue mnoziteli

#include <conio.h>
#include <iostream.h>
void Zad07(void)
   {
   clrscr();
   cout<<"Vvedite chislo.\n";
   long n=0;
   cout<<"n= ";
   cin>>n;
 int a[2][255]; //massiv kol-va mnoziteley
 int na=0;
   for(int i=0;i<2;i++)
      for(int j=0;j<255;j++)
	 a[i][j]=0;
   i=2;
   a[0][0]=2;
   cout<<"Prostue mnoziteli, chisla "<<n<<": \n";
   while (n!=1)
      {
      if ((n-(n/i)*i)==0)
	 {
	 if (a[0][na]==i)
	    {
	    a[1][na]++;
	    } else
	    {
	    na++;
	    a[0][na]=i;
	    a[1][na]++;
	    };
	 cout<<i<<" ";
	 n=n/i;
	 } else i++;
      };
   cout<<endl;
   cout<<"Chislo deliteley chisla "<<n<<":"<<endl;
   cout<<"f(n)= ";
   for (i=0; i<=na;i++)
      {
      if (a[1][i]!=0)
	 cout<<"("<<a[1][i]<<"+1)";
      };
   cout<<"= ";
   int s=1;
   for (i=0;i<=na;i++)
      s*=(a[1][i]+1);
   cout<<s;
   }