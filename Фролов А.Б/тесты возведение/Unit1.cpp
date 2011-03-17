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

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
switch(ComboBox1->ItemIndex)
{
case 0: s->RowCount=2;break;
case 1: s->RowCount=3;break;
case 2: s->RowCount=7;break;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1Change(TObject *Sender)
{
s->ColCount=Edit1->Text.Length();
Label3->Caption="t="+AnsiString(Edit1->Text.Length());
for(int i=0;i<s->ColCount;i++)
{
        s->Cells[i][0]=Edit1->Text[i+1];
        for(int j=1;j<s->RowCount;j++)
        {
                s->Cells[i][j]="0";
        }
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCanResize(TObject *Sender, int &NewWidth,
      int &NewHeight, bool &Resize)
{
        Edit1Change(Sender);
}
//---------------------------------------------------------------------------
int a,b,m,t,p;
void TForm1::Compensate(int i, int j, int val)
{
        if (j*p+i<t)
        s->Cells[j][i]=AnsiString((s->Cells[j][i].ToInt()+val+100*p)%p);
        else
        {
        // отсчитать а, отсчитать b, скомпенсировать
        Compensate((j*p+i-(t-m))%p,(j*p+i-(t-m))/p,-val*a);
        Compensate((j*p+i-t)%p,(j*p+i-t)/p,-val*b);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
a=Edit2->Text.ToInt();
b=Edit3->Text.ToInt();
m=Edit4->Text.ToInt();
t=Edit1->Text.Length();
p=ComboBox1->ItemIndex;
p=(p==2)?7:p+2;

int num=(t-1)/p+1;
for(int i = t-1; i>=num;i--){
        Compensate(0,i, s->Cells[i][0].ToInt() );
        s->Cells[i][0]="0";
}
}
//---------------------------------------------------------------------------

