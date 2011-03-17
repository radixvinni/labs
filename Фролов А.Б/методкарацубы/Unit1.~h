//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TButton *Button1;
        TButton *Button2;
        TEdit *Edit2;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
        void out(int pos,int &x, int &y, AnsiString s, int a, int b, int c);
        void str(int lvl, int &x, int &y, int a, int b, int l,int n,int k, int& superbase);
        void str2(int lvl, int &x, int &y, int a, int b, int l,int n,int k, int& superbase);
        int mul(int x, int y);
public:		// User declarations
        int n;
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
