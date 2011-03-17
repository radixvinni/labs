object Form1: TForm1
  Left = 240
  Top = 274
  Width = 870
  Height = 211
  Caption = #1057#1093#1077#1084#1072' '#1043#1088#1080#1085#1072
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object sg: TStringGrid
    Left = 0
    Top = 57
    Width = 862
    Height = 120
    Align = alClient
    ColCount = 2
    FixedCols = 0
    RowCount = 1
    FixedRows = 0
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goEditing, goAlwaysShowEditor]
    TabOrder = 0
    RowHeights = (
      24)
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 862
    Height = 57
    Align = alTop
    TabOrder = 1
    object Label1: TLabel
      Left = 8
      Top = 8
      Width = 125
      Height = 13
      Caption = #1056#1072#1079#1084#1077#1088'('#1089#1090#1077#1087#1077#1085#1100' '#1076#1074#1086#1081#1082#1080')'
    end
    object Edit1: TEdit
      Left = 8
      Top = 24
      Width = 121
      Height = 21
      TabOrder = 0
      Text = '1'
    end
    object Button1: TButton
      Left = 144
      Top = 16
      Width = 75
      Height = 25
      Caption = #1047#1072#1076#1072#1090#1100
      TabOrder = 1
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 224
      Top = 16
      Width = 75
      Height = 25
      Caption = #1042#1099#1095#1080#1089#1083#1080#1090#1100
      TabOrder = 2
      OnClick = Button2Click
    end
  end
end
