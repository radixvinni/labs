// Zadacha 1 po matlogike
//var 18
#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
void Zad01(void)
{
	clrscr();
	int a, b, q1, q2, r1, r2;
	//a=118, b=11
	//a==b*q1+r1, -a==b*q2+r2, 0<=r1,r2<b
	cout<<"Zadacha 1 po matlogike\na=b*q1+r1 and -a=b*q2+r1\n";
	cout<<"Enter a and b: \n";
	cout<<"a= "; cin>>a;
	cout<<"b= "; cin>>b;
	q1 = (a / b);
	r1 = fmod(a, b);
	q2 = -a / b;
	r2 = -fmod(a, b);
	if (r2<0)
	{
		--q2;
		r2=r2+b;
	}
	cout<<"q1= "<<q1<<"\nr1= "<<r1;
	cout<<"\nq2= "<<q2<<"\nr2= "<<r2;
	cout<<"\nEND";
}