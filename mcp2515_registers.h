// Configuration Registers
#define MCP_CANSTAT         0x0E
#define MCP_CANCTRL         0x0F
#define MCP_BFPCTRL         0x0C
#define MCP_TEC             0x1C
#define MCP_REC             0x1D
#define MCP_CNF3            0x28
#define MCP_CNF2            0x29
#define MCP_CNF1            0x2A
#define MCP_CANINTE         0x2B
#define MCP_CANINTF         0x2C
#define MCP_EFLG            0x2D
#define MCP_TXRTSCTRL       0x0D

// Receive Filters
#define MCP_RXF0SIDH        0x00
#define MCP_RXF0SIDL        0x01
#define MCP_RXF0EID8        0x02
#define MCP_RXF0EID0        0x03
#define MCP_RXF1SIDH        0x04
#define MCP_RXF1SIDL        0x05
#define MCP_RXF1EID8        0x06
#define MCP_RXF1EID0        0x07
#define MCP_RXF2SIDH        0x08
#define MCP_RXF2SIDL        0x09
#define MCP_RXF2EID8        0x0A
#define MCP_RXF2EID0        0x0B
#define MCP_RXF3SIDH        0x10
#define MCP_RXF3SIDL        0x11
#define MCP_RXF3EID8        0x12
#define MCP_RXF3EID0        0x13
#define MCP_RXF4SIDH        0x14
#define MCP_RXF4SIDL        0x15
#define MCP_RXF4EID8        0x16
#define MCP_RXF4EID0        0x17
#define MCP_RXF5SIDH        0x18
#define MCP_RXF5SIDL        0x19
#define MCP_RXF5EID8        0x1A
#define MCP_RXF5EID0        0x1B

// Receive Masks
#define MCP_RXM0SIDH        0x20
#define MCP_RXM0SIDL        0x21
#define MCP_RXM0EID8        0x22
#define MCP_RXM0EID0        0x23
#define MCP_RXM1SIDH        0x24
#define MCP_RXM1SIDL        0x25
#define MCP_RXM1EID8        0x26
#define MCP_RXM1EID0        0x27

// Tx Buffer 0
#define MCP_TXB0CTRL        0x30
#define MCP_TXB0SIDH        0x31
#define MCP_TXB0SIDL        0x32
#define MCP_TXB0EID8        0x33
#define MCP_TXB0EID0        0x34
#define MCP_TXB0DLC         0x35
#define MCP_TXB0D0          0x36
#define MCP_TXB0D1          0x37
#define MCP_TXB0D2          0x38
#define MCP_TXB0D3          0x39
#define MCP_TXB0D4          0x3A
#define MCP_TXB0D5          0x3B
#define MCP_TXB0D6          0x3C
#define MCP_TXB0D7          0x3D

// Tx Buffer 1
#define MCP_TXB1CTRL        0x40
#define MCP_TXB1SIDH        0x41
#define MCP_TXB1SIDL        0x42
#define MCP_TXB1EID8        0x43
#define MCP_TXB1EID0        0x44
#define MCP_TXB1DLC         0x45
#define MCP_TXB1D0          0x46
#define MCP_TXB1D1          0x47
#define MCP_TXB1D2          0x48
#define MCP_TXB1D3          0x49
#define MCP_TXB1D4          0x4A
#define MCP_TXB1D5          0x4B
#define MCP_TXB1D6          0x4C
#define MCP_TXB1D7          0x4D

// Tx Buffer 2
#define MCP_TXB2CTRL        0x50
#define MCP_TXB2SIDH        0x51
#define MCP_TXB2SIDL        0x52
#define MCP_TXB2EID8        0x53
#define MCP_TXB2EID0        0x54
#define MCP_TXB2DLC         0x55
#define MCP_TXB2D0          0x56
#define MCP_TXB2D1          0x57
#define MCP_TXB2D2          0x58
#define MCP_TXB2D3          0x59
#define MCP_TXB2D4          0x5A
#define MCP_TXB2D5          0x5B
#define MCP_TXB2D6          0x5C
#define MCP_TXB2D7          0x5D

// Rx Buffer 0
#define MCP_RXB0CTRL        0x60
#define MCP_RXB0SIDH        0x61
#define MCP_RXB0SIDL        0x62
#define MCP_RXB0EID8        0x63
#define MCP_RXB0EID0        0x64
#define MCP_RXB0DLC         0x65
#define MCP_RXB0D0          0x66
#define MCP_RXB0D1          0x67
#define MCP_RXB0D2          0x68
#define MCP_RXB0D3          0x69
#define MCP_RXB0D4          0x6A
#define MCP_RXB0D5          0x6B
#define MCP_RXB0D6          0x6C
#define MCP_RXB0D7          0x6D

