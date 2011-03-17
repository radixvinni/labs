//---------------------------------------------------------------------------

#include <vcl.h>
#include <memory.h>

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
void __fastcall TForm1::N2Click(TObject *Sender)
{

        int n = scheme->Lines->Count;
        //for po[i=1..1000]
        //for scheme[j=0..n]
        //do a=j.find("".."->")
        //b=>j.find("->".."\0")
        //po[i]=po[i-1]
        //po[i].replace(a,b)
    int i=0;
    AnsiString s = p->Lines->operator [](p->Lines->Count-1);
    for(int k=0;i<100&&k<100;k++)
    {
        //p->Lines->Add(p->Lines->operator [](i-1));
        for(int j=0;j<n;j++)
        {
                int pos = scheme->Lines->operator [](j).Pos("->");
                int len = scheme->Lines->operator [](j).Length();
                AnsiString a = scheme->Lines->operator [](j).SubString(0,pos-1);
                AnsiString b = scheme->Lines->operator [](j).SubString(pos+2,len);
                int alen=pos-1;
                //int blen=len-pos-1;
                if(alen==0)pos=1;
                else pos = s.Pos(a);
                if(pos==0)continue;
                int ppos=b.Pos("*");
                if(ppos>0)
                {
                s.operator =(s.Delete(pos,alen));
                b.operator =(b.Delete(ppos,1));
                p->Lines->Add(s.Insert(b,pos));i++;
                return;
                }
                if(alen>0)
                s.operator =(s.Delete(pos,alen));
                s.operator =(s.Insert(b,pos));
                p->Lines->Add(s);i++;
                break;
        }
    }

}
//---------------------------------------------------------------------------
void __fastcall TForm1::N3Click(TObject *Sender)
{
scheme->Clear();
scheme->Lines->Add("a0->0a");
scheme->Lines->Add("a1->1a");
scheme->Lines->Add("a->b");
scheme->Lines->Add("0b->b1");
scheme->Lines->Add("1b->*0");
scheme->Lines->Add("->a");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
scheme->Clear();
scheme->Lines->Add("a01->1a0");
scheme->Lines->Add("a0b->gb0");
scheme->Lines->Add("a->gb");
scheme->Lines->Add("0g->g0");
scheme->Lines->Add("g0->a0");
scheme->Lines->Add("gb->*");
scheme->Lines->Add("->a");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N5Click(TObject *Sender)
{
scheme->Clear();
scheme->Lines->Add("|0->0||");
scheme->Lines->Add("1->0|");
scheme->Lines->Add("0->");

}
//---------------------------------------------------------------------------

