#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h.h"


void SWL_Init (void)
{
    PT1AD1 &= 0x1F;
DDR1AD1 = 0xE0;
ATD1DIEN1=0x1F;

}
void delayTimer(int delaytime)
{
 int counter;

for (counter=0;counter<delaytime;counter++)
{
 
}

  }                   



void SWL_ON (SWL_LEDColour led)
{
    PT1AD1 |= (unsigned char)led;

}
void SWL_OFF (SWL_LEDColour led)
{
    PT1AD1 &= (unsigned char) led;
}
int SWL_Pushed (SWL_SwitchPos pos)
{
    int push=0;
    if(PT1AD1 & pos)
    {
        push=1;
    }
    return push;
}
void SWL_TOG (SWL_LEDColour led)
{
    PT1AD1 ^= (unsigned char) led;
   
}


