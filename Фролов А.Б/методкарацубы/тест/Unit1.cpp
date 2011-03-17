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
#define _P 3
int a[33];
void add (int p, int q, int n)
{ for(int i=0;i<n;i++) a[p+i]=(a[p+i]+a[q+i]) % _P; }
void sub (int p, int q, int n)
{ for(int i=0;i<n;i++) a[p+i]=(10+a[p+i]-a[q+i]) % _P; }
void mul (int p, int q, int n)
{       a[p]=(a[p]*a[q]) / _P;
        a[p+1]=(a[p]*a[q]) % _P;
}
void exchg (int p, int q, int n)
{ for(int i=0;i<n;i++)
{
        int t=a[p+i];
        a[p+i]=a[q+i];
        a[q+i]=t;
}
}
void equ (int p, int q, int n)
{ for(int i=0;i<n;i++) a[p+i]=a[q+i]; }


void __fastcall TForm1::Button1Click(TObject *Sender)
{
for(int i=1;i<3;i++)a[i]=Edit1->Text[i]-'0';
for(int i=1;i<3;i++)a[i+2]=Edit1->Text[i]-'0';



}
//---------------------------------------------------------------------------
