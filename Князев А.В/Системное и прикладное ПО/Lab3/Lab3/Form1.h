#pragma once
#include "Dialog1.h"
#include "Graf.h"
#include <vcclr.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <stdio.h>

#define M_PI 3.1415926535897932384626433832795

namespace Lab3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::Runtime::InteropServices;	

//    ref struct AbstructDrawer
//	{
		//virtual line(int,int,int,int) = 0;
		//void nodeline(int i,int j);
		//void node(int j);
//	};
ref struct Drawer //:public AbstructDrawer 
	{
		int mx,my,cx,cy;
        int n,r,R;
        double step;
		Graphics^ g;
		Pen^ p;
		SolidBrush^ b;
		Font^ f;

		Drawer(int nn,int xx,int yy):n(nn),mx(xx),my(yy)
        {
                cx=mx/2;
                cy=my/2;
                int rr=(cx<cy?cx:cy);
                int b=(rr/n)>>1;
                R= rr/(1+sin(M_PI/n));
                r= rr-R-b;
				if(r<0)r=-r;
                step=2*M_PI/n;
        }
        void line(int x,int y,int xx,int yy)
        {
			g->DrawLine(p,x,20+y,xx,20+yy);
        }
        void nodeline(int i,int j)
        {
                int x=cx+R*cos(step*j), y=cy+R*sin(step*j);
                int xx=cx+R*cos(step*i), yy=cy+R*sin(step*i);
                line(x,y,xx,20+yy);
        }
        void node(int j)
        {
                int x=cx+R*cos(step*j), y=cy+R*sin(step*j);
				Color c = b->Color;
				g->FillEllipse(b,x-r,20+y-r,2*r,2*r);
				g->DrawEllipse(p,x-r,20+y-r,2*r,2*r);
				System::String^ s= Convert::ToString(j);
				int dx=5*(j>9?2:1), dy=f->Height;
				b->Color = Color::Black;
				g->DrawString(s,f,b,x-dx,20+y-dy);
				b->Color=c;
        }
	};
