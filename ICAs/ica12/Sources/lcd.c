#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "lcd.h"
#include "rti.h.h"
void lcd_Init(void)
{
    PTH = 0b00000000;
    DDRH = 0b11111111;   // data bus  as ouput for write
    PORTK&=0b11111000; // preset RS low, R/W low, EN low
    DDRK |= 0b00000111;  // activate RS,R/W,EN
    RTI_Delay_ms(50);

    // from left to right: 111=(dont care), dont care, font: 5x8 matrix (low).
    PTH = 0b00111000;
    PORTK |= 0b00000001;
    PORTK &= 0b11111000;
    RTI_Delay_ms(5);

    PORTK |= 0b00000001; // RS LOW, R/W LOW, EN HIGH TO WRITE A CONTROL
    PORTK &= 0b11111000; // RESTING STATE
    RTI_Delay_ms(1);

    PORTK |= 0b00000001; // RS LOW, R/W LOW, EN HIGH TO WRITE A CONTROL
    PORTK &= 0b11111000; // RESTING STATE
    RTI_Delay_ms(1);

    LCD_Ctrl(0b00111000);
    LCD_Ctrl(0b00001110);
    LCD_Ctrl(0b00000001);
    LCD_Ctrl(0b00000110);
}

void LCD_Ctrl(unsigned char cCommand)
{
    while (lcd_Busy() != 0)
    {
        PTH = cCommand;
        PORTK |= 0b00000001;
        PORTK &= 0b11111000;
    }
}

unsigned char lcd_Busy(void){
    unsigned char cBusy;
    DDRH=0b00000000;
    PORTK|=0b00000011;
    PORTK&=0b11111000;
    cBusy= PTH&0b10000000;
    DDRH = 0b11111111;
    return cBusy;
}

// Send an instruction byte to the LCD


// Set the cursor to a specific DDRAM address
void lcd_Addr(unsigned char addr) {
    lcd_Ins(0x80 | addr); // 0x80 is the set DDRAM address command
}

// Set the cursor position based on x (column) and y (row) coordinates
void lcd_AddrXY(unsigned char x, unsigned char y) {
    unsigned char addr;
    switch (y) {
        case 0: addr = LCD_ROW0 + x; break;
        case 1: addr = LCD_ROW1 + x; break;
        case 2: addr = LCD_ROW2 + x; break;
        case 3: addr = LCD_ROW3 + x; break;
        default: return; // Invalid row
    }
    lcd_Addr(addr);
}

// Send a data byte to the LCD to be displayed at the current cursor position
void lcd_Data(unsigned char val) {
      while (lcd_Busy() != 0)
    {
        PTH = val;
        PORTK |= 0b00000101;
        PORTK &= 0b11111000;
    }
}

// Display a null-terminated string starting at the current cursor position
void lcd_String(char const * straddr) {
    while (*straddr) {
        lcd_Data(*straddr++); // Display each character
    }
}

// Display a string at specified x (column) and y (row) coordinates
void lcd_StringXY(unsigned char x, unsigned char y, char const * const straddr) {
    lcd_AddrXY(x, y);
    lcd_String(straddr);
}

// Clear the entire display and reset the cursor to the home position
void lcd_Clear(void) {
    lcd_Ins(0x01); // Clear display instruction
    RTI_Delay_ms(2); // Clearing the display takes longer
}

// Return the cursor and display to the home position
void lcd_Home(void) {
    lcd_Ins(0x02); // Return home instruction
    RTI_Delay_ms(2); // This operation takes longer
}

// Shift the display or cursor to the left
void lcd_ShiftL(char count) {
    while (count-- > 0) {
        lcd_Ins(0x18); // Shift display left instruction
    }
}

// Shift the display or cursor to the right
void lcd_ShiftR(char count) {
    while (count-- > 0) {
        lcd_Ins(0x1C); // Shift display right instruction
    }
}

// Set whether the cursor is displayed and whether it blinks
void lcd_DispControl(unsigned char curon, unsigned char blinkon) {
    unsigned char command = 0x08; // Display control instruction
    if (curon) command |= 0x02;   // Option to display cursor
    if (blinkon) command |= 0x01; // Option to blink cursor
    lcd_Ins(command);
}

// Load a custom character into CGRAM at the specified address
void lcd_CGChar(unsigned char cgAddr, unsigned const char* cgData, int size) {
    lcd_Ins(0x40 | (cgAddr << 3)); // Set CGRAM address
    for (int i = 0; i < size; i++) {
        lcd_Data(cgData[i]); // Write each byte of the character pattern
    }
}
