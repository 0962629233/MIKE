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
#include "clock.h"


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
  //Any main local variables must be declared here

  // main entry point
  _DISABLE_COP();
  //EnableInterrupts;
  
/********************************************************************/
  // one-time initializations
/********************************************************************/
SWL_Init();

/********************************************************************/
  // main program loop
/********************************************************************/

     

  for (;;)
   { 
   SWL_TOG(SWL_RED);
 delayTimer(28500);
 delayTimer(28500);
 delayTimer(28500);
 delayTimer(28500);
  if ( SWL_Pushed(SWL_LEFT)>0)
   {
     
    PLL_To20MHz();
     
      
    }
    if ( SWL_Pushed(SWL_CTR)>0)
   {
     
    PLL_To24MHz();
     
      
    }
    if (SWL_Pushed(SWL_UP)>0)
    {
     CLKSEL_PLLSEL = 0;
    }
    
    



    
   

   
  

    

 


   
    
    
    


   } 

}

/********************************************************************/
// Functions
/********************************************************************/


/********************************************************************/
// Interrupt Service Routines
/********************************************************************/