// Rx Buffer 1
#define MCP_RXB1CTRL        0x70
#define MCP_RXB1SIDH        0x71
#define MCP_RXB1SIDL        0x72
#define MCP_RXB1EID8        0x73
#define MCP_RXB1EID0        0x74
#define MCP_RXB1DLC         0x75
#define MCP_RXB1D0          0x76
#define MCP_RXB1D1          0x77
#define MCP_RXB1D2          0x78
#define MCP_RXB1D3          0x79
#define MCP_RXB1D4          0x7A
#define MCP_RXB1D5          0x7B
#define MCP_RXB1D6          0x7C
#define MCP_RXB1D7          0x7D


//******************************************************************
//               Bit register masks
//******************************************************************

// TXBnCTRL
#define MCP_TXREQ           0x08
#define MCP_TXP             0x03

// RXBnCTRL
#define MCP_RXM             0x60
#define MCP_BUKT            0x04

// CANCTRL
#define MCP_REQOP           0xE0
#define MCP_ABAT            0x10
#define MCP_CLKEN           0x04
#define MCP_CLKPRE          0x03

// CANSTAT
#define MCP_REQOP           0xE0
#define MCP_ICOD            0x0E

// CANINTE
#define MCP_RX0IE           0x01
#define MCP_RX1IE           0x02
#define MCP_TX0IE           0x04
#define MCP_TX1IE           0x80
#define MCP_TX2IE           0x10
#define MCP_ERRIE           0x20
#define MCP_WAKIE           0x40
#define MCP_IVMIE           0x80

// CANINTF
#define MCP_RX0IF           0x01
#define MCP_RX1IF           0x02
#define MCP_TX0IF           0x04
#define MCP_TX1IF           0x80
#define MCP_TX2IF           0x10
#define MCP_ERRIF           0x20
#define MCP_WAKIF           0x40
#define MCP_IVMIF           0x80

// BFPCTRL
#define MCP_B1BFS           0x20
#define MCP_B0BFS           0x10
#define MCP_B1BFE           0x08
#define MCP_B0BFE           0x04
#define MCP_B1BFM           0x02
#define MCP_B0BFM           0x01

// CNF1 Masks
#define MCP_SJW             0xC0
#define MCP_BRP             0x3F

// CNF2 Masks
#define MCP_BTLMODE         0x80
#define MCP_SAM             0x40
#define MCP_PHSEG1          0x38
#define MCP_PRSEG           0x07

// CNF3 Masks
#define MCP_WAKFIL          0x40
#define MCP_PHSEG2          0x07

// TXRTSCTRL Masks
#define MCP_TXB2RTS         0x04
#define MCP_TXB1RTS         0x02
#define MCP_TXB0RTS         0x01


//******************************************************************
//                    Bit Timing Configuration
//******************************************************************

// CNF1
#define MCP_SJW_1TQ         0x40
#define MCP_SJW_2TQ         0x80
#define MCP_SJW_3TQ         0x90
#define MCP_SJW_4TQ         0xC0

// CNF2
#define MCP_BTLMODE_CNF3    0x80
#define MCP_BTLMODE_PH1_IPT 0x00

#define MCP_SMPL_3X         0x40
#define MCP_SMPL_1X         0x00

#define MCP_PHSEG1_8TQ      0x38
#define MCP_PHSEG1_7TQ      0x30
#define MCP_PHSEG1_6TQ      0x28
#define MCP_PHSEG1_5TQ      0x20
#define MCP_PHSEG1_4TQ      0x18
#define MCP_PHSEG1_3TQ      0x10
#define MCP_PHSEG1_2TQ      0x08
#define MCP_PHSEG1_1TQ      0x00

#define MCP_PRSEG_8TQ       0x07
#define MCP_PRSEG_7TQ       0x06
#define MCP_PRSEG_6TQ       0x05
#define MCP_PRSEG_5TQ       0x04
#define MCP_PRSEG_4TQ       0x03
#define MCP_PRSEG_3TQ       0x02
#define MCP_PRSEG_2TQ       0x01
#define MCP_PRSEG_1TQ       0x00

// CNF3
#define MCP_PHSEG2_8TQ      0x07
#define MCP_PHSEG2_7TQ      0x06
#define MCP_PHSEG2_6TQ      0x05
#define MCP_PHSEG2_5TQ      0x04
#define MCP_PHSEG2_4TQ      0x03
#define MCP_PHSEG2_3TQ      0x02
#define MCP_PHSEG2_2TQ      0x01
#define MCP_PHSEG2_1TQ      0x00

#define MCP_WAKFIL_ENABLED  0x40
#define MCP_WAKFIL_DISABLED 0x00


//******************************************************************
//                  Control/Configuration Registers
//******************************************************************

// CANINTE
#define MCP_RX0IE_ENABLED   0x01
#define MCP_RX0IE_DISABLED  0x00
#define MCP_RX1IE_ENABLED   0x02
#define MCP_RX1IE_DISABLED  0x00
#define MCP_G_RXIE_ENABLED  0x03
#define MCP_G_RXIE_DISABLED 0x00

