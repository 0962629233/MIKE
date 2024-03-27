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
void transmitVowels(void);
void TransmitVowelsWithSumColor(void);
void TransmitVowelsWithSum(void);
/********************************************************************/
// Local Prototypes
/********************************************************************/

/********************************************************************/
// Global Variables
/********************************************************************/

unsigned char receivedChar;
unsigned long actualBaudRate;
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
  actualBaudRate = sci0_InitMath(20E6, 19200); // Store the actual baud rate
  sci0_Init();

  /********************************************************************/
  // main program loop
  /********************************************************************/

  for (;;)
  {

    TransmitVowelsWithSumColor();
    RTI_Delay_ms(250); // Adjust this function based on your timer/RTI setup
  }
}

/********************************************************************/
// Functions
/********************************************************************/
void transmitVowels()
{
  char vowels[] = "AEIOUaeiou";
  char str[21]; // 20 vowels + NULL terminator

  int isUpperCase = SWL_Pushed(SWL_CTR); // Hypothetical function to check button state
  int i = 0;
  SWL_ON(SWL_RED);
  for (i = 0; i < 20; ++i)
  {
    int index = rand() % 10; // Random index for vowels
    // Choose case based on button state
    str[i] = isUpperCase ? toupper(vowels[index]) : tolower(vowels[index]);
  }
  str[20] = '\0';

  sci0_txStr(str);
  SWL_OFF(SWL_RED);
}

void TransmitVowelsWithSum()
{
  char vowels[] = "AEIOUaeiou";
  char str[26]; // 20 vowels, space, 4-digit sum, space, and NULL terminator
  int sum = 0;
  int i;

  // Check button state for case (implement this based on your system)
  int isUpperCase = SWL_Pushed(SWL_CTR);

  SWL_ON(SWL_RED);

  for (i = 0; i < 20; ++i)
  {
    int index = rand() % 10; // Random index for vowels
    char ch = isUpperCase ? toupper(vowels[index]) : tolower(vowels[index]);
    str[i] = ch;
    sum += ch; // Add character value to sum
  }
  str[20] = '\0'; // Null-terminate the vowel string

  // Append the sum as a four-digit number, padded with leading zeros, with a space before and after it
  sprintf(str + 20, " %04d ", sum);

  // Transmit the string
  sci0_txStr(str);

  SWL_OFF(SWL_RED);
}

void TransmitVowelsWithSumColor()
{
  static int firstRun = 1;
  char buffer[512]; // Buffer for the entire message, including ANSI codes
  int sum = 0;
  char vowels[] = "AEIOUaeiou";
  char str[21]; // For the vowels and NULL terminator
  int isUpperCase = SWL_Pushed(SWL_CTR);
  int i;
  // On the first run, print the static header
  if (firstRun)
  {
    sprintf(buffer, "\x1b[2J\x1b[0;0H\x1b[7mYour Name\x1b[0m\n"); // Clear screen, move to top, print name inverted
    sci0_txStr(buffer);
    firstRun = 0;
  }

  // Generate the vowel string and calculate the sum
  for (i = 0; i < 20; ++i)
  {
    int index = rand() % 10;
    char ch = isUpperCase ? toupper(vowels[index]) : tolower(vowels[index]);
    str[i] = ch;
    sum += ch;
  }
  str[20] = '\0'; // Null-terminate the vowel string

  // Compose the message with colors and positioning
  sprintf(buffer, "\x1b[3;0H\x1b[32m%s \x1b[33m%04d\x1b[0m", str, sum); // Vowels in green, sum in yellow on 3rd line

  sci0_txStr(buffer);

  // Update and display the transmission count in default color on the 5th line
  sprintf(buffer, "\x1b[5;0H\x1b[0mCount: %lu", ++transmitCount);
  sci0_txStr(buffer);
}

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
