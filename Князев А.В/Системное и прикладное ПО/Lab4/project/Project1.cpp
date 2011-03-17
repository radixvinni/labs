//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", Form1);
USEFORM("Unit3.cpp", OKBottomDlg);
USEFORM("Unit4.cpp", OKBottomDlg1);
USEFORM("Unit5.cpp", Form5);
USEFORM("Unit2.cpp", OKBottomDlg2);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TOKBottomDlg), &OKBottomDlg);
                 Application->CreateForm(__classid(TOKBottomDlg1), &OKBottomDlg1);
                 Application->CreateForm(__classid(TForm5), &Form5);
                 Application->CreateForm(__classid(TOKBottomDlg2), &OKBottomDlg2);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
