object OKBottomDlg2: TOKBottomDlg2
  Left = 504
  Top = 153
  BorderStyle = bsDialog
  Caption = #1044#1086#1073#1072#1074#1080#1090#1100'\'#1080#1079#1084#1077#1085#1080#1090#1100' '#1075#1088#1091#1087#1087#1091
  ClientHeight = 214
  ClientWidth = 313
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 8
    Top = 8
    Width = 297
    Height = 137
    Shape = bsFrame
  end
  object OKBtn: TButton
    Left = 87
    Top = 164
    Width = 75
    Height = 25
    Caption = 'OK'
    Default = True
    ModalResult = 1
    TabOrder = 0
  end
  object CancelBtn: TButton
    Left = 167
    Top = 164
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    ModalResult = 2
    TabOrder = 1
  end
  object LabeledEdit1: TLabeledEdit
    Left = 16
    Top = 32
    Width = 273
    Height = 21
    EditLabel.Width = 58
    EditLabel.Height = 13
    EditLabel.Caption = #1050#1086#1076' '#1075#1088#1091#1087#1087#1099
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 2
    Text = #1040'14-07'
  end
  object LabeledEdit2: TLabeledEdit
    Left = 16
    Top = 72
    Width = 273
    Height = 21
    EditLabel.Width = 99
    EditLabel.Height = 13
    EditLabel.Caption = #1050#1086#1076' '#1089#1087#1077#1094#1080#1072#1083#1100#1085#1086#1089#1090#1080
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 3
    Text = '7654902'
  end
  object LabeledEdit3: TLabeledEdit
    Left = 16
    Top = 112
    Width = 273
    Height = 21
    EditLabel.Width = 130
    EditLabel.Height = 13
    EditLabel.Caption = #1053#1072#1079#1074#1072#1085#1080#1077' '#1089#1087#1077#1094#1080#1072#1083#1100#1085#1086#1089#1090#1080
    LabelPosition = lpAbove
    LabelSpacing = 3
    TabOrder = 4
    Text = #1055#1088#1080#1082#1083#1072#1076#1085#1072#1103' '#1084#1072#1090#1077#1084#1072#1090#1080#1082#1072
  end
end
