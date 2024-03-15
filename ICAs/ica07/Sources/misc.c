#include "misc.h"
int GetRandom(int iLow, int iHighEx) {
    // Return a random number in the inclusive/exclusive range of the arguments
    return rand() % (iHighEx - iLow) + iLow;
}

int isVowel(unsigned char c) {
    // Determine if the provided unsigned char represents a vowel or not
    c = tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}