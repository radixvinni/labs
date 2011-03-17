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
void __fastcall TForm1::Button1Click(TObject *Sender)
{
unsigned short m[1000];
for(int i=0;i<1000;i++)m[i]=0;
unsigned short n=Edit1->Text.ToInt();
for(int i=0; i<Memo->Lines->Count; i++)
{
        int p1 = Memo->Lines->operator [](i).Pos("(");
        int p2 = Memo->Lines->operator [](i).Pos(",");
        int num = Memo->Lines->operator [](i).SubString(p1+1,p2-p1-1).ToInt();
        p1 = Memo->Lines->operator [](i).Pos(")");
        int l = Memo->Lines->operator [](i).SubString(p1-1,1).ToInt();
        for (int j=0; j<l; j++)
        if(num>=Edit1->Text.ToInt())
        if(m[num]==0)
        m[num++]=n++;
}
n=Edit1->Text.ToInt();
for(int i=0; i<Memo->Lines->Count; i++)
{
        AnsiString s=Memo->Lines->operator [](i);
        int p1 = s.Pos("(");
        int p2 = s.Pos(",");
        int num;
        num = s.SubString(p1+1,p2-p1-1).ToInt();
        if(num>=n)
        {
                s=s.Delete(p1+1,p2-p1-1).Insert(AnsiString(m[num]),p1+1);
        }
        p1 = s.Pos(",");
        p2 = p1+s.SubString(p1+1,100).Pos(",");
        num = s.SubString(p1+2,p2-p1-2).ToInt();
        if(num>=n)
        {
                s=s.Delete(p1+2,p2-p1-2).Insert(AnsiString(m[num]),p1+2);
        }
        Memo->Lines->Delete(i);
        Memo->Lines->Insert(i,s);
}
}
//---------------------------------------------------------------------------