class Graf
{
        bool contact[100][100];  //use: contact[max(i,j)][min(i,j)]
        unsigned m;
        public:
        unsigned n;
        Graf() : n(0), m(0) { memset(contact,0,10000); }
        Graf(Graf &a) : n(a.n), m(a.m) { memcpy(contact,a.contact,10000); }
        ~Graf() {}
		void Clear() {memset(contact,0,10000);n=0,m=0;}
		void setAB(unsigned a, unsigned b) { contact[a>b?a:b][a>b?b:a]=true;m++; }
        bool touchingAB(unsigned a, unsigned b){ return contact[a>b?a:b][a>b?b:a]; }
        unsigned newA() {return n++;}
        void fload(char filename[255])
        {
                FILE* f = fopen(filename,"rb");
                if(!f)return;
                fread(contact,10000,1,f);
                fread(&n,sizeof(n),1,f);
                fread(&m,sizeof(m),1,f);
                fclose(f);
        }
        void fsave(char filename[255])
        {
                FILE* f = fopen(filename,"wb");
                if(!f)return;
                fwrite(contact,10000,1,f);
                fwrite(&n,sizeof(n),1,f);
                fwrite(&m,sizeof(m),1,f);
                fclose(f);
        }
        int R[101]; // temp array
        bool search(Drawer^ dr,unsigned a, unsigned b, unsigned c, unsigned d)
        {
                int kk=0;
                for(int i=0;i<101;i++)
                        R[i]=-1;
                unsigned lifo[101];
                R[a]=-2;
                unsigned t=a;
                lifo[0]=a;
                int k=1;
                int j=0;
				//bool wasB=false, wasCD=false;
                do
                {
                        if(j<n)
                        for(;j<n;j++)
                        if(touchingAB(t,j)) break;
                        if(j<n)
                        {
                                if(R[j]==-1)
                                {
                                        //found. step forward.
                                        lifo[k++]=t;
                                        R[j]=t;
                                        t=j;
                                        j=-1;
										//if(t==d){wasCD=true; lifo[k++]=t;R[c]=t;t=c;} else
										//if(t==c){wasCD=true; lifo[k++]=t;R[d]=t;t=d;}
										//if(t==b) wasB=true;
                                }
								if(j==a)
                                {
									int m=j;
									//R[j]=t;//j==a
									bool wasB=false, wasCD=false;
									for(int l=t;R[l]!=-2;l=R[l])
									{
									if(m==d&&l==c)wasCD=true;
									if(m==c&&l==d)wasCD=true;
									if(l==b)wasB=true;
									m=l;
									}
									if(wasB&&wasCD)
									{
										dr->nodeline(t,a);
										for(int l=t;R[l]!=-2;l=R[l])
										{
											dr->nodeline(l,R[l]);
										}	
										return true;
									}
								}
                                j++;
                        }
                        else
                        {
                                //nothing found. step back.
                                R[t]=-1;
                                j=t+1;
                                //if(t==c&&lifo[k-1]==d||t==d&&lifo[k-1]==c)
								//{
								//	wasCD=false;
								//}
								//if(t==b) wasB=false;
								t=lifo[--k];
                        }
                }
                while (k>0);
                return false;
        }
};

	/// <summary>
	/// Сводка для Form1
	///
	/// Внимание! При изменении имени этого класса необходимо также изменить
	///          свойство имени файла ресурсов ("Resource File Name") для средства компиляции управляемого ресурса,
	///          связанного со всеми файлами с расширением .resx, от которых зависит данный класс. В противном случае,
	///          конструкторы не смогут правильно работать с локализованными
	///          ресурсами, сопоставленными данной форме.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			dialog1 = (gcnew Dialog1());
			graf = new Graf();
		}

	protected:
		int temp;
		Graf* graf;
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			delete graf;
			if (components)
			{
				delete components;
			}
		}
	protected: 
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  файлToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem3;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem4;
	private: System::Windows::Forms::ToolStripMenuItem^  правкаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  справкаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem5;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem6;
	private: System::Windows::Forms::ToolStripMenuItem^  ToolStripMenuItem7;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
			 
	private: Dialog1^ dialog1;
	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->файлToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->ToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->ToolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->правкаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItem5 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->ToolStripMenuItem6 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->справкаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ToolStripMenuItem7 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->statusStrip1->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->toolStripStatusLabel1});
			this->statusStrip1->Location = System::Drawing::Point(0, 251);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(314, 22);
			this->statusStrip1->TabIndex = 0;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(78, 17);
			this->toolStripStatusLabel1->Text = L"Задайте граф";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->файлToolStripMenuItem, 
				this->правкаToolStripMenuItem, this->справкаToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(314, 24);
			this->menuStrip1->TabIndex = 1;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// файлToolStripMenuItem
			// 
			this->файлToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->ToolStripMenuItem1, 
				this->toolStripSeparator1, this->ToolStripMenuItem2, this->ToolStripMenuItem3, this->toolStripSeparator2, this->ToolStripMenuItem4});
			this->файлToolStripMenuItem->Name = L"файлToolStripMenuItem";
			this->файлToolStripMenuItem->Size = System::Drawing::Size(45, 20);
			this->файлToolStripMenuItem->Text = L"Файл";
			// 
			// ToolStripMenuItem1
			// 
			this->ToolStripMenuItem1->Name = L"ToolStripMenuItem1";
			this->ToolStripMenuItem1->Size = System::Drawing::Size(152, 22);
			this->ToolStripMenuItem1->Text = L"&Новый граф";
			this->ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItem1_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(149, 6);
			// 
			// ToolStripMenuItem2
			// 
			this->ToolStripMenuItem2->Name = L"ToolStripMenuItem2";
			this->ToolStripMenuItem2->Size = System::Drawing::Size(152, 22);
			this->ToolStripMenuItem2->Text = L"&Открыть...";
			this->ToolStripMenuItem2->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItem2_Click);
			// 
			// ToolStripMenuItem3
			// 
			this->ToolStripMenuItem3->Name = L"ToolStripMenuItem3";
			this->ToolStripMenuItem3->Size = System::Drawing::Size(152, 22);
			this->ToolStripMenuItem3->Text = L"&Сохранить";
			this->ToolStripMenuItem3->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItem3_Click);
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(149, 6);
			// 
			// ToolStripMenuItem4
			// 
			this->ToolStripMenuItem4->Name = L"ToolStripMenuItem4";
			this->ToolStripMenuItem4->Size = System::Drawing::Size(152, 22);
			this->ToolStripMenuItem4->Text = L"&Выход";
			this->ToolStripMenuItem4->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItem4_Click);
			// 
			// правкаToolStripMenuItem
			// 
			this->правкаToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->ToolStripMenuItem5, 
				this->toolStripSeparator3, this->ToolStripMenuItem6});
			this->правкаToolStripMenuItem->Name = L"правкаToolStripMenuItem";
			this->правкаToolStripMenuItem->Size = System::Drawing::Size(56, 20);
			this->правкаToolStripMenuItem->Text = L"Правка";
			// 
			// ToolStripMenuItem5
			// 
			this->ToolStripMenuItem5->Name = L"ToolStripMenuItem5";
			this->ToolStripMenuItem5->Size = System::Drawing::Size(176, 22);
			this->ToolStripMenuItem5->Text = L"Новая &вершина";
			this->ToolStripMenuItem5->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItem5_Click);
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(173, 6);
			// 
			// ToolStripMenuItem6
			// 
			this->ToolStripMenuItem6->Name = L"ToolStripMenuItem6";
			this->ToolStripMenuItem6->Size = System::Drawing::Size(176, 22);
			this->ToolStripMenuItem6->Text = L"Задать &данные...";
			this->ToolStripMenuItem6->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItem6_Click);
			// 
			// справкаToolStripMenuItem
			// 
			this->справкаToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->ToolStripMenuItem7});
			this->справкаToolStripMenuItem->Name = L"справкаToolStripMenuItem";
			this->справкаToolStripMenuItem->Size = System::Drawing::Size(62, 20);
			this->справкаToolStripMenuItem->Text = L"Справка";
			// 
			// ToolStripMenuItem7
			// 
			this->ToolStripMenuItem7->Name = L"ToolStripMenuItem7";
			this->ToolStripMenuItem7->Size = System::Drawing::Size(161, 22);
			this->ToolStripMenuItem7->Text = L"&О программе...";
			this->ToolStripMenuItem7->Click += gcnew System::EventHandler(this, &Form1::ToolStripMenuItem7_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->DefaultExt = L"graf";
			this->openFileDialog1->FileName = L"";
			this->openFileDialog1->Filter = L"Graf|*.graf";
			// 
			// saveFileDialog1
			// 
			this->saveFileDialog1->DefaultExt = L"graf";
			this->saveFileDialog1->Filter = L"Graf|*.graf";
			this->saveFileDialog1->OverwritePrompt = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(314, 273);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Найти цикл, проходящий через две заданные вершины и ребро";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->Resize += gcnew System::EventHandler(this,&Form1::Form1_Resize);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseDown);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseUp);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void toolStripDropDownButton1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void toolStripDropDownButton2_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void ToolStripMenuItem6_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 //grafn=graf->n;
			 dialog1->grafn=graf->n;
			 dialog1->ShowDialog(this);
			 this->Refresh();
		 }
