// filetest.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <fstream>
#include <conio.h> 
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	char a[10];
	char b[100];
	int n;
	float x, y, z;
	char ch;
	int points = 0, polys = 0;
	std::ifstream f1 ("file.txt");
	std::ofstream f2 ("scene.txt");
	f2<<"0 0 -200 0 0\n200 200 200\n0";
	while (!f1.eof()) 
	{
		f1>>ch;
		if(ch=='v') 
		{
			f1>>x>>y>>z;
			x=x*20;
			y=y*20;
			z=z*20;
			f2<<(int)x<<' '<<(int)y<<' '<<(int)z<<"\n";
			std::cout<<"Point("<<(int)x<<' '<<(int)y<<' '<<(int)z<<");\n";
			points++;
		}
		if(ch=='f')
		{
			n=1;
			b[0]=0;
			f1>>a;
			strcat(b," ");
			strcat(b,a);		
			while(!f1.eof())
			{
				f1>>a;
				if(a[0]=='f')
				{
					f2<<n<<b<<" 1\n";
					b[0]=0;
					n=0;
					polys++;
				}
				else
				{
					strcat(b," ");
					strcat(b,a);
					n++;
				}
				//if (f1.fail() ) break;
			}
			//f1.unget();
		}
		//std::cout<<n<<std::endl;

	}
	std::cout<<"Points : "<<points<<std::endl<<"Polygons : "<<polys;
	f1.close();
	f2.close();
	getch(); 
	return 0;
}

