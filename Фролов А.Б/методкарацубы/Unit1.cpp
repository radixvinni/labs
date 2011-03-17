//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"

#include <string.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        n=0;
}
//---------------------------------------------------------------------------
struct cell
{
        int base;
        int degr;
        unsigned char d[10];
        int dn;
        unsigned char addr[30];
        int addrn;
        unsigned char exc;
        cell* next;
};//56 bytes
void expand(cell* &c)
{
        if (c==0)return;
        if (c->degr==2) return;
        if ((c->degr & 3) == 0)
        {
                c->degr=c->degr>>1;
                cell* p = new cell;
                p->base=c->base+c->degr/2;
                p->degr=c->degr;
                for(int i=0;i<c->dn;i++)
                        p->d[i]=c->d[i];
                for(int i=0;i<c->addrn;i++)
                {
                        p->addr[i]=c->addr[i]+c->degr/2;
                        p->addr[i+c->addrn]=c->addr[i]+c->degr;
                }
                p->dn=c->dn;
                p->addrn=2*c->addrn;
                p->exc=c->exc;

                cell* t = new cell;
                t->base=c->base;
                t->degr=c->degr;
                for(int i=0;i<c->dn;i++)
                        t->d[i]=c->d[i];
                for(int i=0;i<c->addrn;i++)
                {
                        t->addr[i]=c->addr[i];
                        t->addr[i+c->addrn]=c->addr[i]+c->degr/2;
                }
                t->dn=c->dn;
                t->addrn=2*c->addrn;
                t->exc=0;

                c->d[c->dn]=c->degr/2;
                c->dn=c->dn+1;
                //c->exc=0;
                for(int i=0;i<c->addrn;i++)
                        c->addr[i]=c->addr[i]+c->degr/2;
                expand(c);
                p->next=c;
                expand(p);
                t->next=p;
                expand(t);
                c=t;
                return;
        }
        if ((c->degr & 1) == 1) return; // вообще это ошибка
        // выполн€ем добавление нул€ в конец.
        // схема будет така€:
        //  [0;0]6   //  [0;0]4  //  [2;2]2  //  [0.2;0,2]2  //  [(0.2).1;(0.2),1]2 //  [1;1]2
        //  a b c   //   0 2    //   2 4    //   2 3        //   3 4               //    3
        // короче - первое слагаемое (degr+2)/2 второе (degr-2)/2 третье - с исключением слагаемого
                int a = (c->degr-2)>>1;
                c->degr=(c->degr+2)>>1;
                cell* p = new cell;
                //p->next=c;
                p->base=c->base+c->degr/2;
                p->degr=a;
                for(int i=0;i<c->dn;i++)
                        p->d[i]=c->d[i];
                for(int i=0;i<c->addrn;i++)
                {
                        p->addr[i]=c->addr[i]+c->degr/2;
                        p->addr[i+c->addrn]=c->addr[i]+c->degr;
                }
                p->dn=c->dn;
                p->addrn=2*c->addrn;
                p->exc=c->exc;
                //expand(p);

                cell* t = new cell;
                //t->next=p;
                t->base=c->base;
                t->degr=c->degr;
                for(int i=0;i<c->dn;i++)
                        t->d[i]=c->d[i];
                for(int i=0;i<c->addrn;i++)
                {
                        t->addr[i]=c->addr[i];
                        t->addr[i+c->addrn]=c->addr[i]+c->degr/2;
                }
                t->dn=c->dn;
                t->addrn=2*c->addrn;
                t->exc=0;
                //expand(t);

                c->d[c->dn]=c->degr/2;
                c->dn=c->dn+1;
                c->exc=c->degr-1;
                for(int i=0;i<c->addrn;i++)
                        c->addr[i]=c->addr[i]+c->degr/2;
                expand(c);
                p->next=c;
                expand(p);
                t->next=p;
                expand(t);
                c=t;
}
void outd(int n,int base,cell* p,AnsiString &s,AnsiString del)
{
        if(n<p->dn)
        {
                s=s+"(";
                outd(n+1,base,p,s,del);
                if(p->exc!=base+p->d[p->dn-n-1])
                {
                        s=s+del;
                        outd(n+1,base+p->d[p->dn-n-1],p,s,del);
                }
                s=s+")";
        }
        else { s=s+IntToStr(base); return; }
}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
                Repaint();
                int x=10;
                int y=40;

                cell* f = new cell;
                f->base=0;
                f->degr=StrToInt(Edit1->Text);
                f->d[0]=0;
                f->addr[0]=0;
                f->next=0;
                f->dn=0;
                f->addrn=1;
                f->exc=0;
                expand(f);

                //Edit2->Text="<style>.w{width:70px}.b td{border:1px solid black}.b{display:inline-block}</style>";
                //Edit2->Text=Edit2->Text+"<table><tr><td class='w' valign=top>";
                Edit2->Text="";


                AnsiString s1 = "[0;0]";
                AnsiString s2 = "a b c";
                Canvas->Font->Size=12;
                int dx = Canvas->TextWidth(s1);
                int dy = Canvas->TextHeight(s1);
                Canvas->Rectangle(x,y,x+30+dx,y+6+2*dy);
                Canvas->TextOutA(x+10,y+2,s1);
                Canvas->Font->Size=6;
                Canvas->TextOutA(x+10+dx,y+10,Edit1->Text);
                Canvas->Font->Size=12;
                Canvas->TextOutA(x+10,y+4+dy,s2);
                Canvas->MoveTo(x,y+dy+4);
                Canvas->LineTo(x+30+dx,y+dy+4);

                //Edit2->Text=Edit2->Text+"<table class='b'><tr><td>[0,0]<sub>"+Edit1->Text+"</sub></td></tr><tr><td>a b c</td></tr></table>";
                //Edit2->Text=Edit2->Text+"<table class='b'><tr><td>=</td></tr><tr><td>&nbsp;</td></tr></table>";
                //Edit2->Text=Edit2->Text+"</td><td>";