private: System::Void ToolStripMenuItem4_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 this->Close();
		 }
private: System::Void ToolStripMenuItem7_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 System::Windows::Forms::MessageBox::Show("Лабораторная работа №3 по дисциплине\r\nСистемное и прикладное програмное обеспечение\r\n\tвыполнил Винннков Александр\r\n\tгруппа А-14-07","О программе",MessageBoxButtons::OK);
		 }
private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) 
		 {
			 this->Refresh();
		 }
private: System::Void Form1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
		int mx=this->Width, my=this->Height;
        int cx=mx/2, cy=my/2;
        int rr=(cx<cy?cx:cy);
		int n=graf->n;
        if(!n){graf->newA();this->Refresh();return;}
        int b=(rr/n)>>1;
        int R= rr/(1+sin(M_PI/n));
        int r= rr-R-b;
        double step=2*M_PI/n;
        double a=0;
        int res=-1;
		int X=e->X, Y=e->Y;
        for(int j=0;j<n;j++)
        {
                int x=cx+R*cos(a), y=cy+R*sin(a);
                if((X-x)*(X-x)+(Y-y)*(Y-y)<=r*r)
                res=j;
                a+=step;
        }
		if(res==-1) {graf->newA();this->Refresh();}
        temp=res;
		 }
private: System::Void Form1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
		 {
		int mx=this->Width, my=this->Height;
        int cx=mx/2, cy=my/2;
        int rr=(cx<cy?cx:cy);
        int n=graf->n;
        if(!n)return;
        int b=(rr/n)>>1;
        int R= rr/(1+sin(M_PI/n));
        int r= rr-R-b;
        double step=2*M_PI/n;
        double a=0;
        int res=-1;
		int X=e->X, Y=e->Y;
        for(int j=0;j<n;j++)
        {
                int x=cx+R*cos(a), y=cy+R*sin(a);
                if((X-x)*(X-x)+(Y-y)*(Y-y)<=r*r)
                res=j;
                a+=step;
        }
        if(res!=-1&&temp!=-1) graf->setAB(res,temp);
		this->Refresh(); 
		 }
