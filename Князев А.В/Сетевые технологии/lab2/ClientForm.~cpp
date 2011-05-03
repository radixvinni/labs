//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ClientForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::N2Click(TObject *Sender)
{
MessageBoxA(Form2->Handle,"Модель SQL-клиента.\r\nВинников А. М., гр. А-14-07\r\nУ сервера есть несколько баз данных (совокупностей таблиц с записями).\r\nКлиент посылает команду use <имя БД>.-Сервер выбирает БД и в ответ\r\nвозвращает квитанцию. Затем клиент посылает запрос 'select * from\r\n<имя табл.> where <условие>'. - Сервер возвращает требуемые записи.","О программе",MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::N3Click(TObject *Sender)
{
ClientSocket1->Close();
Form2->Close();
}
//---------------------------------------------------------------------------


void __fastcall TForm2::Pf1Click(TObject *Sender)
{
        ClientSocket1->Socket->SendText(Memo1->Text);
}
//---------------------------------------------------------------------------

void __fastcall TForm2::select1Click(TObject *Sender)
{
Memo1->Text="select * from table1 where id = 1";
}
//---------------------------------------------------------------------------

void __fastcall TForm2::use1Click(TObject *Sender)
{
Memo1->Text="use base1";
}
//---------------------------------------------------------------------------

void __fastcall TForm2::ClientSocket1Read(TObject *Sender,
      TCustomWinSocket *Socket)
{
        //show columns
        AnsiString s=Socket->ReceiveText();
        int len=s.Length();
        list->Columns->Clear();
        int pos=0;
        while(pos<=len&&s[pos?pos:1]!='\n')
        {
                pos++;
                TListColumn* lc = list->Columns->Add();
                int pos1=pos;
                for(;pos<=len&&s[pos]!='\t'&&s[pos]!='\n';pos++){}
                lc->Caption=s.SubString(pos1,pos-pos1);
        }
        //show rows
        int rows=0;
        list->Items->Clear();
        while(pos<=len)
        {
           pos++;
           TListItem * li =list->Items->Add();
           int pos1=pos;
           for(;s[pos]!='\t'&&s[pos]!='\n';pos++){}
           li->Caption=s.SubString(pos1,pos-pos1);
           rows++;
           while(pos<=len&&s[pos]!='\n')
           {
                pos++;
                int pos1=pos;
                for(;pos<=len&&s[pos]!='\t'&&s[pos]!='\n';pos++){}
                li->SubItems->Add(s.SubString(pos1,pos-pos1));
           }
        }
        if(rows)
        StatusBar1->SimpleText="Ресультатов: "+AnsiString(rows);
        else
        StatusBar1->SimpleText="Нет результата. Пусто";

}
//---------------------------------------------------------------------------

void __fastcall TForm2::N5Click(TObject *Sender)
{
        if(Form3->ShowModal()==mrOk)
        {
                ClientSocket1->Host=Form3->Edit1->Text;
                ClientSocket1->Port=Form3->Edit2->Text.ToInt();
                ClientSocket1->Open();
                StatusBar1->SimpleText="Соединено";
        }
}
//---------------------------------------------------------------------------

