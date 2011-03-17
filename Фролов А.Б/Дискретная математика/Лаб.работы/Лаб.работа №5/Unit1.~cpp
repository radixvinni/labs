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
char   QQ[4][7][4]=
{{"2s1","   ","   ","0r4","0l4","0l5","0s0"},
 {"1r0","1l1","1l2","2s4","   ","1s0","1s0"},
 {"2r0","2l1","1l2","2r3","2l4","0l5","-r6"},
 {"-l2","-r3","-r7","-l5","-r6","-r7","2s7"}};
unsigned endstate;
unsigned minussymbol;
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
 s->Cells[0][1]="0";
 s->Cells[0][2]="1";
 s->Cells[0][3]="2";
 s->Cells[0][s->RowCount-1]="-";
 s->Cells[1][0]="q0";
 s->Cells[2][0]="q1";
 s->Cells[3][0]="q2";
 s->Cells[4][0]="q3";
 s->Cells[5][0]="q4";
 s->Cells[6][0]="q5";
 s->Cells[7][0]="q6";
 s->Cells[8][0]="q7";
 s->Cells[s->ColCount-1][0]=s->Cells[s->ColCount-1][0]+"[E]";
 for(int i=0;i<4;i++)
 for(int j=0;j<7;j++)
 {
        s->Cells[j+1][i+1] = AnsiString(QQ[i][j]);
 }
}


class Turing
{
        public:
        char Q[100];
        int i;
        int q; char b;
        Turing(int i_):i(i_),q(0)
        {
                        memset(Q,'-',100*sizeof(char));
        }
        void setText(char* str)
        {
                memcpy(&Q[i],str,strlen(str));
        }
        bool next()
        {
                int a = Q[i]-'0';
                if(Q[i]=='-')a=minussymbol;
                char news = QQ[a][q][0];
                b=news;
                char slr = QQ[a][q][1];
                q = QQ[a][q][2]-'0';
                Q[i]=news;
                switch(slr)
                {
                        case 'r':i++;break;
                        case 'l':i--;break;
                }
                if (q==endstate) return false;
                return true;
        }
};
//---------------------------------------------------------------------------
void __fastcall TForm1::N2Click(TObject *Sender)
{
         if (s->ColCount>9)return;
         if (s->RowCount>5)return;
         endstate=s->ColCount-2;
         minussymbol=s->RowCount-2;
        for(int i=0;i<4;i++)
        for(int j=0;j<7;j++)
        {
                strcpy(QQ[i][j],s->Cells[j+1][i+1].c_str());// = AnsiString();
        }
        Turing automat(10);
        automat.setText(Memo1->Lines->operator [](0).c_str());
        //Memo2->Text=Memo2->Text+"\r\n"+IntToStr(automat.i)+"["+automat.Q[automat.i]+"]\t"+IntToStr(automat.q);

        while(automat.next())
        {
        //        Memo2->Text=Memo2->Text+"\r\n"+IntToStr(automat.i)+"["+automat.Q[automat.i]+"=>"+automat.b+"]   \t"+IntToStr(automat.q);
        }
        Memo2->Text=Memo2->Text+"\r\n"+AnsiString(automat.Q);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Button5Click(TObject *Sender)
{
N2Click(Sender);
}
//---------------------------------------------------------------------------

void TForm1::aaa()
{
 s->Cells[0][1]="0";
 s->Cells[0][2]="1";
 s->Cells[0][3]="2";
 s->Cells[0][s->RowCount-1]="-";
 s->Cells[1][0]="q0";
 s->Cells[2][0]="q1";
 s->Cells[3][0]="q2";
 s->Cells[4][0]="q3";
 s->Cells[5][0]="q4";
 s->Cells[6][0]="q5";
 s->Cells[7][0]="q6";
 s->Cells[8][0]="q7";
 s->Cells[s->ColCount-1][0]=s->Cells[s->ColCount-1][0]+"[E]";
}
void __fastcall TForm1::Button1Click(TObject *Sender)
{
s->RowCount=s->RowCount+1;
aaa();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
s->RowCount=s->RowCount-1;
aaa();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
s->ColCount=s->ColCount+1;
aaa();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
s->ColCount=s->ColCount-1;
aaa();
}
//---------------------------------------------------------------------------

