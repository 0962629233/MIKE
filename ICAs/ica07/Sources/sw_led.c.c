#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sw_led.h.h"

void SWL_Init(void)
{
    PT1AD1 &= 0x1F;
    DDR1AD1 = 0xE0;
    ATD1DIEN1 = 0x1F;
}
void delayTimer(int delaytime)
{
    int counter;

    for (counter = 0; counter < delaytime; counter++)
    {
    }
}

void SWL_ON(SWL_LEDColour led)
{
    PT1AD1 |= (unsigned char)led;
}
void SWL_OFF(SWL_LEDColour led)
{
    PT1AD1 &= (unsigned char)led;
}
int SWL_Pushed(SWL_SwitchPos pos)
{
    int push = 0;
    if (PT1AD1 & pos)
    {
        push = 1;
    }
    return push;
}
void SWL_TOG(SWL_LEDColour led)
{
    PT1AD1 ^= (unsigned char)led;
}

int SWL_PushedDeb(SWL_SwitchPos pos) {
    if (SWL_Pushed(pos)) { // Check if switch is pressed
        RTI_Delay_ms(20); // Wait for 20ms to debounce
        if (SWL_Pushed(pos)) { // Check again to confirm the switch is still pressed
            return 1; // Confirmed switch press
        }
    }
    return 0; // Switch not pressed or bounce detected
}




