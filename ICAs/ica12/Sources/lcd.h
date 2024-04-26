/////////////////////////////////////////////////////////////////////////////
// Processor:     MC9S12XDP512
// Bus Speed:     20 MHz (Requires Active PLL)
// Author:        Simon Walker
// Details:       LCD Library
// Revision History :
// Created : Unknown
//  Dec 07 2020 - Modified Documentation
//  Dec    2020 - Modified names, modified to use timer for delays
//  Nov 2021, Added PIT Timer for delays, by Carlos
/////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////
// 8-Bit interface init on LCD
// LCD is wired to PTH for data, PK0:2 for control :
// 2     1     0     PTK 
// A     R/W*  E     LCD 
////////////////////////////////////////////////////

////////////////////////////////////////////////////
// LCD Address Scheme (HEX):
// 00 01 ... 12 13
// 40 41 ... 52 53
// 14 15 ... 26 27
// 54 55 ... 66 67
////////////////////////////////////////////////////
#define LCD_WIDTH 20
#define LCD_ROW0 0
#define LCD_ROW1 64
#define LCD_ROW2 20
#define LCD_ROW3 84

#define null 0

#define SHIFT_CUR 0
#define SHIFT_SCR (1<<3)

#define lcd_MicroDelay { char __x = 10; while (--__x); } // 20MHz Version
#define lcd_Latch {PORTK_PK0 = 1;lcd_MicroDelay;PORTK_PK0 = 0;}

/////////////////////////////////////////////////////////////////////////////
// Library Prototypes
/////////////////////////////////////////////////////////////////////////////

void lcd_Init (void);
void lcd_Ins (unsigned char); //LCD_Inst
unsigned char lcd_Busy(void); //LCD_Inst
char lcd_GetAddr(void);
void lcd_Data (unsigned char val);
void lcd_Addr (unsigned char addr);
void lcd_AddrXY (unsigned char ix, unsigned char iy);
void lcd_String (char const * straddr);
void lcdSmartString(char const * straddr, unsigned int delay);
void lcd_StringXY (unsigned char ix, unsigned char iy, char const * const straddr);

void lcd_DispControl (unsigned char curon, unsigned char blinkon);
void lcd_Clear (void);
void lcd_Home (void);
void lcd_ShiftL (char);
void lcd_ShiftR (char);
void lcd_CGAddr (unsigned char addr);
void lcd_CGChar (unsigned char cgAddr, unsigned const char* cgData, int size);
void LCD_Ctrl(unsigned char cCommand);