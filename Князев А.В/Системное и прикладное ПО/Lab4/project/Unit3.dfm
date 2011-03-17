object OKBottomDlg: TOKBottomDlg
  Left = 659
  Top = 235
  BorderStyle = bsDialog
  Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1089#1090#1091#1076#1077#1085#1090#1072
  ClientHeight = 255
  ClientWidth = 313
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 297
    Height = 177
    Shape = bsFrame
  end
  object Label1: TLabel
    Left = 16
    Top = 56
    Width = 35
    Height = 13
    Caption = #1043#1088#1091#1087#1087#1072
  end
  object Label2: TLabel
    Left = 16
    Top = 16
    Width = 75
    Height = 13
    Caption = #1060#1048#1054' '#1089#1090#1091#1076#1077#1085#1090#1072
  end
  object Label3: TLabel
    Left = 16
    Top = 96
    Width = 144
    Height = 13
    Caption = #1057#1088#1077#1076#1085#1103#1103' '#1086#1094#1077#1085#1082#1072' '#1079#1072' '#1101#1082#1079#1072#1084#1077#1085
  end
  object Label4: TLabel
    Left = 16
    Top = 136
    Width = 92
    Height = 13
    Caption = #1048#1085#1089#1090#1088#1072#1085#1085#1099#1081' '#1103#1079#1099#1082
  end
  object OKBtn: TButton
    Left = 79
    Top = 212
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object CancelBtn: TButton
    Left = 159
    Top = 212
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object DBLookupComboBox1: TDBLookupComboBox
    Left = 16
    Top = 72
    Width = 273
    Height = 21
    DataField = 'GroupId'
    DataSource = DataSource2
    KeyField = 'GroupId'
    ListField = 'GroupCode'
    ListSource = DataSource1
    TabOrder = 2
  end
  object Edit1: TEdit
    Left = 16
    Top = 32
    Width = 273
    Height = 21
    TabOrder = 3
    Text = #1042#1080#1085#1085#1080#1082#1086#1074' '#1040#1083#1077#1082#1089#1072#1085#1076#1088' '#1052#1080#1093#1072#1081#1083#1086#1074#1080#1095
  end
  object Edit2: TEdit
    Left = 16
    Top = 112
    Width = 273
    Height = 21
    TabOrder = 4
    Text = '4'
  end
  object Edit3: TEdit
    Left = 16
    Top = 152
    Width = 273
    Height = 21
    TabOrder = 5
    Text = #1040#1085#1075#1083#1080#1081#1089#1082#1080#1081
  end
  object DataSource1: TDataSource
    DataSet = Table1
    Left = 8
    Top = 192
  end
  object Table1: TTable
    Active = True
    AutoRefresh = True
    DatabaseName = '..\'
    TableName = 'groups.db'
    Left = 40
    Top = 192
  end
  object DataSource2: TDataSource
    DataSet = Table2
    Left = 8
    Top = 224
  end
  object Table2: TTable
    Active = True
    AutoRefresh = True
    DatabaseName = '..\'
    TableName = 'students.DB'
    Left = 40
    Top = 224
  end
end
