object FormTestSerial: TFormTestSerial
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'ProbeSerial'
  ClientHeight = 399
  ClientWidth = 552
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  DesignSize = (
    552
    399)
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 12
    Top = 5
    Width = 101
    Height = 13
    Caption = #1057#1087#1080#1089#1086#1082' COM '#1087#1086#1088#1090#1086#1074
  end
  object UpdateSerialList: TBitBtn
    Left = 8
    Top = 279
    Width = 109
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1054#1073#1085#1086#1074#1080#1090#1100
    Glyph.Data = {
      36030000424D3603000000000000360000002800000010000000100000000100
      18000000000000030000C40E0000C40E00000000000000000000FFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFF55C068FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF3EDA5AFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFF3FB24C60FA7B3C8E454A8B53458C4E538A5AFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4A8B5344E15C4BE26560FA7B60
      FA7B58ED713DD6572F943BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFF3CCB514ACF6044D35A4BE2654EDD6548D65E48D65E44DE5F2AB43CFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF4A8B5335BC4850D5664EDD655C
      8D63FFFFFFFFFFFF5B956335BC482F943BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFF57955D3CC35057755CFFFFFFFFFFFFFFFFFFFFFFFF3C8E
      45FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF6F8F71FFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFF2F943B3C8E45FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFF4AB55653A55CFFFFFFFFFFFFFFFFFF4A8B533DD65722AB333C8E45FFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF57955D58ED714AB5563C8E4544
      9F4B46995147D95D39C84D24BF3917A327FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFF57955D58ED716BF78478FD9060FA7B58ED714EDD6544D35A4A8B
      53FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF59AA6253A55C5C
      CF6966D26F60DC7472F18A52BA5BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF59AA626BF784FFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFF57A85FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF}
    TabOrder = 0
    OnClick = UpdateSerialListClick
  end
  object ListBox_COM_Ports: TListBox
    Left = 8
    Top = 24
    Width = 109
    Height = 249
    Anchors = [akLeft, akTop, akBottom]
    ItemHeight = 13
    TabOrder = 1
  end
  object BitBtnConnect: TBitBtn
    Left = 8
    Top = 370
    Width = 109
    Height = 25
    Anchors = [akLeft, akBottom]
    Caption = #1055#1086#1076#1082#1083#1102#1095#1080#1090#1100#1089#1103
    Glyph.Data = {
      36030000424D3603000000000000360000002800000010000000100000000100
      18000000000000030000C40E0000C40E00000000000000000000FFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD1D1D14D4D4D2929
      294D4D4DD1D1D1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFC9C9C9292929E7E7E7FFFFFFE7E7E7292929D1D1D1FFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF393939E7E7E7FFFFFFFFFF
      FFFFFFFFE7E7E74D4D4DFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFF131313FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF292929FFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFB6B6B6242424EBEBEBFFFFFFFFFF
      FFFFFFFFE7E7E74D4D4DFFFFFFC9C9C9393939121212383838D2D2D2D5D5D545
      45452F2F2F303030383838E7E7E7FFFFFFE7E7E7292929D1D1D1D1D1D1292929
      E7E7E7FFFFFFE7E7E73838383030302E2E2E4A4A4AD8D8D8D2D2D23838381212
      12393939C9C9C9FFFFFF4D4D4DE7E7E7FFFFFFFFFFFFFFFFFFEBEBEB292929C2
      C2C2FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF292929FFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFF161616FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFF4D4D4DE7E7E7FFFFFFFFFFFFFFFFFFEBEBEB2D2D2D45
      4545B3B3B3FFFFFFCACACA383838121212393939C9C9C9FFFFFFD1D1D1292929
      E7E7E7FFFFFFE7E7E73838383A3A3A3232323232323A3A3A383838E7E7E7FFFF
      FFE7E7E7292929D1D1D1FFFFFFC9C9C9393939121212383838CACACAFFFFFFB3
      B3B34545452D2D2DEBEBEBFFFFFFFFFFFFFFFFFFE7E7E74D4D4DFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF141414FFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFF292929FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFF393939E7E7E7FFFFFFFFFFFFFFFFFFE7E7E74D4D4DFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFC9C9C9292929E7E7E7FFFF
      FFE7E7E7292929D1D1D1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFD1D1D14D4D4D2929294D4D4DD1D1D1FFFFFF}
    TabOrder = 2
    OnClick = BitBtnConnectClick
  end
  object ComboBoxBaudRate: TComboBox
    Left = 8
    Top = 308
    Width = 109
    Height = 21
    Style = csDropDownList
    Anchors = [akLeft, akBottom]
    TabOrder = 3
  end
  object GroupBoxDevice: TGroupBox
    Left = 123
    Top = 8
    Width = 421
    Height = 383
    Anchors = [akLeft, akTop, akRight, akBottom]
    Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077
    TabOrder = 4
    object Label5: TLabel
      Left = 16
      Top = 85
      Width = 69
      Height = 13
      Caption = #1062#1040#1055' '#1082#1072#1085#1072#1083' '#1040':'
    end
    object Label6: TLabel
      Left = 16
      Top = 116
      Width = 68
      Height = 13
      Caption = #1062#1040#1055' '#1082#1072#1085#1072#1083' B:'
    end
    object Label7: TLabel
      Left = 13
      Top = 174
      Width = 77
      Height = 13
      Caption = #1047#1085#1072#1095#1077#1085#1080#1077' '#1040#1062#1055':'
    end
    object Label2: TLabel
      Left = 13
      Top = 201
      Width = 76
      Height = 13
      Caption = 'ID '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1072':'
    end
    object Label3: TLabel
      Left = 77
      Top = 242
      Width = 106
      Height = 13
      Caption = #1057#1086#1089#1090#1086#1103#1085#1080#1077' '#1082#1085#1086#1087#1086#1082
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 80
      Top = 261
      Width = 19
      Height = 13
      Caption = 'Run'
    end
    object Label8: TLabel
      Left = 122
      Top = 261
      Width = 13
      Height = 13
      Caption = 'Up'
    end
    object Label9: TLabel
      Left = 156
      Top = 261
      Width = 27
      Height = 13
      Caption = 'Down'
    end
    object Label10: TLabel
      Left = 19
      Top = 287
      Width = 26
      Height = 13
      Caption = 'Press'
    end
    object Label11: TLabel
      Left = 19
      Top = 329
      Width = 49
      Height = 13
      Caption = 'LongPress'
    end
    object ButtonGetStatus: TButton
      Left = 13
      Top = 24
      Width = 116
      Height = 25
      Caption = #1047#1072#1087#1088#1086#1089' '#1089#1086#1089#1090#1086#1103#1085#1080#1103
      TabOrder = 0
      OnClick = ButtonGetStatusClick
    end
    object StatusBar1: TStatusBar
      Left = 2
      Top = 362
      Width = 417
      Height = 19
      Panels = <
        item
          Width = 50
        end>
    end
    object CheckBoxRelay: TCheckBox
      Left = 152
      Top = 28
      Width = 49
      Height = 17
      Caption = #1056#1101#1083#1077
      TabOrder = 2
      OnClick = CheckBoxRelayClick
    end
    object EditADC: TEdit
      Left = 96
      Top = 171
      Width = 97
      Height = 21
      ReadOnly = True
      TabOrder = 3
    end
    object ButtonGetADC: TButton
      Left = 199
      Top = 169
      Width = 58
      Height = 25
      Caption = #1047#1072#1087#1088#1086#1089
      TabOrder = 4
      OnClick = ButtonGetADCClick
    end
    object EditDeviceID: TEdit
      Left = 96
      Top = 198
      Width = 97
      Height = 21
      ReadOnly = True
      TabOrder = 5
    end
    object ButtonGetDeviceID: TButton
      Left = 199
      Top = 196
      Width = 58
      Height = 25
      Caption = #1047#1072#1087#1088#1086#1089
      TabOrder = 6
      OnClick = ButtonGetDeviceIDClick
    end
    object PanelRunPress: TPanel
      Left = 74
      Top = 280
      Width = 33
      Height = 33
      Color = clSilver
      ParentBackground = False
      ShowCaption = False
      TabOrder = 7
    end
    object PanelUpPress: TPanel
      Left = 113
      Top = 280
      Width = 33
      Height = 33
      Color = clSilver
      ParentBackground = False
      ShowCaption = False
      TabOrder = 8
    end
    object PanelDownPress: TPanel
      Left = 152
      Top = 280
      Width = 33
      Height = 33
      Color = clSilver
      ParentBackground = False
      ShowCaption = False
      TabOrder = 9
    end
    object PanelRunLongPress: TPanel
      Left = 74
      Top = 319
      Width = 33
      Height = 33
      Color = clSilver
      ParentBackground = False
      ShowCaption = False
      TabOrder = 10
    end
    object PanelUpLongPress: TPanel
      Left = 113
      Top = 319
      Width = 33
      Height = 33
      Color = clSilver
      ParentBackground = False
      ShowCaption = False
      TabOrder = 11
    end
    object PanelDownLongPress: TPanel
      Left = 152
      Top = 319
      Width = 33
      Height = 33
      Color = clSilver
      ParentBackground = False
      ShowCaption = False
      TabOrder = 12
    end
    object ButtonGetBtnState: TButton
      Left = 199
      Top = 307
      Width = 58
      Height = 25
      Caption = #1047#1072#1087#1088#1086#1089
      TabOrder = 13
      OnClick = ButtonGetBtnStateClick
    end
    object CheckBoxAutoGetBtnState: TCheckBox
      Left = 199
      Top = 284
      Width = 97
      Height = 17
      Caption = #1040#1074#1090#1086#1086#1087#1088#1086#1089
      TabOrder = 14
      OnClick = CheckBoxAutoGetBtnStateClick
    end
    object TrackBarDAC_A: TTrackBar
      Left = 137
      Top = 81
      Width = 200
      Height = 28
      Max = 4095
      PageSize = 1
      PositionToolTip = ptTop
      ShowSelRange = False
      TabOrder = 15
      TickMarks = tmBoth
      TickStyle = tsNone
      OnChange = TrackBarDAC_AChange
    end
    object TrackBarDAC_B: TTrackBar
      Left = 137
      Top = 112
      Width = 200
      Height = 25
      Max = 4095
      PageSize = 1
      PositionToolTip = ptTop
      ShowSelRange = False
      TabOrder = 16
      TickMarks = tmBoth
      TickStyle = tsNone
      OnChange = TrackBarDAC_BChange
    end
    object EditDAC_A: TEdit
      Left = 87
      Top = 82
      Width = 50
      Height = 21
      NumbersOnly = True
      TabOrder = 17
      Text = '0'
      OnChange = EditDAC_AChange
      OnKeyDown = EditDAC_AKeyDown
    end
    object EditDAC_B: TEdit
      Left = 87
      Top = 113
      Width = 50
      Height = 21
      NumbersOnly = True
      TabOrder = 18
      Text = '0'
      OnChange = EditDAC_BChange
      OnKeyDown = EditDAC_BKeyDown
    end
    object ButtonSetDAC_A: TButton
      Left = 336
      Top = 80
      Width = 75
      Height = 25
      Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
      TabOrder = 19
      OnClick = ButtonSetDAC_AClick
    end
    object ButtonSetDAC_B: TButton
      Left = 336
      Top = 112
      Width = 75
      Height = 25
      Caption = #1055#1088#1080#1084#1077#1085#1080#1090#1100
      TabOrder = 20
      OnClick = ButtonSetDAC_BClick
    end
    object TrackBarAutoGetButtonStatePeriod: TTrackBar
      Left = 278
      Top = 280
      Width = 131
      Height = 28
      Max = 2000
      Min = 10
      PageSize = 1
      Position = 10
      PositionToolTip = ptTop
      ShowSelRange = False
      TabOrder = 21
      TickMarks = tmBoth
      TickStyle = tsNone
    end
  end
  object TimerAutoClearStatus: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = TimerAutoClearStatusTimer
  end
end
