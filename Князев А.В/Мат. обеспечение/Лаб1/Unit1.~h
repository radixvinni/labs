//---------------------------------------------------------------------------


#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>

//---------------------------------------------------------------------------
#include "Unit2.h"
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TEdit *Edit1;
        TEdit *Edit2;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TPaintBox *s;
        TValueListEditor *v;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall sPaint(TObject *Sender);
private:	// User declarations
        struct Drawer
        {
                int y;
                Drawer():y(0) {}
                void draw(int i, char str[]);
        };
        ArrayMap<Drawer> array;

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
