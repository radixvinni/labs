object Form1: TForm1
  Left = 368
  Top = 112
  Width = 859
  Height = 471
  Caption = #1043#1088#1072#1092
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
    Left = 680
    Top = 0
    Width = 3
    Height = 398
    Cursor = crHSplit
    Align = alRight
  end
  object i: TPaintBox
    Left = 0
    Top = 0
    Width = 680
    Height = 398
    Align = alClient
    OnMouseDown = iMouseDown
    OnMouseUp = iMouseUp
    OnPaint = iPaint
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 398
    Width = 851
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object GroupBox1: TGroupBox
    Left = 683
    Top = 0
    Width = 168
    Height = 398
    Align = alRight
    Caption = #1044#1072#1085#1085#1099#1077
    TabOrder = 1
    DesignSize = (
      168
      398)
    object Label1: TLabel
      Left = 12
      Top = 176
      Width = 77
      Height = 13
      Caption = #1053#1072#1081#1076#1085#1085#1099#1077' '#1087#1091#1090#1080
    end
    object ButtonNewA: TButton
      Left = 9
      Top = 352
      Width = 148
      Height = 33
      Anchors = [akLeft, akTop, akRight]
      Caption = #1044#1086#1073#1072#1074#1080#1090#1100' '#1091#1079#1077#1083
      TabOrder = 0
      OnClick = ButtonNewAClick
    end
    object EditA: TLabeledEdit
      Left = 9
      Top = 30
      Width = 148
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      EditLabel.Width = 102
      EditLabel.Height = 13
      EditLabel.Caption = #1053#1072#1095#1072#1083#1100#1085#1072#1103' '#1074#1077#1088#1096#1080#1085#1072
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 1
      OnChange = iPaint
    end
    object EditB: TLabeledEdit
      Left = 8
      Top = 72
      Width = 149
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      EditLabel.Width = 95
      EditLabel.Height = 13
      EditLabel.Caption = #1050#1086#1085#1077#1095#1085#1072#1103' '#1074#1077#1088#1096#1080#1085#1072
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 2
      OnChange = iPaint
    end
    object EditC: TLabeledEdit
      Left = 8
      Top = 112
      Width = 149
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      EditLabel.Width = 128
      EditLabel.Height = 13
      EditLabel.Caption = #1055#1088#1086#1084#1077#1078#1091#1090#1086#1095#1085#1072#1103' '#1074#1077#1088#1096#1080#1085#1072
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 3
      OnChange = iPaint
    end
    object EditD: TLabeledEdit
      Left = 8
      Top = 152
      Width = 149
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      AutoSize = False
      EditLabel.Width = 123
      EditLabel.Height = 13
      EditLabel.Caption = #1053#1072#1087#1088#1072#1074#1083#1077#1085#1080' '#1085#1072' '#1074#1077#1088#1096#1080#1085#1091
      LabelPosition = lpAbove
      LabelSpacing = 3
      TabOrder = 4
      OnChange = iPaint
    end
    object l: TListBox
      Left = 8
      Top = 192
      Width = 150
      Height = 153
      Anchors = [akLeft, akTop, akRight]
      ItemHeight = 13
      TabOrder = 5
      OnClick = lClick
    end
  end
  object MainMenu1: TMainMenu
    Left = 760
    Top = 392
    object N1: TMenuItem
      Caption = #1044#1072#1085#1085#1099#1077
      object N5: TMenuItem
        Caption = #1054#1090#1082#1088#1099#1090#1100
        OnClick = N5Click
      end
      object N6: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100
        OnClick = N6Click
      end
      object N3: TMenuItem
        Caption = #1042#1099#1093#1086#1076
        OnClick = N3Click
      end
    end
    object N2: TMenuItem
      Caption = #1057#1087#1088#1072#1074#1082#1072
      object N4: TMenuItem
        Caption = #1054' '#1087#1088#1086#1075#1088#1072#1084#1084#1077
        OnClick = N4Click
      end
    end
  end
  object ofd: TOpenDialog
    Left = 728
    Top = 392
  end
  object sfd: TSaveDialog
    Left = 696
    Top = 392
  end
end
