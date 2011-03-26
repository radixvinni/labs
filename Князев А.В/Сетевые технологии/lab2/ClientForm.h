//---------------------------------------------------------------------------

#ifndef ClientFormH
#define ClientFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <ScktComp.hpp>
#include "ClientOptions.h"
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TMainMenu *MainMenu1;
        TStatusBar *StatusBar1;
        TMenuItem *A1;
        TMenuItem *N1;
        TMenuItem *N2;
        TMenuItem *N3;
        TListView *list;
        TSplitter *Splitter1;
        TMemo *Memo1;
        TMenuItem *Pf1;
        TMenuItem *select1;
        TMenuItem *use1;
        TMenuItem *N4;
        TClientSocket *ClientSocket1;
        TMenuItem *N5;
        void __fastcall N2Click(TObject *Sender);
        void __fastcall N3Click(TObject *Sender);
        void __fastcall Pf1Click(TObject *Sender);
        void __fastcall select1Click(TObject *Sender);
        void __fastcall use1Click(TObject *Sender);
        void __fastcall ClientSocket1Read(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall N5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
