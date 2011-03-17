object Form1: TForm1
  Left = 282
  Top = 186
  Width = 870
  Height = 640
  Caption = #1048#1085#1080#1094#1080#1072#1083#1100#1085#1099#1081' '#1082#1086#1085#1077#1095#1085#1099#1081' '#1072#1074#1090#1086#1084#1072#1090
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
    Left = 409
    Top = 0
    Width = 3
    Height = 567
    Cursor = crHSplit
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 567
    Width = 862
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object Memo1: TMemo
    Left = 0
    Top = 0
    Width = 409
    Height = 567
    Align = alLeft
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Courier New'
    Font.Style = []
    Lines.Strings = (
      '010201120212')
    ParentFont = False
    TabOrder = 1
  end
  object Memo2: TMemo
    Left = 412
    Top = 0
    Width = 450
    Height = 567
    Align = alClient
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Courier New'
    Font.Style = []
    Lines.Strings = (
      #1056#1077#1079#1091#1083#1100#1090#1080#1088#1091#1102#1097#1072#1103' '#1094#1077#1087#1086#1095#1082#1072' (a,b,k)')
    ParentFont = False
    TabOrder = 2
  end
  object MainMenu1: TMainMenu
    Left = 536
    Top = 152
    object N1: TMenuItem
      Caption = #1040#1074#1090#1086#1084#1072#1090
      object N2: TMenuItem
        Caption = #1054#1073#1088#1072#1073#1086#1090#1072#1090#1100' '#1094#1077#1087#1086#1095#1082#1091
        OnClick = N2Click
      end
    end
  end
end
