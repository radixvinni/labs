//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void draw(TCanvas* c, int& x, int& y, int b=1, int d=1, int lvl=1)
{
        c->Rectangle(x,y,x+50,y+20);
        AnsiString s = IntToStr(b)+"; "+IntToStr(b+d);
        c->TextOutA(x+6,y+1,s);
        x+=49;
        y+=19;
}
void __fastcall TForm1::FormPaint(TObject *Sender)
{
        int n = Edit1->Text.ToInt();
        int x=10, y=50;
        int nx = 1<<n;
        Canvas->Rectangle(x,y,x+(nx*25),y+20);
        x+=5;
        Canvas->Font->Size=10;
        Canvas->TextOutA(x+1,y+1,"V");
        x+=Canvas->TextWidth("V");
        Canvas->Font->Size=8;
        Canvas->TextOutA(x+1,y+4,Edit1->Text);
        x+=Canvas->TextWidth(Edit1->Text);
        Canvas->Font->Size=10;
        Canvas->TextOutA(x+1,y+1,"[1]");
        x+=Canvas->TextWidth("[1]");
        x=10+nx*25-nx/2;
        Canvas->Rectangle(x,y,x+nx*25-nx/2+1,y+20);
        x+=5;
        Canvas->Font->Size=10;
        Canvas->TextOutA(x+1,y+1,"V");
        x+=Canvas->TextWidth("V");
        Canvas->Font->Size=8;
        Canvas->TextOutA(x+1,y+4,Edit1->Text);
        x+=Canvas->TextWidth(Edit1->Text);
        Canvas->Font->Size=10;
        Canvas->TextOutA(x+1,y+1,"[2]");
        x+=Canvas->TextWidth("[2]");
        x=10;
        y+=20-1;
        TCanvas* canvas = Canvas;
        for (int lvl=1; lvl<=n; lvl++)
        {
             int d = 1<<(lvl-1); // V_lvl
             for(int base=1; base+d<=nx; base+=d+d)
             {
                for(int b=base; b<d+base; b++)
                {
                        Canvas->Rectangle(x,y,x+50,y+20);
                        AnsiString s = IntToStr(b)+"; "+IntToStr(b+d);
                        Canvas->TextOutA(x+6,y+1,s);
                        x+=49;
                        //y+=19;
                }
                for(int b=base; b<d+base; b++)
                {
                        Canvas->Rectangle(x,y,x+50,y+20);
                        AnsiString s = IntToStr(b)+"; -"+IntToStr(b+d);
                        Canvas->TextOutA(x+6,y+1,s);
                        x+=49;
                        //y+=19;
                }
             }
             y+=19;
             x=10;

        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        Form2->Memo1->Text="";
        int n = Edit1->Text.ToInt();
        int nx = 1<<n;
        int i = nx+1;
        for (int lvl=1; lvl<=n; lvl++)
        {
             int d = 1<<(lvl-1); // V_lvl
             for(int base=1; base+d<=nx; base+=d+d)
             {
                for(int b=base; b<d+base; b++)
                {
                        AnsiString s = "add("+IntToStr(i)+", "+IntToStr(b)+", "+IntToStr(b+d)+")";
                        Form2->Memo1->Text=Form2->Memo1->Text+s+"\r\n";
                        i++;
                }
                for(int b=base; b<d+base; b++)
                {
                        AnsiString s = "sub("+IntToStr(i)+", "+IntToStr(b)+", "+IntToStr(b+d)+")";
                        Form2->Memo1->Text=Form2->Memo1->Text+s+"\r\n";
                        i++;
                }
             }
        }
        AnsiString s = "# Результирующий вектор находятся по адресам: "+IntToStr(i-nx)+".."+IntToStr(i-1);
        Form2->Memo1->Text=Form2->Memo1->Text+s;
        Form2->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
        Repaint();        
}
//---------------------------------------------------------------------------