private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) 
		 {
			 if (!graf->n) return;
			 
			 Drawer ^dr = gcnew Drawer(graf->n,this->Width,this->Height-70);
			 //void (Drawer::*lnp)(int,int);
			 //lnp = &Drawer::nodeline;
//			 LNPROC lnp;
//			 lnp = &dr->nodeline;
			 //void* lnptr = &dr;
			 //lnptr = lnptr + (void*)lnp;
			 Graphics ^g = e->Graphics;
			 dr->p = gcnew Pen(Color::Black);
			 dr->f = this->Font;
			 dr->b = gcnew SolidBrush(this->BackColor);
			 dr->g = g;

			 double step=2*M_PI/graf->n;
			 double a=0;
			 for(int j=0;j<graf->n;j++)
			 {
                int x=dr->cx+dr->R*cos(a), y=dr->cy+dr->R*sin(a);
                for (int k=0;k<graf->n;k++)
                if(graf->touchingAB(j,k))
                        dr->line(dr->cx+dr->R*cos(k*step),dr->cy+dr->R*sin(k*step),x,y);
                a+=step;
			 }
			 if(dialog1->dA!=-1&&dialog1->dB!=-1&&dialog1->dC!=-1&&dialog1->dD!=-1)
			 {  
				dr->p->Width=4;
				if(!graf->search(dr,dialog1->dA,dialog1->dB,dialog1->dC,dialog1->dD))
				{
					this->statusStrip1->Text="Цикл найден.";
				}
				else this->statusStrip1->Text="Нет таких циклов.";
				dr->p->Width=1;
			 }
			 for(int j=0;j<graf->n;j++)
                dr->node(j);
		 }
private: System::Void ToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 graf->Clear();this->Refresh();
		 }
private: System::Void ToolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(openFileDialog1->ShowDialog(this)==System::Windows::Forms::DialogResult::OK)
			 {
				 char* str = (char*)(void*)Marshal::StringToHGlobalAnsi(openFileDialog1->FileName);
				 graf->fload(str);
				 //Marshal::FreeHGlobal(str);
			 }
			 this->Refresh();
		 }
private: System::Void ToolStripMenuItem3_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 if(saveFileDialog1->ShowDialog(this)==System::Windows::Forms::DialogResult::OK)
			 {
				 char* str = (char*)(void*)Marshal::StringToHGlobalAnsi(openFileDialog1->FileName);
				 graf->fsave(str);
				 //Marshal::FreeHGlobal(str);
			 }
			 this->Refresh();
		 }
private: System::Void ToolStripMenuItem5_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 graf->newA();this->Refresh();
		 }
};
}

