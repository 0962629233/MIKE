#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "rti.h.h"
void RTI_Init(void);
void RTI_Delay_ms(unsigned int ms){
    unsigned long i;

    // Stop the RTI
    RTICTL &= ~0b10000000;

    // Check the RTIF flag of CRGFLG register, if it is set, clear it
    if (CRGFLG & CRGFLG_RTIF_MASK) {
        CRGFLG = CRGFLG_RTIF_MASK;
    }

    // Start the RTI with a 1ms period
    RTICTL = 0b10010111;

    // For Intervalms times, wait for the RTIF flag, then clear it
    for (i = 0; i < ms; i++) {
        while (!(CRGFLG & CRGFLG_RTIF_MASK));
        CRGFLG = CRGFLG_RTIF_MASK;
    }

    // Stop the RTI
    RTICTL &= ~0b10000000;
}