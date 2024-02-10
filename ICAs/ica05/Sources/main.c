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
int count
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

//  for (;;)
//   { 
//     if ( (PT1AD1 & SWL_LEFT)>0)
//     {
     
//      SWL_ON(SWL_RED);
     
      
//     }
//     else 
//     {
//      SWL_OFF(SWL_YELLOW);
//     }

//     if ( (PT1AD1 & SWL_CTR)>0)
//     {
     
//      SWL_ON(SWL_YELLOW);
     
      
//     }
//     else 
//     {
//      SWL_OFF(SWL_RED);
//     }

//     if ( (PT1AD1 & SWL_RIGHT)>0)
//     {
     
//      SWL_ON(SWL_GREEN);
     
      
//     }
//     else 
//     {
//      SWL_OFF(SWL_YELLOW);
//     } 
      
    
    
    


  //}    


//  for (;;)
//   { 
//     if ( (PT1AD1 & SWL_LEFT)>0)
//     {
     
//      SWL_ON(SWL_RED);
     
      
//      }
  

//    if ( (PT1AD1 & SWL_CTR)>0)
//     {
     
//       SWL_ON(SWL_YELLOW);
     
      
//     }
   

//     if ( (PT1AD1 & SWL_RIGHT)>0)
//    {
     
//       SWL_ON(SWL_GREEN);
     
      
//      }
//     if(((PT1AD1 & SWL_UP)>0)||((PT1AD1 & SWL_DOWN)>0))
//     {
//       SWL_OFF(SWL_YELLOW);
//       SWL_OFF(SWL_RED);
//       SWL_OFF(SWL_GREEN);

//     }
      
    
    
    


//   }      

  for (;;)
   { 
   
        if ( (PT1AD1 & SWL_LEFT)>0)
    {
      if(GetCount() < 2)
          SWL_TOG(SWL_RED);
     
      
     }
  

   if ( (PT1AD1 & SWL_CTR)>0)
    {
     if(GetCount() < 2)
      SWL_TOG(SWL_YELLOW);
     
      
    }
   

    if ( (PT1AD1 & SWL_RIGHT)>0)
   {
     if(GetCount() < 2)
      SWL_TOG(SWL_GREEN);
     
      
     }
 
    



    
   

   
  

    

 


   
    
    
    


   } 

}

/********************************************************************/
// Functions
/********************************************************************/
int GetCount(void)
{

}

/********************************************************************/
// Interrupt Service Routines
/********************************************************************/
