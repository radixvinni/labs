#include <iostream>
#include <cmath>
#include <fstream>

#pragma pack(push)
#pragma pack(1)
struct BMPHEDAER {
		char 	signature[2];
		int	filesize, reserved, headersize, dibheadersize, width, height;
		unsigned short	planes, bitsperpixel;
		int	compression, imagesize, therest[17], colortable[3];
		char rest[1078-118];
	} header={
		'B','M', 640*480+0x436, 0, 0x436, 0x28, 640, 480, 1, 8, 0, 640*480, {0, 0, 0, 0, 0, 0x800000, 0x8000, 
		0x808000, 0x80, 0x800080, 0x8080, 0x808080, 0xC0C0C0, 0xFF00000, 0xFF00, 0xFFFF00, 0xFF}, {0xFF00FF,0xFFFF, 0xFFFFFF}
	};
#pragma pack(pop)

class BMP
{
public:
	unsigned char data[640][480];
	BMP()
	{
		for(int i= 0; i<640; i++)
			for(int j= 0; j<480; j++)
				data[i][j] = 15;
	}

	void save(const std::string str="");

	void line(int x1, int y, int length, int color)
	{
		for(int i=x1;i<x1+length;i++)
			data[i][y] =  color;
	}

	void point(int x, int y, int color)
	{
		data[x][y] = color;
	}
	 
	void rectangle(int x1, int x2, int y1, int y2,int color)
	{
		for(int i=x1;i<x2;i++)
			data[i][y1] =  color;
				 
		for(int y=y1;y<y2;y++)
			data[x1][y] =  color;

		for(int i=x1;i<x2;i++)
			data[i][y2] =  color;

		for(int y=y1;y<y2;y++)
			data[x2][y] =  color;
					 
	}
	void round(int x1, int y1, int length,int color)
	{
		for(double i=0;i<2*M_PI;i+=0.01)
		{
			int x=x1+length*cos(i);
			int y=y1+length*sin(i);
			data[x][y] =  color;
		}
	}
	 
};
 
void BMP::save(const std::string str)
{
	int i = 0;
 
	std::ofstream f(str.c_str());
 
	f.write((char*)&header, sizeof(header));
 
	for(int i= 0; i<480; i++)
			for(int j= 0; j<640; j++)
				f<<data[j][i];
 
	f.close();
}
 
int main()
{
	BMP bitmap;
 
	bitmap.line(100, 150, 150, 12);
	bitmap.rectangle(200, 400, 200, 300,12);
	bitmap.round(450, 350, 100,1);
	bitmap.save("renk.bmp");
 
	return 0;
}
