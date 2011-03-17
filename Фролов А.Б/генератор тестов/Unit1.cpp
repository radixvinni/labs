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
AnsiString mul(AnsiString str, int a, int p)
{
        for(int i=1;i<=str.Length();i++)
                str[i]=((str[i]-'0')*a)%p + '0';
        return str;
}
AnsiString dup0(int a)
{
        AnsiString str="";
        for(int i=0;i<a;i++) str=str+"0";
        return str;
}
AnsiString inv(AnsiString a, int p)
{
        for(int i=1;i<=a.Length();i++)
                if(a[i]!='0')
                        a[i] = p - (a[i]-'0') + '0';
        return a;
}
AnsiString sum(AnsiString a, AnsiString b, AnsiString c, int p)
{
        b=b+dup0(a.Length()-b.Length());
        c=c+dup0(a.Length()-c.Length());

        for(int i=1;i<=a.Length();i++)
                a[i]=(a[i]-'0'+b[i]-'0'+c[i]-'0')%p+'0';
        return a;
}
void __fastcall TForm1::Button1Click(TObject *Sender)
{
        int p = Edit1->Text.ToInt();
        int b = Edit2->Text.ToInt();
        int a = Edit3->Text.ToInt();
        int t = Edit4->Text.ToInt();
        int m = Edit5->Text.ToInt();

        Memo1->Text="";
        int s=m-1+t;
        Memo1->Text=Memo1->Text+"s=m-1+t="+AnsiString(m)+"-1+"+AnsiString(t)+"="+AnsiString(s)+"\r\n";
        Edit8->Text=Edit6->Text.SubString(s+1,Edit6->Text.Length()-s);
        Memo1->Text=Memo1->Text+"q(X)="+Edit8->Text;
        Edit7->Text=Edit6->Text.SubString(1,s);
        int t1=2*s-2*m+1,t2=2*s-2*m+1-t;
        Memo1->Text=Memo1->Text+" r(X)="+Edit7->Text+"\r\n2s-2m+1="+AnsiString(t1)+" 2s-2m+1-t="+AnsiString(t2)+"\r\n";
        Memo1->Text=Memo1->Text+"r(X)=r(X)-bq(X)X^"+AnsiString(t1)+"-aq(X)X^"+AnsiString(t2)+"=\r\n   ";
        Memo1->Text=Memo1->Text+Edit7->Text+"-"+AnsiString(b)+"("+Edit8->Text+")X^"+AnsiString(t1)+"-"+AnsiString(a)+"("+Edit8->Text+")X^"+AnsiString(t2)+"=\r\n   ";
        Memo1->Text=Memo1->Text+Edit7->Text+"-"+dup0(t1)+mul(Edit8->Text,b,p)+"-"+dup0(t2)+mul(Edit8->Text,a,p)+"=\r\n   ";
        Memo1->Text=Memo1->Text+Edit7->Text+"+"+inv(dup0(t1)+mul(Edit8->Text,b,p),p)+"+"+inv(dup0(t2)+mul(Edit8->Text,a,p),p)+"=\r\n   ";
        Edit7->Text=sum(Edit7->Text,inv(dup0(t1)+mul(Edit8->Text,b,p),p),inv(dup0(t2)+mul(Edit8->Text,a,p),p),p);
        Memo1->Text=Memo1->Text+Edit7->Text+"\r\n";

        s=m;
        Edit8->Text=Edit7->Text.SubString(s+1,Edit7->Text.Length()-s);
        Memo1->Text=Memo1->Text+"q(X)="+Edit8->Text;
        Edit7->Text=Edit7->Text.SubString(1,s);
        t1=t;t2=0;
        Memo1->Text=Memo1->Text+" r(X)="+Edit7->Text+"\r\n";
        Memo1->Text=Memo1->Text+"r(X)=r(X)-bq(X)X^"+AnsiString(t1)+"-aq(X)X^"+AnsiString(t2)+"=\r\n   ";
        Memo1->Text=Memo1->Text+Edit7->Text+"-"+AnsiString(b)+"("+Edit8->Text+")X^"+AnsiString(t1)+"-"+AnsiString(a)+"("+Edit8->Text+")X^"+AnsiString(t2)+"=\r\n   ";
        Memo1->Text=Memo1->Text+Edit7->Text+"-"+dup0(t1)+mul(Edit8->Text,b,p)+"-"+dup0(t2)+mul(Edit8->Text,a,p)+"=\r\n   ";
        Memo1->Text=Memo1->Text+Edit7->Text+"+"+inv(dup0(t1)+mul(Edit8->Text,b,p),p)+"+"+inv(dup0(t2)+mul(Edit8->Text,a,p),p)+"=\r\n   ";
        Edit7->Text=sum(Edit7->Text,inv(dup0(t1)+mul(Edit8->Text,b,p),p),inv(dup0(t2)+mul(Edit8->Text,a,p),p),p);
        Memo1->Text=Memo1->Text+Edit7->Text;
}
//---------------------------------------------------------------------------
