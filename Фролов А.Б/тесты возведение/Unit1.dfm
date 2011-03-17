object Form1: TForm1
  Left = 307
  Top = 284
  Width = 490
  Height = 189
  Caption = 
    #1075#1077#1085#1077#1088#1072#1090#1086#1088' '#1090#1077#1089#1090#1086#1074' - '#1074#1086#1079#1074#1077#1076#1077#1085#1080#1077' '#1074' '#1089#1090#1077#1087#1077#1085#1100' '#1093#1072#1088#1072#1082#1090#1077#1088#1080#1089#1090#1080#1082#1080' '#1082#1086#1085#1077#1095#1085#1086#1075#1086 +
    ' '#1087#1086#1083#1103
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCanResize = FormCanResize
  DesignSize = (
    482
    155)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 136
    Top = 11
    Width = 12
    Height = 13
    Caption = 'a='
  end
  object Label2: TLabel
    Left = 184
    Top = 11
    Width = 12
    Height = 13
    Caption = 'b='
  end
  object Label3: TLabel
    Left = 280
    Top = 12
    Width = 15
    Height = 13
    Caption = 't=5'
  end
  object Label4: TLabel
    Left = 232
    Top = 12
    Width = 14
    Height = 13
    Caption = 'm='
  end
  object Edit1: TEdit
    Left = 304
    Top = 8
    Width = 83
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 0
    Text = '01201'
    OnChange = Edit1Change
  end
  object Button1: TButton
    Left = 391
    Top = 8
    Width = 82
    Height = 25
    Anchors = [akTop, akRight]
    Caption = #1042#1086#1079#1074#1077#1076#1077#1085#1080#1077
    TabOrder = 1
    OnClick = Button1Click
  end
  object s: TStringGrid
    Left = 2
    Top = 34
    Width = 475
    Height = 117
    Anchors = [akLeft, akTop, akRight, akBottom]
    ColCount = 12
    DefaultColWidth = 48
    FixedCols = 0
    RowCount = 3
    FixedRows = 0
    TabOrder = 2
  end
  object ComboBox1: TComboBox
    Left = 8
    Top = 8
    Width = 121
    Height = 21
    ItemHeight = 13
    ItemIndex = 1
    TabOrder = 3
    Text = 'PolynomGF3'
    OnChange = ComboBox1Change
    Items.Strings = (
      'PolynomGF2'
      'PolynomGF3'
      'PolynomGF7')
  end
  object Edit2: TEdit
    Left = 152
    Top = 8
    Width = 25
    Height = 21
    TabOrder = 4
    Text = '1'
  end
  object Edit3: TEdit
    Left = 200
    Top = 8
    Width = 25
    Height = 21
    TabOrder = 5
    Text = '2'
  end
  object Edit4: TEdit
    Left = 248
    Top = 8
    Width = 25
    Height = 21
    TabOrder = 6
    Text = '4'
  end
end
