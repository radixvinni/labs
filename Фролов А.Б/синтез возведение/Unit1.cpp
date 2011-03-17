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

int a,b,m,t,p;
void TForm1::Compensate(int i, int j, AnsiString val, int koef=1)
{
        if (j*p+i<t)
        s->Text=s->Text+"\r\nc["+AnsiString(i)+"]["+AnsiString(j)+"]+="+val+"*"+AnsiString(koef)+";";
        else
        {
        // отсчитать а, отсчитать b, скомпенсировать
        if(val.Pos("-"))
                val=val.Insert("+", val.Pos("-")).Delete(val.Pos("-"),1);
        else
        if(val.Pos("+"))
                val=val.Insert("-", val.Pos("+")).Delete(val.Pos("+"),1);
        Compensate((j*p+i-(t-m))%p,(j*p+i-(t-m))/p,val,koef*a);
        Compensate((j*p+i-t)%p,(j*p+i-t)/p,val,koef*b);
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
a=Edit2->Text.ToInt();
b=Edit3->Text.ToInt();
m=Edit4->Text.ToInt();
t=Edit1->Text.ToInt();
p=ComboBox1->ItemIndex;
p=(p==2)?7:p+2;
s->Text="//c[0,i]=a^"+AnsiString(p);
int num=(t-1)/p+1;
for(int i = t-1; i>=num;i--){
        Compensate(0,i, "+c[0]["+AnsiString(i)+"]" );
        s->Text=s->Text+"\r\nc[0]["+AnsiString(i)+"]=0;";
}
}
//---------------------------------------------------------------------------

