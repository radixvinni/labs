using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Graf
{
    public partial class Form1 : Form
    {
        int temp;
        Граф граф=new Граф();
        Dialog1 dialog1=new Dialog1();

        public Form1()
        {
            InitializeComponent();
        }

        private void оПрограммеToolStripMenuItem_Click(object sender, EventArgs e)
        {
        }

        private void файлToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void выходToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void заданиеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Найти самый длинный цикл в графе, проходящий через заданную вершину и заданное ребро.", "Задание");
        }

        private void оПрограммеToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Лабораторная работа №6\r\nРабота с графом на С#\r\n  выполнил Винников Александр\r\n  группа А-14-07", "О программе");
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            int mx = this.Width, my = this.Height;
            int cx = mx / 2, cy = my / 2;
            int rr = (cx < cy ? cx : cy);
            int n = граф.количество_вершин;
            if (n==0) { граф.НоваяВершина(); this.Refresh(); return; }
            int b = (rr / n) >> 1;
            int R = (int)(rr / (1 + Math.Sin(Math.PI / n)));
            int r = rr - R - b;
            double step = 2 * Math.PI / n;
            double a = 0;
            int res = -1;
            int X = e.X, Y = e.Y;
            for (int j = 0; j < n; j++)
            {
                int x = (int)(cx + R * Math.Cos(a)), y = (int)(cy + R * Math.Sin(a));
                if ((X - x) * (X - x) + (Y - y) * (Y - y) <= r * r)
                    res = j;
                a += step;
            }
            if (res == -1) { граф.НоваяВершина(); this.Refresh(); }
            temp = res;

        }

        private void Form1_MouseUp(object sender, MouseEventArgs e)
        {
            int mx = this.Width, my = this.Height;
            int cx = mx / 2, cy = my / 2;
            int rr = (cx < cy ? cx : cy);
            int n = граф.количество_вершин;
            if (n == 0) { граф.НоваяВершина(); this.Refresh(); return; }
            int b = (rr / n) >> 1;
            int R = (int)(rr / (1 + Math.Sin(Math.PI / n)));
            int r = rr - R - b;
            double step = 2 * Math.PI / n;
            double a = 0;
            int res = -1;
            int X = e.X, Y = e.Y;
            for (int j = 0; j < n; j++)
            {
                int x = (int)(cx + R * Math.Cos(a)), y = (int)(cy + R * Math.Sin(a));
                if ((X - x) * (X - x) + (Y - y) * (Y - y) <= r * r)
                    res = j;
                a += step;
            }
            if (res != -1 && temp != -1) граф.НовоеРебро(res, temp);
            this.Refresh(); 
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
			 if (граф.количество_вершин==0) return;

             Холст dr = new Холст(граф.количество_вершин, this.Width, this.Height - 70, e.Graphics, new Pen(Color.Black), new SolidBrush(this.BackColor), this.Font);

			 double a=0;
			 for(int j=0;j<граф.количество_вершин;j++)
			 {
                for (int k=0;k<граф.количество_вершин;k++)
                if(граф.ЕстьРебро(j,k))
                    dr.соединить_вершины(j,k);
                a+=dr.step;
			 }
			 if(dialog1.dA!=-1&&dialog1.dB!=-1&&dialog1.dC!=-1)
			 {  
				dr.p.Width=4;
				if(граф.поиск_в_глубину(dr,dialog1.dA,dialog1.dB,dialog1.dC,dialog1.dD))
				{
					this.statusStrip1.Items[0].Text="Цикл найден.";
				}
                else this.statusStrip1.Items[0].Text = "Нет таких циклов.";
				dr.p.Width=1;
			 }
			 for(int j=0;j<граф.количество_вершин;j++)
                dr.вершина(j);
        }

        private void yjdsqToolStripMenuItem_Click(object sender, EventArgs e)
        {
            граф.Очистить();
            dialog1.dA = -1;
            dialog1.dB = -1;
            dialog1.dC = -1;
            this.Refresh();
        }

        private void задатьДанныеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            dialog1.grafn = граф.количество_вершин;
            if( dialog1.ShowDialog() == DialogResult.Cancel ) return;
            this.Refresh();
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            Refresh();
        }
    }
}
