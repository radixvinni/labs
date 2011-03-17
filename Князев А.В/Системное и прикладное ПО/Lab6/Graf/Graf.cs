using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace Graf
{
    struct Холст 
	{
		private int mx,my,cx,cy;
        private int n,r,R;
        public double step;
		private Graphics g;
		public Pen p;
		private SolidBrush b;
        private Font f;

        public Холст(int n, int mx, int my, Graphics g, Pen p, SolidBrush b, Font f)
        {
            this.n = n;
            this.mx = mx;
            this.my = my;
            this.cx = mx / 2;
            this.cy = my / 2;
            int rr=(cx<cy?cx:cy);
            int bb=(rr/n)>>1;
            this.R = (int)(rr / (1 + Math.Sin(Math.PI / n)));
            this.r = rr - R - bb;
			if(r<0)r=-r;
            this.step = 2 * Math.PI / n;
            this.b = b;
            this.f = f;
            this.g = g;
            this.p = p;
        }
        private void линия(int x,int y,int xx,int yy)
        {
			g.DrawLine(p,x,20+y,xx,20+yy);
        }
        public void соединить_вершины(int i,int j)
        {
            int x = (int)(cx + R * Math.Cos(step * j)), y = (int)(cy + R * Math.Sin(step * j));
            int xx = (int)(cx + R * Math.Cos(step * i)), yy = (int)(cy + R * Math.Sin(step * i));
            линия(x,y,xx,yy);
        }
        public void вершина(int j)
        {
                int x=(int)(cx+R*Math.Cos(step*j)), y=(int)(cy+R*Math.Sin(step*j));
				Color c = b.Color;
				g.FillEllipse(b,x-r,20+y-r,2*r,2*r);
				g.DrawEllipse(p,x-r,20+y-r,2*r,2*r);
				String s= Convert.ToString(j);
				int dx=5*(j>9?2:1), dy=f.Height;
				b.Color = Color.Black;
				g.DrawString(s,f,b,x-dx,20+y-dy);
				b.Color=c;
        }
	}
    class Граф
    {
        private bool[,] матрицасмежности=new bool[100,100];  //use: contact[max(i,j),min(i,j)]
        public int количество_ребер;
        
        public int количество_вершин;
        public void Очистить() {for(int i =0;i<100;++i) for(int j =0;j<100;++j) матрицасмежности[i,j]=false; количество_вершин=0;количество_ребер=0;}
		public Граф() { Очистить(); }
        public void НовоеРебро(int a, int b) { матрицасмежности[a>b?a:b,a>b?b:a]=true;количество_ребер++; }
        public bool ЕстьРебро(int a, int b){ return матрицасмежности[a>b?a:b,a>b?b:a]; }
        public int НоваяВершина() {return количество_вершин++;}
        /*public void fload(char[255] filename)
        {
                FILE* f = fopen(filename,"rb");
                if(!f)return;
                fread(contact,10000,1,f);
                fread(&n,sizeof(n),1,f);
                fread(&m,sizeof(m),1,f);
                fclose(f);
        }
        public void fsave(char[255] filename)
        {
                FILE* f = fopen(filename,"wb");
                if(!f)return;
                fwrite(contact,10000,1,f);
                fwrite(&n,sizeof(n),1,f);
                fwrite(&m,sizeof(m),1,f);
                fclose(f);
        }*/
        // Найти самый длинный цикл через вершину а и ребро b c
        private int[] пройдено = new int[100]; // temp array
        public bool поиск_в_глубину(Холст холст,int a, int b, int c, int d)
        {
                int максимальная_длина=0;
                for(int i=0;i<100;i++)
                        пройдено[i]=-1;
                int[] очередь = new int[100];
                пройдено[a]=-2;
                int текущая_вершина=a;
                очередь[0]=a;
                int текущая_длина=1;
                int следующая_вершина=0;
                int[] цикл = new int[1];
				bool ребро_пройдено=false;
                do
                {
                        if(следующая_вершина<количество_вершин)
                        for(;следующая_вершина<количество_вершин;следующая_вершина++)
                        if(ЕстьРебро(текущая_вершина,следующая_вершина)) break;
                        if(следующая_вершина<количество_вершин)
                        {
                                if(пройдено[следующая_вершина]==-1)
                                {
                                        // шаг вперед
                                        очередь[текущая_длина++]=текущая_вершина;
                                        пройдено[следующая_вершина]=текущая_вершина;
                                        текущая_вершина=следующая_вершина;
                                        следующая_вершина=-1;
                                        if (текущая_вершина == b && пройдено[c] == -1 && ЕстьРебро(b,c)) 
                                        { 
                                            ребро_пройдено = true; 
                                            очередь[текущая_длина++] = текущая_вершина; 
                                            пройдено[c] = текущая_вершина; 
                                            текущая_вершина = c; 
                                        }
                                        else
                                            if (текущая_вершина == c && пройдено[b] == -1 && ЕстьРебро(c, b)) 
                                            { 
                                                ребро_пройдено = true; 
                                                очередь[текущая_длина++] = текущая_вершина; 
                                                пройдено[b] = текущая_вершина; текущая_вершина = b; 
                                            }
                                }
								if(следующая_вершина==a&&ребро_пройдено&&максимальная_длина<текущая_длина)
                                {
                                    максимальная_длина = текущая_длина;
                                    
                                    цикл = new int[максимальная_длина + 1];
                                    int s=0;
									for(int l=текущая_вершина;l!=-2;l=пройдено[l])
									{
                                        цикл[s] = l;
                                        s++;
									}
                                    цикл[s] = текущая_вершина;
								}
                                следующая_вершина++;
                        }
                        else //ничего не найдено
                        {
                                // шаг назад
                                пройдено[текущая_вершина]=-1;
                                следующая_вершина=текущая_вершина+1;
                                if(текущая_вершина==c&&очередь[текущая_длина-1]==b||текущая_вершина==b&&очередь[текущая_длина-1]==c)
								{
									ребро_пройдено=false;
								}
								текущая_вершина=очередь[--текущая_длина];
                        }
                }
                while (текущая_длина>0);
                if (максимальная_длина == 0) return false;
                for (int l = 0; l < максимальная_длина; l++)
                {
                    холст.соединить_вершины(цикл[l], цикл[l+1]);
                }										
                return true;
        }
    }
}