#define MCP_TX0IE_ENABLED   0x04
#define MCP_TX0IE_DISABLED  0x00
#define MCP_TX1IE_ENABLED   0x08
#define MCP_TX2IE_DISABLED  0x00
#define MCP_TX2IE_ENABLED   0x10
#define MCP_TX2IE_DISABLED  0x00
#define MCP_G_TXIE_ENABLED  0x1C
#define MCP_G_TXIE_DISABLED 0x00

#define MCP_ERRIE_ENABLED   0x20
#define MCP_ERRIE_DISABLED  0x00
#define MCP_WAKIE_ENABLED   0x40
#define MCP_WAKIE_DISABLED  0x00
#define MCP_IVRE_ENABLED    0x80
#define MCP_IVRE_DISABLED   0x00

// CANINTF
#define MCP_RX0IF_SET       0x01
#define MCP_RX0IF_RESET     0x00
#define MCP_RX1IF_SET       0x02
#define MCP_RX1IF_RESET     0x00
#define MCP_TX0IF_SET       0x04
#define MCP_TX0IF_RESET     0x00
#define MCP_TX1IF_SET       0x08
#define MCP_TX2IF_RESET     0x00
#define MCP_TX2IF_SET       0x10
#define MCP_TX2IF_RESET     0x00
#define MCP_ERRIF_SET       0x20
#define MCP_ERRIF_RESET     0x00
#define MCP_WAKIF_SET       0x40
#define MCP_WAKIF_RESET     0x00
#define MCP_IVRF_SET        0x80
#define MCP_IVRF_RESET      0x00

// CANCTRL
#define MCP_REQOP_CONFIG    0x80
#define MCP_REQOP_LISTEN    0x60
#define MCP_REQOP_LOOPBACK  0x40
#define MCP_REQOP_SLEEP     0x20
#define MCP_REQOP_NORMAL    0x00

#define MCP_ABORT           0x10

#define MCP_CLKOUT_ENABLED  0x04
#define MCP_CLKOUT_DISABLED 0x00
#define MCP_CLKOUT_PRE_8    0x03
#define MCP_CLKOUT_PRE_4    0x02
#define MCP_CLKOUT_PRE_2    0x01
#define MCP_CLKOUT_PRE_1    0x00

// CANSTAT
#define MCP_OPMODE_CONFIG   0x80
#define MCP_OPMODE_LISTEN   0x60
#define MCP_OPMODE_LOOPBACK 0x40
#define MCP_OPMODE_SLEEP    0x20
#define MCP_OPMODE_NORMAL   0x00


// RXBnCTRL
#define MCP_RXM_RCV_ALL     0x60
#define MCP_RXM_VALID_EXT   0x40
#define MCP_RXM_VALID_STD   0x20
#define MCP_RXM_VALID_ALL   0x00

#define MCP_RXRTR_REMOTE    0x08
#define MCP_RXRTR_NO_REMOTE 0x00

#define MCP_BUKT_ROLLOVER    0x04
#define MCP_BUKT_NO_ROLLOVER 0x00

#define MCP_FILHIT0_FLTR_1  0x01
#define MCP_FILHIT0_FLTR_0  0x00

#define MCP_FILHIT1_FLTR_5  0x05
#define MCP_FILHIT1_FLTR_4  0x04
#define MCP_FILHIT1_FLTR_3  0x03
#define MCP_FILHIT1_FLTR_2  0x02
#define MCP_FILHIT1_FLTR_1  0x01
#define MCP_FILHIT1_FLTR_0  0x00


// TXBnCTRL
#define MCP_TXREQ_SEND      0x08
#define MCP_TXREQ_ABORT     0x00

#define MCP_TXP_HIGHEST     0x03
#define MCP_TXP_INTER_HIGH  0x02
#define MCP_TXP_INTER_LOW   0x01
#define MCP_TXP_LOWEST      0x00


//******************************************************************
//                  Register Bit Masks
//******************************************************************

#define MCP_DLC_0          0x00
#define MCP_DLC_1          0x01
#define MCP_DLC_2          0x02
#define MCP_DLC_3          0x03
#define MCP_DLC_4          0x04
#define MCP_DLC_5          0x05
#define MCP_DLC_6          0x06
#define MCP_DLC_7          0x07
#define MCP_DLC_8          0x08


//******************************************************************
//                  CAN SPI commands
//******************************************************************

#define MCP_RESET       0xC0
#define MCP_READ        0x03
#define MCP_WRITE       0x02
#define MCP_RTS         0x80
#define MCP_RTS_TXB0    0x81
#define MCP_RTS_TXB1    0x82
#define MCP_RTS_TXB2    0x83
#define MCP_READ_STATUS 0xA0
#define MCP_BIT_MODIFY  0x05


//******************************************************************
//                  Miscellaneous
//******************************************************************

#define MCP_DUMMY_BYTE      0x00
#define MCP_TXB0            0x31
#define MCP_TXB1            0x41
#define MCP_TXB2            0x51
#define MCP_RXB0            0x61
#define MCP_RXB1            0x71
#define MCP_EXIDE_SET       0x08
#define MCP_EXIDE_RESET     0x00
