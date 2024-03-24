#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sci.h"

void sci0_Init (void){
    SCI0BD = 130;
     SCI0CR2 = 0b00001100; 
}
int sci0_read(unsigned char *pData) {
    if (SCI0SR1 & SCI0SR1_RDRF_MASK) { // Check if data is available to read
        *pData = SCI0DRL; // Read the data from the data register, which also clears the RDRF flag
        return 1; // Return 1 to indicate that data was read
    } else {
        return 0; // Return 0 if no data was available
    }
}

void sci0_txByte (unsigned char data){
    
    //Blocking 1 byte transmission
while(!(SCI0SR1 & SCI0SR1_TDRE_MASK));//Wait till transmit data register is empty
SCI0DRL = data;
//Non-locking 1 byte transmission
if(SCI0SR1 & SCI0SR1_TDRE_MASK) //Check if transmit data register is empty
{
SCI0DRL = data;
}
}