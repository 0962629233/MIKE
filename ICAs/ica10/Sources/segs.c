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
void Segs_ClearDigit(unsigned char addr)
{
    Segs_Custom(addr, 0b10000000);
}
void Segs_8H(unsigned char Address, unsigned char value)
{
    unsigned char upperNibble;
    unsigned char lowerNibble;
    unsigned char nextAddress;
    Address &= 0x07;                   // Ensure the address is within the range of 0-7
    upperNibble = (value >> 4) ; // Extract the upper nibble
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
        nibble = (value >> (i * 4)) ; // Isolate each nibble
        Segs_Normal(startAddress + (3 - i), nibble, Segs_DP_OFF);
    }
}
