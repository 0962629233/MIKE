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


//Other system includes or your includes go here
//#include <stdlib.h>
//#include <stdio.h>


/********************************************************************/
//Defines
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
    RTI_Init();
    SWL_Init();

    for (;;)
{
    if ((PT1AD1 & SWL_RIGHT)>0) {
        SWL_OFF(SWL_RED);
        SWL_ON(SWL_GREEN);
    } else if ((PT1AD1 & SWL_LEFT)>0) {
        RTI_Delay_ms(1);
        SWL_ON(SWL_RED);
        RTI_Delay_ms(9);
        SWL_OFF(SWL_RED);
    } else if ((PT1AD1 & SWL_UP)>0 && (PT1AD1 & SWL_DOWN)<0) {
        RTI_Delay_ms(8);
        SWL_TOG(SWL_RED);
    } else if ((PT1AD1 & SWL_UP)<0 && (PT1AD1 & SWL_DOWN)>0) {
        RTI_Delay_ms(12);
        SWL_TOG(SWL_RED);
    } else {
        RTI_Delay_ms(10);
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