//                Edit2->Text=Edit2->Text+"\\begin{tabular}{|c|}\\hline[0,0]_"+Edit1->Text+"\\\\\\hline a\\ b\\ c\\\\\\hline\\end{tabular}";
//                Edit2->Text=Edit2->Text+"\\begin{tabular}{|c|}\\hline=\\\\\\hline \\\\\\hline\\end{tabular}";
                //\\begin{tabular}{|c|}\\hline[a,b]\\\\\\hline 1\\\\\\hline\\end{tabular}

                x+=30+dx-1;
                dx = 25;
                Canvas->Rectangle(x,y,x+dx,y+6+2*dy);
                Canvas->TextOutA(x+7,y+2,"=");
                Canvas->MoveTo(x,y+dy+4);
                Canvas->LineTo(x+dx,y+dy+4);

                x+=dx-1;
                cell* p = f;
                while(p!=0)
                {
                        s1 = "[";
                        outd(0,p->base,p,s1,".");
                        s1=s1+";";
                        outd(0,p->base,p,s1,",");
                        s1=s1+"]";
                        s2 = "";
                        for(int i=0; i<p->addrn; i++)
                        s2 = s2 + IntToStr(p->addr[i]) + "\\ ";

                        dx = Canvas->TextWidth(s1)+5;
                        int ddx=dx;
                        if(dx < Canvas->TextWidth(s2))
                           dx = Canvas->TextWidth(s2);
                        Canvas->Rectangle(x,y,x+dx+10,y+6+2*dy);
                        Canvas->TextOutA(x+5,y+2,s1);
                        Canvas->Font->Size=6;
                        Canvas->TextOutA(x+ddx,y+10,IntToStr(p->degr));
                        Canvas->Font->Size=12;
                        Canvas->TextOutA(x+5,y+4+dy,s2);
                        Canvas->MoveTo(x,y+dy+4);
                        Canvas->LineTo(x+dx+10,y+dy+4);
                        x+=dx+9;

                        //Edit2->Text=Edit2->Text+"<table class='b'><tr><td>"+s1+"<sub>"+IntToStr(p->degr)+"</sub></td></tr><tr><td>"+s2+"</td></tr></table>";
                        Edit2->Text=Edit2->Text+"\\begin{tabular}{|c|}\\hline"+s1+"_"+IntToStr(p->degr)+"\\\\\\hline"+s2+"\\\\\\hline\\end{tabular}";


                        if(x>Width-200)
                        {
                                x=94;
                                y+=8+2*dy;
                        }
                        p=p->next;
                }
                while(f!=0)
                {
                        p=f->next;
                        delete f;
                        f=p;
                }
                //Edit2->Text=Edit2->Text+"</td></tr></table>";
}
//---------------------------------------------------------------------------
void TForm1::out(int pos,int &x, int &y, AnsiString s, int a, int b, int c)
{
        AnsiString ss = s+"("+AnsiString(a)+", "+AnsiString(b)+", "+AnsiString(c)+")";
        Canvas->TextOutA(x,y,ss);
        y+=Canvas->TextHeight(ss);
        Form2->Memo1->Lines->Delete(pos);
        Form2->Memo1->Lines->Insert(pos,ss);
}
int tx,ty;
void TForm1::str(int lvl, int &x, int &y, int a, int b, int l, int n, int k, int& superbase)
         {
                int canv=Canvas->TextHeight("012")*5;
                int pos=0;
                x=10+100*(lvl-1);
                y = y - canv;
                pos=5*((lvl-1)*ty+(y-110+canv)/canv);
                out(pos+0,x,y,"equ",a,b,l);
                out(pos+1,x,y,"sub",a,b+l,l);
                out(pos+2,x,y,"equ",a+l,b+3*l,l);
                out(pos+3,x,y,"sub",a+l,b+l+l,l);
                out(pos+4,x,y,"exchg",b+l,b+l+l,l);
                if(l!=1)//lvl==k-1//p3=3^k-1
                {
                int yy=y;
                str(lvl+1,x,y,a-n/2,b,l/2,n,k,superbase);
                y = y + Canvas->TextHeight("012")*5;
                str(lvl+1,x,y,a-n/2+l,b+l+l,l/2,n,k,superbase);
                y = y + Canvas->TextHeight("012")*5;
                str2(lvl+1,x,y,a+n/2,a,l/2,n,k,superbase);
                //superbase+=l;
                y=yy;
                }
                else
                {
                        x=10+100*k;
                        int yy=y-canv;
                        pos=(5*(k-1)*ty+3*(y-110)/canv);
                        out(pos+0,x,yy,"mul",b,b+1,1);
                        out(pos+1,x,yy,"mul",b+2,b+3,1);
                        out(pos+2,x,yy,"mul",a,a+1,1);
                }
                y = y - canv;
                x=10+100*(k+k-lvl+1);
                pos=(5*(k-1)*ty+3*ty*(1+k-lvl)+3*(y-110)/canv);
                out(pos+0,x,y,"add",a,b,2*l);
                out(pos+1,x,y,"add",a,b+l+l,2*l);
                out(pos+2,x,y,"add",b+l,a,2*l);
                y = y + Canvas->TextHeight("012")*2;
         }
