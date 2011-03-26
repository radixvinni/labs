object Form2: TForm2
  Left = 301
  Top = 146
  Width = 502
  Height = 423
  Caption = #1054#1082#1085#1086' SQL '#1082#1083#1080#1077#1085#1090#1072
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
    Left = 0
    Top = 65
    Width = 494
    Height = 3
    Cursor = crVSplit
    Align = alTop
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 350
    Width = 494
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object list: TListView
    Left = 0
    Top = 68
    Width = 494
    Height = 282
    Align = alClient
    Columns = <
      item
        Caption = 'Result'
        Width = 100
      end>
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    GridLines = True
    RowSelect = True
    ParentFont = False
    TabOrder = 1
    ViewStyle = vsReport
  end
  object Memo1: TMemo
    Left = 0
    Top = 0
    Width = 494
    Height = 65
    Align = alTop
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Lucida Console'
    Font.Style = []
    Lines.Strings = (
      'use base1')
    ParentFont = False
    TabOrder = 2
  end
  object MainMenu1: TMainMenu
    Left = 456
    Top = 8
    object A1: TMenuItem
      Caption = '&'#1060#1072#1081#1083
      object N5: TMenuItem
        Caption = '&'#1057#1086#1077#1076#1080#1085#1080#1090#1100'...'
        OnClick = N5Click
      end
      object N3: TMenuItem
        Caption = '&'#1042#1099#1093#1086#1076
        OnClick = N3Click
      end
    end
    object N4: TMenuItem
      Caption = #1047#1072#1087#1088#1086#1089
      object use1: TMenuItem
        Caption = 'use'
        OnClick = use1Click
      end
      object select1: TMenuItem
        Caption = 'select'
        OnClick = select1Click
      end
    end
    object Pf1: TMenuItem
      Caption = '&'#1042#1099#1087#1086#1083#1085#1080#1090#1100
      OnClick = Pf1Click
    end
    object N1: TMenuItem
      Caption = '&'#1055#1086#1084#1086#1097#1100
      object N2: TMenuItem
        Caption = '&'#1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
        OnClick = N2Click
      end
    end
  end
  object ClientSocket1: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Host = 'localhost'
    Port = 70
    OnRead = ClientSocket1Read
    Left = 424
    Top = 8
  end
end
