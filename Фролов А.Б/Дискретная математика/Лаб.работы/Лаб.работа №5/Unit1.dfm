object Form1: TForm1
  Left = 255
  Top = 198
  Width = 867
  Height = 469
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
    Left = 257
    Top = 0
    Width = 3
    Height = 396
    Cursor = crHSplit
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 396
    Width = 859
    Height = 19
    Panels = <>
    SimplePanel = False
  end
  object Memo1: TMemo
    Left = 0
    Top = 0
    Width = 257
    Height = 396
    Align = alLeft
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Courier New'
    Font.Style = []
    Lines.Strings = (
      '110')
    ParentFont = False
    TabOrder = 1
  end
  object Panel1: TPanel
    Left = 260
    Top = 0
    Width = 599
    Height = 396
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 2
    object Splitter2: TSplitter
      Left = 1
      Top = 210
      Width = 597
      Height = 3
      Cursor = crVSplit
      Align = alBottom
    end
    object Splitter3: TSplitter
      Left = 1
      Top = 242
      Width = 597
      Height = 3
      Cursor = crVSplit
      Align = alBottom
    end
    object Memo2: TMemo
      Left = 1
      Top = 1
      Width = 597
      Height = 209
      Align = alClient
      Font.Charset = RUSSIAN_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Courier New'
      Font.Style = []
      Lines.Strings = (
        #1056#1077#1079#1091#1083#1100#1090#1080#1088#1091#1102#1097#1072#1103' '#1094#1077#1087#1086#1095#1082#1072' ')
      ParentFont = False
      ScrollBars = ssVertical
      TabOrder = 0
    end
    object s: TStringGrid
      Left = 1
      Top = 245
      Width = 597
      Height = 150
      Align = alBottom
      ColCount = 9
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goEditing, goAlwaysShowEditor]
      TabOrder = 1
    end
    object Panel2: TPanel
      Left = 1
      Top = 213
      Width = 597
      Height = 29
      Align = alBottom
      Caption = 'Panel2'
      TabOrder = 2
      DesignSize = (
        597
        29)
      object Button1: TButton
        Left = 15
        Top = 2
        Width = 103
        Height = 25
        Anchors = [akLeft, akTop, akBottom]
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1089#1080#1084#1074#1086#1083
        TabOrder = 0
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 120
        Top = 2
        Width = 90
        Height = 25
        Anchors = [akLeft, akTop, akBottom]
        Caption = #1059#1073#1088#1072#1090#1100' '#1089#1080#1084#1074#1086#1083
        TabOrder = 1
        OnClick = Button2Click
      end
      object Button3: TButton
        Left = 212
        Top = 2
        Width = 117
        Height = 25
        Anchors = [akLeft, akTop, akBottom]
        Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1089#1086#1089#1090#1086#1103#1085#1080#1077
        TabOrder = 2
        OnClick = Button3Click
      end
      object Button4: TButton
        Left = 331
        Top = 2
        Width = 112
        Height = 25
        Anchors = [akLeft, akTop, akBottom]
        Caption = #1059#1073#1088#1072#1090#1100' '#1089#1086#1089#1090#1086#1103#1085#1080#1077
        TabOrder = 3
        OnClick = Button4Click
      end
      object Button5: TButton
        Left = 445
        Top = 2
        Width = 116
        Height = 25
        Anchors = [akLeft, akTop, akBottom]
        Caption = #1054#1073#1088#1072#1073#1086#1090#1072#1090#1100' '#1094#1077#1087#1086#1095#1082#1091
        TabOrder = 4
        OnClick = Button5Click
      end
    end
  end
  object MainMenu1: TMainMenu
    Left = 168
    Top = 168
    object N1: TMenuItem
      Caption = #1040#1074#1090#1086#1084#1072#1090
      object N2: TMenuItem
        Caption = #1054#1073#1088#1072#1073#1086#1090#1072#1090#1100' '#1094#1077#1087#1086#1095#1082#1091
        OnClick = N2Click
      end
    end
  end
end
