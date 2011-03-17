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
const char  A[3]={'0','1','2'};
const int   QQ[5][3]=
{{0,1,1},
 {1,2,2},
 {2,3,3},
 {3,4,4},
 {4,0,0}};
const int   ps[5][3]=
{{0,0,0},
 {1,1,1},
 {2,2,2},
 {0,0,0},
 {1,1,1}};
class Automat
{
        public:
        int Q[5][3];
        int q;
        //int a,k,b;
        Automat(int q_):q(q_)
        {
                for(int i=0;i<5;i++)
                for(int j=0;j<3;j++)
                {
                        memcpy(Q,QQ,5*3*sizeof(int));
                }

        }
        int phi(int k, char a)
        {
                int t=q;
                q=Q[k][a-'0'];
                return t;
        }
        int psi(int k, char a)
        {
                return ps[k][a-'0'];
        }

};
//---------------------------------------------------------------------------
void __fastcall TForm1::N2Click(TObject *Sender)
{
        Automat automat(0);
        for(int i=1; i<Memo1->Text.Length()-1; i++)
        {
                Memo2->Text=Memo2->Text+"\r\n("+
                Memo1->Text[i]+", "+
                AnsiString(automat.psi(automat.q,Memo1->Text[i]))+", "+
                AnsiString(automat.phi(automat.q,Memo1->Text[i]))+")";

        }
}
//---------------------------------------------------------------------------
