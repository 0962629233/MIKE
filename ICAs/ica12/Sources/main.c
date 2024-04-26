
/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     MHz
// Author:        This B. You
// Details:       A more detailed explanation of the program is entered here
// Date:          Date Created
// Revision History :
//  each revision will have a date + desc. of changes

/********************************************************************/
// Library includes
/********************************************************************/
#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h.h"
#include "clock.h.h"
#include "rti.h.h"

#include "sci.h"
#include "segs.h"
// Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/
void Segs_16D_with_DP(unsigned int value, Segs_LineOption line, int decimalPos);
void incrementDigit(unsigned int *number, int digitIndex);
void decrementDigit(unsigned int *number, int digitIndex);
unsigned int pow10(int pow);
/********************************************************************/
// Local Prototypes
/********************************************************************/
#define Segs_WLATCH \
  PORTA &= (~0x01); \
  PORTA |= 0x01;
#define Segs_ML PORTA &= (~0x02);
#define Segs_MH PORTA |= 0x02;
/********************************************************************/
// Global Variables
/********************************************************************/
unsigned int uicounter = 0;
int selectedDigit = 0; // Default to the least significant digit initially

// Previous states for button press detection
int oldStateUp = 0, oldStateDown = 0, oldStateLeft = 0, oldStateRight = 0;
/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  // Any main local variables must be declared here

  // main entry point
  _DISABLE_COP();
  // EnableInterrupts;

  /********************************************************************/
  // one-time initializations
  /********************************************************************/
  Segs_Init();   // Initialize the 7-segment display system
  SWL_Init();    // Initialize the switches and LEDs
  PLL_To20MHz(); // Set the system clock to 20 MHz for accurate timing

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {
    // Read button states
    int curStateUp = SWL_Pushed(SWL_UP);
    int curStateDown = SWL_Pushed(SWL_DOWN);
    int curStateLeft = SWL_Pushed(SWL_LEFT);
    int curStateRight = SWL_Pushed(SWL_RIGHT);

    // Button action handling
    if ((curStateUp != oldStateUp) && curStateUp)
    {
      incrementDigit(&uicounter, selectedDigit); // Increment the current digit
    }
    if ((curStateDown != oldStateDown) && curStateDown)
    {
      decrementDigit(&uicounter, selectedDigit); // Decrement the current digit
    }
    if ((curStateLeft != oldStateLeft) && curStateLeft)
    {
      selectedDigit = (selectedDigit < 3) ? selectedDigit + 1 : 3; // Move selection left, without wrapping
    }
    if ((curStateRight != oldStateRight) && curStateRight)
    {
      selectedDigit = (selectedDigit > 0) ? selectedDigit - 1 : 0; // Move selection right, without wrapping
    }

    // Update old states for button detection
    oldStateUp = curStateUp;
    oldStateDown = curStateDown;
    oldStateLeft = curStateLeft;
    oldStateRight = curStateRight;

    // Display updates
    Segs_16D_with_DP(uicounter, Segs_LineTop, 3 - selectedDigit); // Display the current number with the decimal point at the selected digit
    Segs_16H(uicounter, Segs_LineBottom);                         // Display the hexadecimal equivalent on the bottom line
  }
}

/********************************************************************/
// Functions
/********************************************************************/
void Segs_16D_with_DP(unsigned int value, Segs_LineOption line, int decimalPos)
{
  unsigned char startAddress = (line == Segs_LineTop) ? 0 : 4;
  char digits[4] = {0}; // Initialize all digits to 0, assume a 4-digit display
  int i;

  // Extract each digit from the value and store it in the digits array
  for (i = 0; i < 4; i++)
  {
    digits[i] = value % 10;
    value /= 10;
  }

  // Display the digits from the most significant to the least significant
  for (i = 0; i < 4; i++)
  {
    // Calculate the correct position for each digit
    unsigned char position = startAddress + (3 - i);
    // Display digit and set decimal point if this is the selected digit
    Segs_Normal(position, digits[3 - i], (3 - i == decimalPos) ? Segs_DP_ON : Segs_DP_OFF);
  }
}

// Increment the digit at the specified index
void incrementDigit(unsigned int *number, int digitIndex)
{
  unsigned int increment = pow10(3 - digitIndex);
  *number = (*number + increment) % 10000; // Ensure it wraps around at 9999
}
// Decrement the digit at the specified index
void decrementDigit(unsigned int *number, int digitIndex)
{
  unsigned int decrement = pow10(3 - digitIndex);
  if (*number < decrement)
  {
    *number += 10000; // Handle underflow by adding 10000
  }
  *number -= decrement;
  *number %= 10000; // Ensure the number stays within 4 digits
}

// Compute powers of 10 using a lookup table for efficiency
unsigned int pow10(int pow)
{
  static const unsigned int powers_of_10[] = {1, 10, 100, 1000, 10000};
  if (pow >= 0 && pow < sizeof(powers_of_10) / sizeof(powers_of_10[0]))
  {
    return powers_of_10[pow];
  }
  return 0; // Return 0 if the power is out of range
}

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
