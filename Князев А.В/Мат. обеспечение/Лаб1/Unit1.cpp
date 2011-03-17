//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
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
        array.Add(Edit1->Text.c_str(),Edit2->Text.ToInt());
        v->InsertRow(Edit1->Text,Edit2->Text,false);
        Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        MessageBoxA(Form1->Handle,IntToStr(array.Search(Edit1->Text.c_str())).c_str(),"Результат",MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
        array.Delete(Edit1->Text.c_str());
        int a;
        if (v->FindRow(Edit1->Text,a))
        v->DeleteRow(a);
        Repaint();
}
void TForm1::Drawer::draw(int i, char str[])
{
        AnsiString s= AnsiString(str)+ ": " + AnsiString(i);
        int dy= Form1->s->Canvas->TextHeight(s);
        int dx= Form1->s->Canvas->TextWidth(s)>>1;

        int x = Form1->s->Width>>1;
        TRect rect;
        rect.Top=y;
        rect.Bottom=y+dy+2;
        rect.Left=x-100;
        rect.Right=x+100;

        Form1->s->Canvas->Brush->Color=clBtnFace;
        Form1->s->Canvas->Brush->Style=bsSolid;
        Form1->s->Canvas->Rectangle(rect);
        Form1->s->Canvas->TextOutA(x-dx-20,y+1,s);
        rect.Left=x+60;
        Form1->s->Canvas->Brush->Color=clBlack;
        Form1->s->Canvas->Brush->Style=bsBDiagonal;
        Form1->s->Canvas->Rectangle(rect);
        Form1->s->Canvas->Brush->Style=bsClear;
        y+=dy;
        Form1->s->Canvas->MoveTo(x+80,y);
        Form1->s->Canvas->LineTo(x+80,y+10);
        Form1->s->Canvas->LineTo(x-80,y+10);
        Form1->s->Canvas->LineTo(x-80,y+20);
        Form1->s->Canvas->LineTo(x-85,y+15);
        Form1->s->Canvas->MoveTo(x-80,y+20);
        Form1->s->Canvas->LineTo(x-75,y+15);
        y+=20;
        Form1->s->Canvas->TextOutA(x-83,y+1,"0");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::sPaint(TObject *Sender)
{
        Drawer dr;
        array.draw(dr);
}
//---------------------------------------------------------------------------

