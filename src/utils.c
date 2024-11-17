#include "utils.h"

/*
* This function converts a 10 base number to a hexadecimal digit.
*/
char getHexaDigit(int num){
    switch (num)
    {
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13: return 'D';
        case 14: return 'E';
        case 15: return 'F';
        default: return (char)(num+48);
    }
}

/**
 * This function converts the input array to hexadecimal format.
*/
void toHex(int input[], char output[], int lenght){
    for (int i = 0; i < lenght; i++)
    {
        output[2*i] = getHexaDigit(input[i] / 16);
        output[2*i+1] = getHexaDigit(input[i] % 16);
    }    
}