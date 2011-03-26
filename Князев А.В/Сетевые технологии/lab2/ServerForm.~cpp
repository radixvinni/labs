//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ServerForm.h"
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
//низко-уровневые процедуры: чтение заданной строки, чтение строки до разделителя, чтение разделителя
bool parse_const_string(char* &p,char* s)
{
        while(*s!=0)
        if(*p!=*s) return false;
        else { p++; s++; }
        return true;
}
void parse_string(char* &p,char* id)
{
        while(*p!='\r'&&*p!='\n'&&*p!=' '&&*p!='\t'&&*p!='\0')
        {
                *id=*p;
                p++;
                id++;
        }
        *id=0;
}
void parse_delimiter(char* &p)
{
        while(*p=='\r'||*p=='\n'||*p==' '||*p=='\t') p++;
}
char database[100];
char table[100];
struct Condition
{
        char field[100];
        char compare_indicator;
        char constant[100];
        int field_number;
        char field_type;//0=string 1=integer
        //todo: and or ( )
        //~Condition() {}
} *condition;
void parse_condition(char* &p, Condition* &c)
{
        c=new Condition();
        parse_string(p,c->field);
        parse_delimiter(p);
        c->compare_indicator=*p;
        p++;
        parse_delimiter(p);
        parse_string(p,c->constant);
}
void __fastcall TForm1::ServerSocket1ClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
        char buffer[500];
        buffer[0]=0;
        //strcpy(buffer,Socket->ReceiveText().c_str());
        buffer[Socket->ReceiveBuf(buffer,500)]=0;
        //parse buffer!
        char* p=buffer;
        //{u{se }(.*){\r\n,\0},s{elect * from }(.*)[{ where }(.*){=,<,>}(#)[{or,and} ...]]}
        while(*p!=0)
        switch(*p)
        {
        case 'u':
        case 'U':
                {
                        p++;
                        if(!parse_const_string(p,"se")) return;
                        parse_delimiter(p);
                        parse_string(p,database);
                        parse_delimiter(p);
                        ListBox1->Items->Add("Клиент "+Socket->RemoteHost+":"+Socket->RemotePort+" открыл базу данных "+database);
                        Socket->SendText("Ok");
                        break;
                }
        case 's':
        case 'S':
                {
                        p++;
                        if(!parse_const_string(p,"elect * from")) return;
                        parse_delimiter(p);
                        parse_string(p,table);
                        parse_delimiter(p);
                        if(*p=='w'||*p=='W')
                        {       p++;
                                if(!parse_const_string(p,"here")) return;
                                parse_delimiter(p);
                                parse_condition(p,condition);
                                parse_delimiter(p);
                        }
                        buffer[0]=0;
                        strcat(buffer,database);
                        strcat(buffer,"\\");
                        strcat(buffer,table);
                        FILE* f=fopen(buffer,"r");
                        char outbuf[1000];
                        if(!feof(f))
                                fgets(outbuf,1000,f);
                        p=outbuf;
                        int num=0;
                        while(*p!=0)
                        {
                                num++;
                                char type=(*p=='*');
                                if(*p=='*')p++;
                                parse_string(p,buffer);
                                if(condition)
                                if(strcmp(buffer,condition->field)==0)
                                {
                                        condition->field_number=num;
                                        condition->field_type=type;
                                }
                                parse_delimiter(p);
                        }
                        int rows=0;
                        while(!feof(f))
                        {
                                fgets(buffer,490,f);
                                //skip condition->field_num fields
                                char* t=buffer;
                                if(condition)
                                for(int i=0;i<condition->field_number;i++)
                                {
                                        while(*p!='\r'&&*p!='\n'&&*p!=' '&&*p!='\t'&&*p!='\0')
                                                t++;
                                        parse_delimiter(t);
                                }
                                if(!condition
                                 ||!condition->field_type&&parse_const_string(t,condition->constant)
                                 ||condition&&atoi(t)==atoi(condition->constant))
                                {
                                        rows++;
                                        strcpy(p,buffer);
                                        p+=strlen(p);
                                }
                        }
                        if(*(p-1)=='\n')*(p-1)=0;
                        fclose(f);
                        //Socket->SendBuf(buffer,(int)(buffer-p));
                        Socket->SendText(AnsiString(outbuf));
                        ListBox1->Items->Add("Клиенту "+Socket->RemoteHost+":"+Socket->RemotePort+" отправлено "+AnsiString(rows)+" записей из "+table);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
MessageBoxA(Form1->Handle,"Модель SQL-сервера.\r\nВинников А. М., гр. А-14-07\r\nУ сервера есть несколько баз данных (совокупностей таблиц с записями).\r\nКлиент посылает команду use <имя БД>.-Сервер выбирает БД и в ответ\r\nвозвращает квитанцию. Затем клиент посылает запрос 'select * from\r\n<имя табл.> where <условие>'. - Сервер возвращает требуемые записи.","О программе",MB_OK);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
ServerSocket1->Close();
Form1->Close();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N5Click(TObject *Sender)
{
        if(Form4->ShowModal()==mrOk)
        {
                ServerSocket1->Port=Form4->Edit2->Text.ToInt();
                ServerSocket1->Open();
                StatusBar1->SimpleText="Сервер запущен";
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)
{
ServerSocket1->Close();
StatusBar1->SimpleText="Сервер остановлен";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1Accept(TObject *Sender,
      TCustomWinSocket *Socket)
{
        ListBox1->Items->Add("Соединение c "+Socket->RemoteHost+":"+Socket->RemotePort+" принято");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientConnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        ListBox1->Items->Add("Соединение c "+Socket->RemoteHost+":"+Socket->RemotePort+" начато");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientDisconnect(TObject *Sender,
      TCustomWinSocket *Socket)
{
        ListBox1->Items->Add("Соединение c "+Socket->RemoteHost+":"+Socket->RemotePort+" завершено");

}
//---------------------------------------------------------------------------

void __fastcall TForm1::ServerSocket1ClientError(TObject *Sender,
      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
        ListBox1->Items->Add("Соединение c "+Socket->RemoteHost+":"+Socket->RemotePort+" завершилось ошибкой");

}
//---------------------------------------------------------------------------

