#include "misc.h"


int isVowel(unsigned char c) {
    // Determine if the provided unsigned char represents a vowel or not
  switch (c) {
        case 'A': case 'E': case 'I': case 'O': case 'U': case 'Y':
        case 'a': case 'e': case 'i': case 'o': case 'u': case 'y':
            return 1;
        default:
            return 0;
    }
     
}