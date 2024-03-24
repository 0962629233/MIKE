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
#include "misc.h"
#include "sci.h"
// Other system includes or your includes go here
#include <stdlib.h>
#include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/
char randomChar;
unsigned char receivedChar;
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
  PLL_To20MHz();
  SWL_Init();

  sci0_Init();

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {
    RTI_Delay_ms(50);
    SWL_TOG(SWL_RED);

    randomChar = 'A' + (rand() % 26);
    sci0_txByte(randomChar);

    if (sci0_read(&receivedChar)) // Assuming sci0_read function correctly sets receivedChar and returns true if a char was received
    {
      if (isVowel(receivedChar) == 1)
      {
        SWL_ON(SWL_GREEN);
      }
      else
      {
        SWL_OFF(SWL_YELLOW); // Ensure YELLOW is off when a vowel is received
      }
      if (isVowel(receivedChar) == 0)
      {
        SWL_ON(SWL_YELLOW);
      }
      else
      {
        SWL_OFF(SWL_GREEN); // Ensure GREEN is off when a non-vowel is received
      }
    }
  }
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
