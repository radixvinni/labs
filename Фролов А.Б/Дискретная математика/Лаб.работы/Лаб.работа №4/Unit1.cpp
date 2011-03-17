//---------------------------------------------------------------------------

#include <vcl.h>
#include <memory.h>

#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int   Q1[4][4]=
{{1,0,0,0},
 {1,0,1,0},
 {1,0,0,0},
 {0,1,0,0}};
int   Q2[4][4]=
{{1,2,3,3},
 {1,0,1,2},
 {1,0,0,0},
 {1,0,0,0}};

int   Q[4][4];
 //---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
s->Cells[0][1]="phi(0,q)";
s->Cells[0][2]="phi(1,q)";
s->Cells[0][3]="psi(0,q)";
s->Cells[0][4]="psi(1,q)";
s->Cells[1][0]="q0";
s->Cells[2][0]="q1";
s->Cells[3][0]="q2";
s->Cells[4][0]="q3";
for(int i=1;i<=4;i++)
for(int j=1;j<=4;j++)
s->Cells[i][j]=AnsiString(Q1[j-1][i-1]);
}
const char  A[3]={'0','1'};
class Automat
{
        public:
        int q;
        //int a,k,b;
        Automat(int q_):q(q_)
        {
        }
        int phi(char a)
        {
                int k=q;
                q=Q[a-'0'][k];
                return q;
        }
        int psi( char a)
        {
                return Q[a-'0'+2][q];
        }

};
//---------------------------------------------------------------------------
void __fastcall TForm1::N2Click(TObject *Sender)
{
 for(int i=1;i<=4;i++)
 for(int j=1;j<=4;j++)
  Q[j-1][i-1]=StrToInt(s->Cells[i][j]);
 for(int len=2;len<5;len++)
 {
   bool foundsameglobal = false;
   Memo1->Text=Memo1->Text+"Результат для слов длины "+len+"\r\nСлово     \tдля Vq0\tдля Vq1\tдля Vq2\tдля Vq3\r\n";
   AnsiString str="000000";
   for(int ex=0;ex<(1<<len);ex++)
   {
     bool foundsame = false;
     bool found[32];
     for(int j=0;j<32;j++)found[j]=false;
     for(int j=0;j<len;j++)
     {
        if((ex>>j)%2==0)str[len-j]='0';
        else str[len-j]='1';
     }
     Memo1->Text=Memo1->Text+str+"\t";
     for(int j=0;j<s->ColCount-1;j++)
     {
        Automat automat(j);
        Memo1->Text=Memo1->Text+"\t";
        int sost=0;
        for(int i=1; i<=len; i++)
        {
                Memo1->Text=Memo1->Text+
                AnsiString(automat.psi(str[i]));
                sost=automat.phi(str[i]);
        }
        if(found[sost])foundsame=true;
        found[sost]=true;
     }
     Memo1->Text=Memo1->Text+"\r\n";
     if(foundsame)foundsameglobal=true;
     if(foundsame)Memo1->Text=Memo1->Text+"Автоматы неотличимы по слову "+str+"\r\n";
   }
   //if(foundsameglobal)Memo1->Text=Memo1->Text+"\r\nАвтоматы неотличимы по слову длины "+len+"\r\n";
   if(foundsameglobal)break;
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
        s->ColCount=4;
        for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++)
                s->Cells[i][j]=AnsiString(Q1[j-1][i-1]);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
        s->ColCount=5;
        for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++)
                s->Cells[i][j]=AnsiString(Q2[j-1][i-1]);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
 for(int i=1;i<=4;i++)
 for(int j=1;j<=4;j++)
  Q[j-1][i-1]=StrToInt(s->Cells[i][j]);
 for(int len=2;len<=5;len++)
 {
   Memo1->Text=Memo1->Text+"Результат для слов длины "+len+"\r\nСлово     \tдля Vq0\tдля Vq1\tдля Vq2\tдля Vq3\r\n";
   AnsiString str="000000";
   bool foundsame = false;
   //bool found[1024];
   //for(int j=0;j<1024;j++)found[j]=false;
   unsigned ssost[5];
   for(int j=0;j<5;j++)ssost[j]=1;
   for(int ex=0;ex<(1<<len);ex++)
   {
     for(int j=0;j<len;j++)
     {
        if((ex>>j)%2==0)str[len-j]='0';
        else str[len-j]='1';
     }
     Memo1->Text=Memo1->Text+str+"\t";
     for(int j=0;j<s->ColCount-1;j++)
     {
        Automat automat(j);
        Memo1->Text=Memo1->Text+"\t";
        int sost=0;
        for(int i=1; i<=len; i++)
        {
                Memo1->Text=Memo1->Text+
                AnsiString(automat.psi(str[i]));
                sost=automat.phi(str[i]);
        }
        Memo1->Text=Memo1->Text+"["+sost+"]";
        ssost[j]=ssost[j]*4+sost;
     }
     Memo1->Text=Memo1->Text+"\r\n";
     //if(found[sost])foundsame=true;
     //found[sost]=true;
     //if(foundsame)foundsameglobal=true;
     //if(foundsame)Memo1->Text=Memo1->Text+"Автоматы неотличимы по слову "+str+"\r\n";
   }
   if(  ssost[0]==ssost[1]||ssost[1]==ssost[2]||ssost[0]==ssost[2]||ssost[0]==ssost[3]||
        ssost[1]==ssost[3]||ssost[2]==ssost[3])foundsame=true;
   if(foundsame)Memo1->Text=Memo1->Text+"\r\nАвтоматы неотличимы по слову длины "+len+"\r\n";
   if(foundsame)break;
 }
}
//---------------------------------------------------------------------------

