object Form1: TForm1
  Left = 299
  Top = 170
  Width = 870
  Height = 640
  Caption = #1040#1083#1075#1086#1088#1080#1090#1084#1099' '#1052#1072#1088#1082#1086#1074#1072
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
  object p: TMemo
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
      '1000111')
    ParentFont = False
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object scheme: TMemo
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
      'a0->0a'
      'a1->1a'
      'a->b'
      '0b->b1'
      '1b->*0'
      '->a')
    ParentFont = False
    TabOrder = 2
  end
  object MainMenu1: TMainMenu
    Left = 536
    Top = 152
    object N1: TMenuItem
      Caption = #1057#1093#1077#1084#1072
      object N3: TMenuItem
        Caption = #1042#1099#1095#1080#1090#1072#1085#1080#1077' '#1077#1076#1080#1085#1080#1094#1099
        OnClick = N3Click
      end
      object N4: TMenuItem
        Caption = #1047#1077#1088#1082#1072#1083#1100#1085#1086#1077' '#1086#1090#1086#1073#1088#1072#1078#1077#1085#1080#1077
        OnClick = N4Click
      end
      object N5: TMenuItem
        Caption = #1047#1072#1087#1080#1089#1072#1090#1100' '#1087#1072#1083#1086#1095#1082#1072#1084#1080
        OnClick = N5Click
      end
    end
    object N2: TMenuItem
      Caption = #1054#1073#1088#1072#1073#1086#1090#1072#1090#1100' '#1089#1083#1086#1074#1086
      OnClick = N2Click
    end
  end
end
