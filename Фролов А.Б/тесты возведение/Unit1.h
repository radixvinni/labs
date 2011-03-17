//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TButton *Button1;
        TStringGrid *s;
        TComboBox *ComboBox1;
        TLabel *Label1;
        TEdit *Edit2;
        TLabel *Label2;
        TEdit *Edit3;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit4;
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall FormCanResize(TObject *Sender, int &NewWidth,
          int &NewHeight, bool &Resize);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
        void Compensate(int i, int j, int val);
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
