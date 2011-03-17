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


void __fastcall TForm1::N9Click(TObject *Sender)
{
Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
        MessageBoxA(Form1->Handle,"Лабораторная работа №1 \n Выполнил: Винников Александр\n Группа А-14-07\n Преподаватель: Князев Анатолий Васильевич", "О программе",0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton3Click(TObject *Sender)
{
        Form5->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N7Click(TObject *Sender)
{
        Form5->Query1->SQL->Clear();
        Form5->Query1->SQL->Add("SELECT students.FIO AS ФИО_студента, students.AvgMark AS Средняя_оценка, students.Lang AS Иностранный_язык, groups.GroupCode AS Код_группы, groups.SpecName AS Название_специальности, groups.SpecCode AS Код_специальности FROM students INNER JOIN groups ON students.GroupId = groups.GroupId WHERE students.AvgMark > 4.1 AND students.Lang = 'Английский'");
        Form5->Query1->Active=true;
        Form5->StatusBar1->SimpleText="Количество записей: " + AnsiString(Form5->Query1->RecordCount);
        Form5->Show();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N8Click(TObject *Sender)
{
        if(OKBottomDlg1->ShowModal()==mrOk)
        {
                Form5->Query1->SQL->Clear();
                Form5->Query1->SQL->Add("SELECT students.FIO AS ФИО_студента, students.AvgMark AS Средняя_оценка, students.Lang AS Иностранный_язык, groups.GroupCode AS Код_группы, groups.SpecName AS Название_специальности, groups.SpecCode AS Код_специальности FROM students INNER JOIN groups ON students.GroupId = groups.GroupId WHERE "+OKBottomDlg1->ComboBox1->Text+"='"+OKBottomDlg1->LabeledEdit1->Text+"'");
                Form5->Query1->Active=true;
                Form5->StatusBar1->SimpleText="Количество записей: " + IntToStr(Form5->Query1->RecordCount);
                Form5->Show();
        }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N5Click(TObject *Sender)
{
        if(OKBottomDlg->ShowModal()==mrOk)
        {
                Query1->Active=false;
                Query3->SQL->Clear();
                Query3->SQL->Add("INSERT INTO students (FIO,GroupId,AvgMark,Lang) VALUES (:FIO,:GroupId,:AvgMark,:Lang)"); //
                Query3->ParamByName("FIO")->AsString = OKBottomDlg->Edit1->Text;
                Query3->ParamByName("GroupId")->AsInteger = OKBottomDlg->DataSource1->DataSet->Fields->FieldByName("GroupId")->AsInteger;
                Query3->ParamByName("AvgMark")->AsFloat = OKBottomDlg->Edit2->Text.ToDouble();
                Query3->ParamByName("Lang")->AsString = OKBottomDlg->Edit3->Text;

                //OKBottomDlg->Query1->Active=false;
                //OKBottomDlg->Query2->Active=false;
                Query3->ExecSQL();
                //OKBottomDlg->Query1->Active=true;
                //OKBottomDlg->Query2->Active=true;
                Query1->Active=true;
        }
        StatusBar1->SimpleText=AnsiString("Количество студентов: ")+Query1->RecordCount+", количество групп: "+Query2->RecordCount;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N6Click(TObject *Sender)
{
        if(MessageBoxA(0,"Вы действительно хотите удалить эту запись?","Удаление",MB_YESNO)==IDYES)
        {
                Query3->SQL->Clear();
                Query3->SQL->Add("DELETE FROM students WHERE FIO=:FIO");
                Query3->ParamByName("FIO")->AsString = DataSource1->DataSet->Fields->FieldByName("FIO")->AsString;
                Query1->Active=false;
                Query3->ExecSQL();
                Query1->Active=true;
        }
        StatusBar1->SimpleText=AnsiString("Количество студентов: ")+Query1->RecordCount+", количество групп: "+Query2->RecordCount;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N12Click(TObject *Sender)
{
        if(MessageBoxA(0,"Вы действительно хотите удалить эту группу?","Удаление",MB_YESNO)==IDYES)
        {
                Query3->SQL->Clear();
                Query3->SQL->Add("DELETE FROM groups WHERE GroupId=:GroupId");
                Query3->ParamByName("GroupId")->AsInteger = DataSource2->DataSet->Fields->FieldByName("GroupId")->AsInteger;
                Query2->Active=false;
                Query3->ExecSQL();
                Query2->Active=true;
        }
        StatusBar1->SimpleText=AnsiString("Количество студентов: ")+Query1->RecordCount+", количество групп: "+Query2->RecordCount;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N11Click(TObject *Sender)
{
        if(OKBottomDlg2->ShowModal()==mrOk)
        {
                Query2->Active=false;
                Query3->SQL->Clear();
                Query3->SQL->Add("INSERT INTO groups (GroupCode,SpecName,SpecCode) VALUES (:GroupCode,:SpecName,:SpecCode)");
                Query3->ParamByName("GroupCode")->AsString = OKBottomDlg2->LabeledEdit1->Text;
                Query3->ParamByName("SpecCode")->AsInteger = OKBottomDlg2->LabeledEdit2->Text.ToInt();
                Query3->ParamByName("SpecName")->AsString = OKBottomDlg2->LabeledEdit3->Text;
                Query3->ExecSQL();
                Query2->Active=true;
        }
        StatusBar1->SimpleText=AnsiString("Количество студентов: ")+Query1->RecordCount+", количество групп: "+Query2->RecordCount;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::N13Click(TObject *Sender)
{
        AnsiString OldFIO = DataSource1->DataSet->Fields->FieldByName("FIO")->AsString;
        OKBottomDlg->Edit1->Text = OldFIO;
        OKBottomDlg->Edit2->Text = DataSource1->DataSet->Fields->FieldByName("AvgMark")->AsString;
        OKBottomDlg->Edit3->Text = DataSource1->DataSet->Fields->FieldByName("Lang")->AsString;

        if(OKBottomDlg->ShowModal()==mrOk)
        {
                Query1->Active=false;
                Query3->SQL->Clear();
                Query3->SQL->Add("UPDATE students SET  FIO=:FIO, GroupId=:GroupId, AvgMark=:AvgMark, Lang=:Lang WHERE FIO=:OldFIO"); //
                Query3->ParamByName("FIO")->AsString = OKBottomDlg->Edit1->Text;
                Query3->ParamByName("OldFIO")->AsString = OldFIO;
                Query3->ParamByName("GroupId")->AsInteger = OKBottomDlg->DataSource1->DataSet->Fields->FieldByName("GroupId")->AsInteger;
                Query3->ParamByName("AvgMark")->AsFloat = OKBottomDlg->Edit2->Text.ToDouble();
                Query3->ParamByName("Lang")->AsString = OKBottomDlg->Edit3->Text;

                //OKBottomDlg->Query1->Active=false;
                //OKBottomDlg->Query2->Active=false;
                Query3->ExecSQL();
                //OKBottomDlg->Query1->Active=true;
                //OKBottomDlg->Query2->Active=true;
                Query1->Active=true;
        }
        StatusBar1->SimpleText=AnsiString("Количество студентов: ")+Query1->RecordCount+", количество групп: "+Query2->RecordCount;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ToolButton12Click(TObject *Sender)
{
        int OldId = DataSource2->DataSet->Fields->FieldByName("GroupId")->AsInteger;
        OKBottomDlg2->LabeledEdit1->Text = DataSource2->DataSet->Fields->FieldByName("GroupCode")->AsString;
        OKBottomDlg2->LabeledEdit2->Text = DataSource2->DataSet->Fields->FieldByName("SpecName")->AsString;
        OKBottomDlg2->LabeledEdit3->Text = DataSource2->DataSet->Fields->FieldByName("SpecCode")->AsString;

        if(OKBottomDlg2->ShowModal()==mrOk)
        {
                Query2->Active=false;
                Query3->SQL->Clear();
                Query3->SQL->Add("UPDATE groups SET  GroupCode=:GroupCode, SpecName=:SpecName, SpecCode=:SpecCode WHERE GroupId=:OldId"); //
                Query3->ParamByName("OldId")->AsInteger = OldId;
                Query3->ParamByName("GroupCode")->AsString = OKBottomDlg2->LabeledEdit1->Text;
                Query3->ParamByName("SpecName")->AsString = OKBottomDlg2->LabeledEdit2->Text;
                Query3->ParamByName("SpecCode")->AsInteger = OKBottomDlg2->LabeledEdit3->Text.ToInt();

                //OKBottomDlg->Query1->Active=false;
                //OKBottomDlg->Query2->Active=false;
                Query3->ExecSQL();
                //OKBottomDlg->Query1->Active=true;
                //OKBottomDlg->Query2->Active=true;
                Query2->Active=true;
        }
        StatusBar1->SimpleText=AnsiString("Количество студентов: ")+Query1->RecordCount+", количество групп: "+Query2->RecordCount;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::N15Click(TObject *Sender)
{
 Form5->Query1->SQL->Clear();
        Form5->Query1->SQL->Add("SELECT students.FIO AS ФИО_студента, students.AvgMark AS Средняя_оценка, students.Lang AS Иностранный_язык, groups.GroupCode AS Код_группы, groups.SpecName AS Название_специальности, groups.SpecCode AS Код_специальности FROM students INNER JOIN groups ON students.GroupId = groups.GroupId");
        Form5->Query1->Active=true;
        Form5->StatusBar1->SimpleText="Количество записей: " + AnsiString(Form5->Query1->RecordCount);
        Form5->Show();        
}
//---------------------------------------------------------------------------

