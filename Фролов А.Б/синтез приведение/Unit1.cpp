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
        AnsiString p = ComboBox1->Text;
        AnsiString a = Edit2->Text;
        AnsiString b = Edit3->Text;
        int t = Edit4->Text.ToInt();
        int m = Edit5->Text.ToInt();

        Memo1->Text="AAL::"+p+" delenie(AAL::"+p+" m)\r\n{\r\n        ";
        int s=m-1+t;
        Memo1->Text=Memo1->Text+"//s=m-1+t="+AnsiString(m)+"-1+"+AnsiString(t)+"="+AnsiString(s)+"\r\n";
        Memo1->Text=Memo1->Text+"        AAL::"+p+" a(\""+a+"\");\r\n";
        Memo1->Text=Memo1->Text+"        AAL::"+p+" b(\""+b+"\");\r\n";
        Memo1->Text=Memo1->Text+"        AAL::"+p+" x_s(\""+dup0(s)+"1\");\r\n";
        Memo1->Text=Memo1->Text+"        AAL::"+p+" q = m/x_s;\r\n";
        Memo1->Text=Memo1->Text+"        AAL::"+p+" r = m%x_s;\r\n";
        int t1=2*s-2*m+1,t2=2*s-2*m+1-t;
        Memo1->Text=Memo1->Text+"        //2s-2m+1="+AnsiString(t1)+"\r\n";
        Memo1->Text=Memo1->Text+"        AAL::"+p+" x_p(\""+dup0(t1)+"1\");\r\n        r=r-a*q*x_p;\r\n";

        Memo1->Text=Memo1->Text+"        //2s-2m+1-t="+AnsiString(t2)+"\r\n";
        Memo1->Text=Memo1->Text+"        AAL::"+p+" x_p_t(\""+dup0(t2)+"1\");\r\n        r=r-b*q*x_p_t;\r\n";

        Memo1->Text=Memo1->Text+"\r\n";

        Memo1->Text=Memo1->Text+"        AAL::"+p+" x_m(\""+dup0(m)+"1\");\r\n        if(x_m>r) q.setZero(); else\r\n";
        Memo1->Text=Memo1->Text+"        q = r/x_m;\r\n";
        Memo1->Text=Memo1->Text+"        r = r%x_m;\r\n";
        Memo1->Text=Memo1->Text+"        AAL::"+p+" x_t(\""+dup0(t)+"1\");\r\n        r=r-a*q*x_t-b*q;\r\n        return r;\r\n}";
}
//---------------------------------------------------------------------------
