#include "misc.h"


int isr(unsigned char c) {
    // Determine if the provided unsigned char represents a vowel or not
  switch (c) {
        case 'R':  
        case 'r':  
            return 1;
        default:
            return 0;
    }
     
}
int isg(unsigned char c) {
    // Determine if the provided unsigned char represents a vowel or not
  switch (c) {
        case 'G':
        case 'g':
            return 1;
        default:
            return 0;
    }
     
}
int isb(unsigned char c) {
    // Determine if the provided unsigned char represents a vowel or not
  switch (c) {
        case 'B': 
        case 'b':  
            return 1;
        default:
            return 0;
    }
     
}