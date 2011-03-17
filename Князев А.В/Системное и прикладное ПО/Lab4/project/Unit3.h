//----------------------------------------------------------------------------
#ifndef Unit3H
#define Unit3H
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <DBTables.hpp>
#include <Mask.hpp>
//----------------------------------------------------------------------------
class TOKBottomDlg : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
        TLabel *Label1;
        TLabel *Label2;
        TDataSource *DataSource1;
        TTable *Table1;
        TDBLookupComboBox *DBLookupComboBox1;
        TDataSource *DataSource2;
        TTable *Table2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
private:
public:
	virtual __fastcall TOKBottomDlg(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TOKBottomDlg *OKBottomDlg;
//----------------------------------------------------------------------------
#endif    
