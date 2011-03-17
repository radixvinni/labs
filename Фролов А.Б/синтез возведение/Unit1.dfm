object Form1: TForm1
  Left = 283
  Top = 165
  Width = 629
  Height = 352
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
  DesignSize = (
    621
    318)
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
    Width = 9
    Height = 13
    Caption = 't='
  end
  object Label4: TLabel
    Left = 232
    Top = 12
    Width = 14
    Height = 13
    Caption = 'm='
  end
  object Edit1: TEdit
    Left = 296
    Top = 8
    Width = 25
    Height = 21
    TabOrder = 0
    Text = '5'
  end
  object Button1: TButton
    Left = 327
    Top = 8
    Width = 82
    Height = 25
    Caption = #1042#1086#1079#1074#1077#1076#1077#1085#1080#1077
    TabOrder = 1
    OnClick = Button1Click
  end
  object ComboBox1: TComboBox
    Left = 8
    Top = 8
    Width = 121
    Height = 21
    ItemHeight = 13
    ItemIndex = 1
    TabOrder = 2
    Text = 'PolynomGF3'
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
    TabOrder = 3
    Text = '1'
  end
  object Edit3: TEdit
    Left = 200
    Top = 8
    Width = 25
    Height = 21
    TabOrder = 4
    Text = '2'
  end
  object Edit4: TEdit
    Left = 248
    Top = 8
    Width = 25
    Height = 21
    TabOrder = 5
    Text = '4'
  end
  object s: TMemo
    Left = 8
    Top = 40
    Width = 609
    Height = 272
    Anchors = [akLeft, akTop, akRight, akBottom]
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Courier New'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 6
  end
end
