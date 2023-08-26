/*============================================================================*/
/* AT89S52.H : Atmel AT89S52 MCU Declarations				      */
/*----------------------------------------------------------------------------*/
/* Designed for Keil C Compiler C51.EXE by Duck-Yong Yoon in 2005.	      */
/*============================================================================*/

#ifndef AT89S52_HEADER_FILE
#define AT89S52_HEADER_FILE 1

/*------------------------------------------------
	Byte Registers
------------------------------------------------*/
sfr P0     = 0x80;      /* Port 0 */
sfr SP     = 0x81;      /* Stack Pointer */
sfr DPL    = 0x82;      /* Data Pointer Low Byte */
sfr DPH    = 0x83;      /* Data Pointer High Byte */
sfr DP0L   = 0x82;      /* Alternate Definition */
sfr DP0H   = 0x83;      /* Alternate Definition */
sfr DP1L   = 0x84;      /* Data Pointer 1 Low Byte */
sfr DP1H   = 0x85;      /* Data Pointer 1 High Byte */
sfr PCON   = 0x87;      /* Power Control Register */

sfr TCON   = 0x88;      /* Timer Control Register */
sfr TMOD   = 0x89;      /* Timer Mode Control Register */
sfr TL0    = 0x8A;      /* Timer 0 Low Byte */
sfr TL1    = 0x8B;      /* Timer 1 Low Byte */
sfr TH0    = 0x8C;      /* Timer 0 High Byte */
sfr TH1    = 0x8D;      /* Timer 1 High Byte */
sfr AUXR   = 0x8E;      /* Auxiliary Register */

sfr P1     = 0x90;      /* Port 1 */
sfr SCON   = 0x98;      /* Serial Port Control Register */
sfr SBUF   = 0x99;      /* Serial Port Buffer */

sfr P2     = 0xA0;      /* Port 2 */
sfr AUXR1  = 0xA2;      /* Auxiliary Register 1 */
sfr WDTRST = 0xA6;      /* Watchdog Timer Reset Register */
sfr IE     = 0xA8;      /* Interrupt Enable Register */

sfr P3     = 0xB0;      /* Port 3 */
sfr IP     = 0xB8;      /* Interrupt Priority Register */

sfr T2CON  = 0xC8;      /* Timer 2 Control Register */
sfr T2MOD  = 0xC9;      /* Timer 2 Mode Control Register */
sfr RCAP2L = 0xCA;      /* Timer 2 Capture Register Low Byte */
sfr RCAP2H = 0xCB;      /* Timer 2 Capture Register High Byte */
sfr TL2    = 0xCC;      /* Timer 2 Low Byte */
sfr TH2    = 0xCD;      /* Timer 2 High Byte */

sfr PSW    = 0xD0;      /* Program Status Word */
sfr ACC    = 0xE0;      /* Accumulator */
sfr B      = 0xF0;      /* B Register */

/*------------------------------------------------
	P0 (0x80) Bit Registers
------------------------------------------------*/
sbit P0_0  = 0x80;
sbit P0_1  = 0x81;
sbit P0_2  = 0x82;
sbit P0_3  = 0x83;
sbit P0_4  = 0x84;
sbit P0_5  = 0x85;
sbit P0_6  = 0x86;
sbit P0_7  = 0x87;

/*------------------------------------------------
	TCON (0x88) Bit Registers
------------------------------------------------*/
sbit IT0   = 0x88;      /* Interrupt 0 Type Control Bit */
sbit IE0   = 0x89;      /* Interrupt 0 Edge Flag */
sbit IT1   = 0x8A;      /* Interrupt 1 Type Control Bit */
sbit IE1   = 0x8B;      /* Interrupt 1 Edge Flag */
sbit TR0   = 0x8C;      /* Timer 0 Run Control Bit */
sbit TF0   = 0x8D;      /* Timer 0 Overflow Flag */
sbit TR1   = 0x8E;      /* Timer 1 Run Control Bit */
sbit TF1   = 0x8F;      /* Timer 1 Overflow Flag */

/*------------------------------------------------
	P1 (0x90) Bit Registers
------------------------------------------------*/
sbit P1_0  = 0x90;
sbit P1_1  = 0x91;
sbit P1_2  = 0x92;
sbit P1_3  = 0x93;
sbit P1_4  = 0x94;
sbit P1_5  = 0x95;
sbit P1_6  = 0x96;
sbit P1_7  = 0x97;

sbit T2    = 0x90;      /* Timer 2 external input & clock out */
sbit T2EX  = 0x91;      /* Timer 2 capture/reload trigger & direction control */
sbit MOSI  = 0x95;      /* SPI MOSI - Master data output, slave data input */
sbit MISO  = 0x96;      /* SPI MISO - Master data input, slave data output */
sbit SCK   = 0x97;      /* SPI SCK  - Master clock output, slave clock input */

