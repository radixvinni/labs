object Form1: TForm1
  Left = 716
  Top = 133
  Width = 519
  Height = 500
  Caption = #1054#1089#1085#1086#1074#1099' '#1087#1086#1089#1090#1088#1086#1077#1085#1080#1103' '#1090#1088#1072#1085#1089#1083#1103#1090#1086#1088#1086#1074
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Splitter1: TSplitter
    Left = 241
    Top = 0
    Width = 3
    Height = 427
    Cursor = crHSplit
  end
  object Memo1: TMemo
    Left = 0
    Top = 0
    Width = 241
    Height = 427
    Align = alLeft
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Courier New'
    Font.Style = [fsBold]
    Lines.Strings = (
      'd=2+3+1;'
      'a=3+2*d;'
      'c=2*d+3*a;'
      #1045#1057#1051#1048'(d>c)'
      #9'a=d*2;'
      #1048#1053#1040#1063#1045
      #9'a=d;'
      #1050#1054#1053#1045#1062'_'#1045#1057#1051#1048
      'i=1;'
      #1062#1048#1050#1051'_'#1055#1054#1050#1040'(i<10)'
      #9'i=i+1;'
      #1050#1054#1053#1045#1062'_'#1062#1048#1050#1051)
    ParentFont = False
    TabOrder = 0
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 427
    Width = 511
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object Panel1: TPanel
    Left = 244
    Top = 0
    Width = 267
    Height = 427
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 2
    object Splitter2: TSplitter
      Left = 1
      Top = 217
      Width = 265
      Height = 3
      Cursor = crVSplit
      Align = alTop
    end
    object sg2: TStringGrid
      Left = 1
      Top = 220
      Width = 265
      Height = 206
      Align = alClient
      ColCount = 3
      DefaultRowHeight = 16
      FixedCols = 0
      RowCount = 2
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Courier New'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      ColWidths = (
        120
        51
        64)
    end
    object l: TListBox
      Left = 1
      Top = 1
      Width = 265
      Height = 216
      Align = alTop
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Courier New'
      Font.Style = []
      ItemHeight = 14
      ParentFont = False
      TabOrder = 1
    end
  end
  object MainMenu1: TMainMenu
    Left = 272
    Top = 8
    object N1: TMenuItem
      Caption = '&'#1060#1072#1081#1083
      object N2: TMenuItem
        Caption = '&'#1042#1099#1093#1086#1076
      end
    end
    object N21: TMenuItem
      Caption = #1051#1072#1073'2'
      object N3: TMenuItem
        Caption = #1047#1072#1087#1091#1089#1090#1080#1090#1100' '#1094#1080#1082#1083
        OnClick = N3Click
      end
    end
    object N31: TMenuItem
      Caption = #1051#1072#1073'3'
      OnClick = N31Click
    end
    object N4: TMenuItem
      Caption = #1051#1072#1073'4'
      OnClick = N4Click
    end
    object N41: TMenuItem
      Caption = #1064#1072#1075'>'
      OnClick = N41Click
    end
    object N6: TMenuItem
      Caption = #1055#1091#1089#1082'>>'
      OnClick = N6Click
    end
    object N5: TMenuItem
      Caption = #1057#1090#1086#1087'-|'
      OnClick = N5Click
    end
  end
end
