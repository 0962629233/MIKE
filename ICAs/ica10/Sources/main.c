
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
int caretPosition = 0;
int caretMovementCount = 0;
int loopCounter = 0;
int leftSwitchCounter = 0;
int rightSwitchCounter = 0;
int upperCount = 0;
int lowerCount = 0;
unsigned char segments[] = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F};
int j = 0;
int count = 0;
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
  Segs_Init();
  SWL_Init();
  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {

    // tier 1
    
    Segs_8H(7,0xE4);
    Segs_Normal(4,3,Segs_DP_ON);
    Segs_Custom(1,0b01001010);
    Segs_Custom(2,0b11110000);
    Segs_Custom(5,0b10001011);
    Segs_Custom(6,0b10110001);

        if (SWL_Pushed(SWL_CTR))
        {
          Segs_16H(upperCount, Segs_LineTop);
          Segs_16H(lowerCount, Segs_LineBottom);
          upperCount++;
          lowerCount--;
          RTI_Delay_ms(100); // 100 ms delay
        }
      }


    /*
      int count = countSegment(j++);
      if (SWL_Pushed(SWL_LEFT))
      {
        if (++loopCounter % 10 == 0)
        {
         Segs_ClearDigit(caretPosition);
          if (caretPosition > 0)
          {
            caretPosition -= 1; // Decrement caretPosition if it's greater than 0
          }
          else
          {
            caretPosition = 5; // Wrap around to the last position if caretPosition is at the first position
          }

          caretMovementCount++;
          loopCounter = 0;
        }
      }
      else if (SWL_Pushed(SWL_RIGHT))
      {
        if (++loopCounter % 10 == 0)
        {
         Segs_ClearDigit(caretPosition);
          if (caretPosition < 5)
          {
            caretPosition += 1; // Increment caretPosition if it's less than 5
          }
          else
          {
            caretPosition = 0; // Wrap around to the first position if caretPosition is at the last position
          }

           caretMovementCount++;
          loopCounter = 0;
        }
      }


      Segs_Custom(caretPosition, segments[count]);

      // Display movement count
      Segs_16H(caretMovementCount, Segs_LineBottom);
      RTI_Delay_ms(100);
    }
  */
 /*
    int count = countSegment(j++);
    if (SWL_Pushed(SWL_LEFT))
    {
      leftSwitchCounter++;
    }
    else
    {
      leftSwitchCounter = 0;
    }

    // Check right switch
    if (SWL_Pushed(SWL_RIGHT))
    {
      rightSwitchCounter++;
    }
    else
    {
      rightSwitchCounter = 0;
    }

    // Execute action if left switch has been held down for 10 iterations
    if (leftSwitchCounter >= 10)
    {
      Segs_ClearDigit(caretPosition);
      caretPosition = (caretPosition > 0) ? caretPosition - 1 : 5;
      caretMovementCount++;
      leftSwitchCounter = 0; // Reset after action to prevent repeated actions without new hold
      
    }

    // Execute action if right switch has been held down for 10 iterations
    if (rightSwitchCounter >= 10)
    {
      Segs_ClearDigit(caretPosition);
      caretPosition = (caretPosition < 5) ? caretPosition + 1 : 0;
      caretMovementCount++;
      rightSwitchCounter = 0; // Reset after action
      
    }

    // Clear line and display caret at new position

    Segs_Custom(caretPosition, segments[count]);

    // Display movement count
    Segs_16H(caretMovementCount, Segs_LineBottom);
      RTI_Delay_ms(100);
  }
  */
}
/********************************************************************/
// Functions
/********************************************************************/
int countSegment(int i)
{
  return i % 6; // This will naturally cycle from 0 to 5 and wrap around
}

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