void TForm1::str2(int lvl, int &x, int &y, int a, int b, int l, int n, int k, int& superbase)
         {
                int canv=Canvas->TextHeight("012")*5;
                int pos=0;
                x=10+100*(lvl-1);
                y = y - canv;
                pos=5*((lvl-1)*ty+(y-110+canv)/canv);
                out(pos+0,x,y,"equ",superbase,b,l);
                out(pos+1,x,y,"sub",superbase,b+l,l);
                out(pos+2,x,y,"equ",superbase+l,b+3*l,l);
                out(pos+3,x,y,"sub",superbase+l,b+l+l,l);
                out(pos+4,x,y,"exchg",b+l,b+l+l,l);
                int olda=superbase;
                superbase+=2*l;
                if(l!=1)
                {
                int yy=y;
                str2(lvl+1,x,y,a-n/2,b,l/2,n,k,superbase);
                y = y + Canvas->TextHeight("012")*5;
                str2(lvl+1,x,y,a-n/2+l,b+l+l,l/2,n,k,superbase);
                y = y + Canvas->TextHeight("012")*5;
                str2(lvl+1,x,y,a+n/2,a,l/2,n,k,superbase);
                //superbase+=l;
                y=yy;
                }
                else
                {
                        x=10+100*k;
                        int yy=y-canv;
                        pos=(5*(k-1)*ty+3*(y-110)/canv);
                        out(pos+0,x,yy,"mul",b,b+1,1);
                        out(pos+1,x,yy,"mul",b+2,b+3,1);
                        out(pos+2,x,yy,"mul",a,a+1,1);
                }
                y = y - canv;
                x=10+100*(k+k-lvl+1);
                pos=(5*(k-1)*ty+3*ty*(1+k-lvl)+3*(y-110)/canv);
                out(pos+0,x,y,"add",olda,b,2*l);
                out(pos+1,x,y,"add",olda,b+l+l,2*l);
                out(pos+2,x,y,"add",b+l,olda,2*l);
                y = y + Canvas->TextHeight("012")*2;
         }
