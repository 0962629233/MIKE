/********************************************************************/
// HC12 Program:  YourProg - MiniExplanation
// Processor:     MC9S12XDP512
// Bus Speed:     20MHz
// Author:        bao huynh pham
// Details:      setting bus speed and baudrate and transmit letter
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

unsigned long actualBaudRate;
char firstLetter;
unsigned char receivedChar;
unsigned long transmitCount = 0;
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
  actualBaudRate = sci0_InitMath(20E6, 38400); // Store the actual baud rate
  sci0_Init();

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {

    int midBtn = SWL_Pushed(SWL_CTR);
    int downBtn = SWL_Pushed(SWL_DOWN);
    int upBtn = SWL_Pushed(SWL_UP);
    int i = 0;
    char buffer[512];
    firstLetter = '.';
    RTI_Delay_ms(200);
    SWL_TOG(SWL_GREEN);
  
    if (midBtn)
    {
      for (i = 0; i < 10; i++)
      {
        firstLetter = '.';
        RTI_Delay_ms(200);
        SWL_TOG(SWL_GREEN);
        sci0_txByte(firstLetter);
      }
    }
    if (upBtn)
    {
      for (i = 0; i < 10; i++)
      {
        firstLetter = '!';
        RTI_Delay_ms(200);
        SWL_TOG(SWL_GREEN);
        sci0_txByte(firstLetter);
      }
    }
    if (downBtn)
    {
      for (i = 0; i < 10; i++)
      {
        firstLetter = '?';
        RTI_Delay_ms(200);
        SWL_TOG(SWL_GREEN);
        sci0_txByte(firstLetter);
      }
    }
   
   sci0_txByte(firstLetter);
    sprintf(buffer, "\x1b[0;0H\x1b[0mCount: %lu", ++transmitCount);
  sci0_txStr(buffer);
    sprintf(buffer, "\x1b[3;0H\x1b[2K", firstLetter); 
  sci0_txStr(buffer);
    if (sci0_read(&receivedChar)) // Assuming sci0_read function correctly sets receivedChar and returns true if a char was received
    {
      if (isr(receivedChar) == 1)
      {
        sprintf(buffer, "\x1b[0;0H\x1b[0mCount: %lu", ++transmitCount);
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