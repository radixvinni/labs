//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
#include "Unit2.h"

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TSplitter *Splitter1;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TMenuItem *N3;
        TMenuItem *N2;
        TMenuItem *N4;
        TPaintBox *i;
        TGroupBox *GroupBox1;
        TButton *ButtonNewA;
        TLabeledEdit *EditA;
        TLabeledEdit *EditB;
        TLabeledEdit *EditC;
        TLabeledEdit *EditD;
        TOpenDialog *ofd;
        TSaveDialog *sfd;
        TMenuItem *N5;
        TMenuItem *N6;
        TLabel *Label1;
        TListBox *l;
        void __fastcall N4Click(TObject *Sender);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall N5Click(TObject *Sender);
        void __fastcall N6Click(TObject *Sender);
        void __fastcall iPaint(TObject *Sender);
        void __fastcall ButtonNewAClick(TObject *Sender);
        void __fastcall iMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall iMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
        void __fastcall lClick(TObject *Sender);
private:	// User declarations
        struct Drawer;
        Graf graf;
        int temp;
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
