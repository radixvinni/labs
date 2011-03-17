object Form1: TForm1
  Left = 712
  Top = 222
  Width = 524
  Height = 327
  Caption = #1052#1072#1089#1089#1080#1074
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    516
    293)
  PixelsPerInch = 96
  TextHeight = 13
  object s: TPaintBox
    Left = 259
    Top = 38
    Width = 249
    Height = 246
    Anchors = [akLeft, akTop, akRight, akBottom]
    OnPaint = sPaint
  end
  object Edit1: TEdit
    Left = 8
    Top = 8
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object Edit2: TEdit
    Left = 136
    Top = 8
    Width = 129
    Height = 21
    TabOrder = 1
  end
  object Button1: TButton
    Left = 272
    Top = 8
    Width = 75
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100
    TabOrder = 2
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 352
    Top = 8
    Width = 75
    Height = 25
    Caption = #1055#1086#1080#1089#1082
    TabOrder = 3
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 432
    Top = 8
    Width = 75
    Height = 25
    Caption = #1059#1076#1072#1083#1077#1085#1080#1077
    TabOrder = 4
    OnClick = Button3Click
  end
  object v: TValueListEditor
    Left = 8
    Top = 40
    Width = 241
    Height = 244
    Anchors = [akLeft, akTop, akBottom]
    TabOrder = 5
    ColWidths = (
      89
      146)
  end
end
