#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "segs.h"

#define Segs_WLATCH   \
    PORTA &= (~0x01); \
    PORTA |= 0x01;
#define Segs_ML PORTA &= (~0x02);
#define Segs_MH PORTA |= 0x02;

void Segs_Init(void)
{
    PORTA |= 0x03;

    DDRA |= 0x03;
    DDRB = 0xff;
    Segs_Clear();
}

void Segs_Normal(unsigned char Address, unsigned char value, Segs_DPOption dp)
{
    Address &= 0x07;
    Address |= 0b01011000;
    if (dp)
    {
        value &= (~0x80);
    }
    else
    {
        value |= 0x80;
    }
    PORTB = Address;
    Segs_MH;
    Segs_WLATCH;
    PORTB = value;
    Segs_ML;
    Segs_WLATCH;
}

void Segs_Custom(unsigned char Address, unsigned char value)
{
    Address &= 0x07;
    Address |= 0b01111000;

    PORTB = Address;
    Segs_MH;
    Segs_WLATCH;
    PORTB = value;
    Segs_ML;
    Segs_WLATCH;
}

void Segs_Clear(void)
{
    int call = 0;
    for (call = 0; call < 8; call++)
    {
        Segs_Custom(call, 0b10000000);
    }
}
void Segs_8H(unsigned char Address, unsigned char value)
{
    unsigned char upperNibble;
    unsigned char lowerNibble;
    unsigned char nextAddress;
    Address &= 0x07;                   // Ensure the address is within the range of 0-7
    upperNibble = (value >> 4) & 0x0F; // Extract the upper nibble
    lowerNibble = value & 0x0F;        // Extract the lower nibble

    // Display the upper nibble
    Segs_Normal(Address, upperNibble, Segs_DP_OFF);

    // Calculate the next address, wrap around to 0 if the address is 7
    nextAddress = (Address + 1) % 8;
    if (nextAddress == 0)
    {
        Segs_Normal(nextAddress, lowerNibble, Segs_DP_OFF);
    }
    // Display the lower nibble
}

void Segs_16H(unsigned int value, Segs_LineOption line)
{
    int i;
    unsigned char startAddress;
    unsigned char nibble;
    startAddress = (line == Segs_LineTop) ? 0 : 4;

    // Display each nibble starting from the most significant
    for (i = 3; i >= 0; i--)
    {
        nibble = (value >> (i * 4)) & 0x0F; // Isolate each nibble
        Segs_Normal(startAddress + (3 - i), nibble, Segs_DP_OFF);
    }
}
void Segs_ClearDigit(unsigned char addr)
{
    Segs_Custom(addr, 0b10000000);
}
void Segs_16D(unsigned int value, Segs_LineOption line)
{
    unsigned char startAddress = (line == Segs_LineTop) ? 0 : 4;
    char digits[5]; // Maximum of 5 digits for a 16-bit integer (0-65535)
    int i, numDigits = 0;

    // Initialize all segments to zero
    for (i = 0; i < 4; i++)
    {
        Segs_Normal(startAddress + i, 0, Segs_DP_OFF);
    }

    // Check if the value is zero
    if (value == 0)
    {
        digits[numDigits++] = 0; // Only display '0'
    }
    else
    {
        // Extract each digit from the value
        while (value > 0 && numDigits < 5)
        {
            digits[numDigits++] = value % 10;
            value /= 10;
        }
    }

 

    // Display the digits starting from the most significant
    for (i = numDigits - 1; i >= 0; i--)
    {
        // Calculate the correct position for each digit
        unsigned char position = startAddress + 4 - numDigits + i;
        Segs_Normal(position, digits[i], Segs_DP_OFF);
    }
}