/*------------------------------------------------
	SCON (0x98) Bit Registers
------------------------------------------------*/
sbit RI    = 0x98;      /* Receive Interrupt Flag */
sbit TI    = 0x99;      /* Transmit Interrupt Flag */
sbit RB8   = 0x9A;      /* 9th data bit or stop bit received */
sbit TB8   = 0x9B;      /* 9th data bit to be transmitted in modes 2 & 3 */
sbit REN   = 0x9C;      /* Receive Enable */
sbit SM2   = 0x9D;      /* Serial Port Mode Bit 2 */
sbit SM1   = 0x9E;      /* Serial Port Mode Bit 1 */
sbit SM0   = 0x9F;      /* Serial Port Mode Bit 0 */

/*------------------------------------------------
	P2 (0xA0) Bit Registers
------------------------------------------------*/
sbit P2_0  = 0xA0;
sbit P2_1  = 0xA1;
sbit P2_2  = 0xA2;
sbit P2_3  = 0xA3;
sbit P2_4  = 0xA4;
sbit P2_5  = 0xA5;
sbit P2_6  = 0xA6;
sbit P2_7  = 0xA7;

/*------------------------------------------------
	IE (0xA8) Bit Registers
------------------------------------------------*/
sbit EX0   = 0xA8;      /* External Interrupt 0 Enable */
sbit ET0   = 0xA9;      /* Timer 0 Interrupt Enable */
sbit EX1   = 0xAA;      /* External Interrupt 1 Enable */
sbit ET1   = 0xAB;      /* Timer 1 Interrupt Enable */
sbit ES    = 0xAC;      /* Serial Port Interrupt Enable */
sbit ET2   = 0xAD;      /* Timer 2 Interrupt Enable */
sbit EA    = 0xAF;      /* Global Interrupt Enable */

/*------------------------------------------------
	P3 (0xB0) Bit Registers
------------------------------------------------*/
sbit P3_0  = 0xB0;
sbit P3_1  = 0xB1;
sbit P3_2  = 0xB2;
sbit P3_3  = 0xB3;
sbit P3_4  = 0xB4;
sbit P3_5  = 0xB5;
sbit P3_6  = 0xB6;
sbit P3_7  = 0xB7;

sbit RXD   = 0xB0;      /* Serial data input */
sbit TXD   = 0xB1;      /* Serial data output */
sbit INT0  = 0xB2;      /* External interrupt 0 */
sbit INT1  = 0xB3;      /* External interrupt 1 */
sbit T0    = 0xB4;      /* Timer 0 external input */
sbit T1    = 0xB5;      /* Timer 1 external input */
sbit WR    = 0xB6;      /* External data memory write strobe */
sbit RD    = 0xB7;      /* External data memory read strobe */

/*------------------------------------------------
	IP (0xB8) Bit Registers
------------------------------------------------*/
sbit PX0   = 0xB8;      /* External Interrupt 0 Priority Bit */
sbit PT0   = 0xB9;      /* Timer 0 Interrupt Priority Bit */
sbit PX1   = 0xBA;      /* External Interrupt 1 Priority Bit */
sbit PT1   = 0xBB;      /* Timer 1 Interrupt Priority Bit */
sbit PS    = 0xBC;      /* Serial Port Interrupt Priority Bit */   
sbit PT2   = 0xBD;      /* Timer 2 Interrupt Priority Bit */

/*------------------------------------------------
	T2CON (0xC8) Bit Registers
------------------------------------------------*/
sbit CP_RL2= 0xC8;      /* 0=Reload,     1=Capture select */
sbit C_T2  = 0xC9;      /* 0=Timer,      1=Counter */
sbit TR2   = 0xCA;      /* 0=Stop timer, 1=Start timer */
sbit EXEN2 = 0xCB;      /* Timer 2 external enable */
sbit TCLK  = 0xCC;      /* 0=Baud rate by Timer 1, 1=Baud rate by Timer 2 */
sbit RCLK  = 0xCD;      /* 0=Baud rate by Timer 1, 1=Baud rate by Timer 2 */
sbit EXF2  = 0xCE;      /* Timer 2 external flag */
sbit TF2   = 0xCF;      /* Timer 2 overflow flag */

/*------------------------------------------------
	PSW (0xD0) Bit Registers
------------------------------------------------*/
sbit P     = 0xD0;      /* Parity Flag */
sbit FL    = 0xD1;      /* User Flag */
sbit OV    = 0xD2;      /* Overflow Flag */
sbit RS0   = 0xD3;      /* Register Bank Select Bit 0 */
sbit RS1   = 0xD4;      /* Register Bank Select Bit 1 */
sbit F0    = 0xD5;      /* User Flag 0 */
sbit AC    = 0xD6;      /* Auxiliary Carry Flag */
sbit CY    = 0xD7;      /* Carry Flag */

#endif
