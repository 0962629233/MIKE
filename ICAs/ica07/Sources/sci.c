#include "sci.h"
void sci0_Init(void) {
     SCI0BDH = 0x00;  // Set the baud rate to 9600
    SCI0BDL = 0x9C;
    SCI0CR1 = 0x00;  // 8 data bits, no parity, 1 stop bit
    SCI0CR2 = 0x0C;  // Enable the receiver and transmitter
}

int sci0_read(unsigned char *pData) {
    // Non-blocking read of a byte
    // Returns 1 if data present, otherwise 0
     if (SCI0SR1 & SCI0SR1_RDRF_MASK) {  // If data is received
        *pData = SCI0DRL;  // Read the received data
        return 1;
    }
    return 0;
}

void sci0_txByte(unsigned char data) {
    // Send a byte to SCI0 (blocking)
    while (!(SCI0SR1 & SCI0SR1_TDRE_MASK));  // Wait for empty transmit buffer
    SCI0DRL = data;  // Put data into buffer, sends the data
}
