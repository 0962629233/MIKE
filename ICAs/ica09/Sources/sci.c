#include <hidef.h>      /* common defines and macros */
#include "derivative.h" /* derivative-specific definitions */
#include "sci.h"


unsigned long sci0_InitMath(unsigned long ulBusClock, unsigned long ulBaudRate) {
    unsigned long brDivisor = (ulBusClock + (8 * ulBaudRate)) / (16 * ulBaudRate); // Round to nearest
    SCI0BD = brDivisor;
    return ulBusClock / (16 * brDivisor); // Return the actual baud rate
}

void sci0_InitEnum (BaudRate br)
{
SCI0BD = br;

}


void sci0_txStr(char const *straddr) {
    // Loop until the end of the string is encountered
    while (*straddr) {
        // Transmit the current character pointed to by straddr
        sci0_txByte(*straddr);
        // Increment the pointer to move to the next character
        straddr++;
    }
}

void sci0_Init (void){
  

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