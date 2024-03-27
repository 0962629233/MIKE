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

// Other system includes or your includes go here
// #include <stdlib.h>
// #include <stdio.h>

/********************************************************************/
// Defines
/********************************************************************/

/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/

/********************************************************************/
// Constants
/********************************************************************/

/********************************************************************/
// Main Entry
/********************************************************************/
void main(void)
{
  // main entry point
  _DISABLE_COP();
  EnableInterrupts;

  SWL_Init();

  for (;;)
  {
    if (SWL_Pushed(SWL_RIGHT))
    {
      SWL_OFF(SWL_RED);
      SWL_ON(SWL_GREEN);
    }
    else if(SWL_PushedDeb(SWL_LEFT))
    {
      SWL_ON(SWL_RED);
      RTI_Delay_ms(1); // LED on for 1ms
      SWL_OFF(SWL_RED);
      RTI_Delay_ms(9); // LED off for 9ms, completing the cycle
                       // Continue with the rest of your loop or handling code
    }
    else
    {
      if (SWL_Pushed(SWL_UP) && SWL_Pushed(SWL_DOWN))
      {
        // Implement your policy here if both are pressed
        // For example, let's choose to prioritize UP behavior
        RTI_Delay_ms(10);
      }
      else if (SWL_Pushed(SWL_UP))
      {
        RTI_Delay_ms(8); // Wait for 8ms if up is pressed
      }
      else if (SWL_Pushed(SWL_DOWN))
      {
        RTI_Delay_ms(12); // Wait for 12ms if down is pressed
      }
      else
      {
        RTI_Delay_ms(10); // Default behavior
      }
      SWL_TOG(SWL_RED);
    }
  }
}

/********************************************************************/
// Functions
/********************************************************************/

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/