int TForm1::mul(int x, int y)
{
        return 0;
}
void __fastcall TForm1::Button2Click(TObject *Sender)
{
        Repaint();
        Canvas->Font->Size=8;
        int x=10, y=110;
        //TStrings* aaaa = new TStrings();
        //Memo1->Lines->Insert(0,"0");
        //Memo1->Lines->Insert(1,"1");
        //Memo1->Lines->Insert(0,"after0");
        // there are 3 steps
        // n = 2^k
        // k-1 уровней рекурсии

        // #1
        // equ(x 1 2)
        // add(x 3 2)
        // equ add ...
        // xchg(3 5 2)
        //// x - адреса более n
        // на уровне рекурсии последнем, k-1 м, занимаетс€ n/2 + n/4 + ...
        // на k-2 м n/4 + .... но умножить на 2
        // на первом уровне
        // число 2^(k-1-i) - размер €чейки
        // начинаем с n + n/2 * (k-1-i)
        int n=StrToInt(Edit1->Text);
        int k=0, m=n;
        while((m&1)==0){m=m>>1;k++;}
        if (m!=1)return;
        Canvas->TextOutA(10,30,"ѕр€мой ход:");
        Canvas->TextOutA(10+100*k,30,"”множение:");
        Canvas->TextOutA(10+100*k+200,30,"ќбратный ход:");
        int superbase = 1+n + n/2 * (k-1);
        ty=1;
        for(int i =1; i<k-1;i++)ty*=3;
        tx=k+k+1;
        Form2->Memo1->Clear();
        for(int i=0;i<(5*(k-1)*ty+3*ty*(k));i++)Form2->Memo1->Lines->Add("");
        str(1,x,y,1+n + n/2 * (k-1-1),1,(1<<(k-1-1)),n,k,superbase);
        // l - длина операций всегда равна 1<<(k-1-lvl)
        for(int i=0;i<(5*(k-1)*ty+3*ty*(k));i++)
        if(Form2->Memo1->Lines->operator [](i)=="")
                Form2->Memo1->Lines->Delete(i);
        AnsiString s = Form2->Memo1->Text;
        int pos;
        while(s.Pos("\r\n\r\n")>0)
        {
                s.Delete(s.Pos("\r\n\r\n"),2);
        }
        Form2->Memo1->Text=s;
        // #2 mul
        //int x=10+100*k, y=40;
        //for(int i=1;i<)
        // #3 add
}

//---------------------------------------------------------------------------


void __fastcall TForm1::FormShow(TObject *Sender)
{
        Form2->Show();
}
//---------------------------------------------------------------------------

