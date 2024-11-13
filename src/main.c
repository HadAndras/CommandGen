#include<stdio.h>

#include "main.h"
#include "command.h"
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

void toHex(int input[], char output[]){
    for (int i = 0; i < 7; i++)
    {
        output[2*i] = getHexaDigit(input[i] / 16);
        output[2*i+1] = getHexaDigit(input[i] % 16);
    }
    
}

void checksum(int input[], char output[]){
    int checksum = 0;
    for (int i = 0; i < 7; i++) {
        checksum += input[i];
    }
    checksum %= 256;
    output[14] = getHexaDigit(checksum / 16);
    output[15] = getHexaDigit(checksum % 16);
}

void commandGen(){
    char output[16] = {0};
    int input[7] = {0};
    for (int i = 0; i < 7; i++)
    {
        printf("%d. data(8 bit number): ", i);
        scanf("%d", &input[i]);
    }
    toHex(input, output);
    checksum(input, output);
    printf("w");
    for (int j = 0; j < 16; j++)
    {
        printf("%c", output[j]);
    }

}

int getDecNum(char num){
    switch (num)
    {
        case 'A': return 10;
        case 'B': return 11;
        case 'C': return 12;
        case 'D': return 13;
        case 'E': return 14;
        case 'F': return 15;
        default: return (int)(num)-48;
    }
}

void readData(){
    char incomingData[33] = {0};
    int nums[16] = {0};
    printf("Type in the data coming from the space. The first letter must be r\n");
    scanf("%s", &incomingData);
    for (int i = 1; i < 33; i++)
    {
        if (i % 2 == 0)
        {
            nums[i/2-1] += getDecNum(incomingData[i]);
        }
        else
        {
            nums[i/2] += 16*getDecNum(incomingData[i]);
        }
        
    }
    printf("r ");
    for (int j = 0; j < 16; j++)
    {
        printf("%d ", nums[j]);
    }
    
    
    
}


int main(){
    char command = 'g';
    printf("Type g if you want to generate a hexa command from numbers\n");
    printf("Type r if you want to read a hexa code, which was sent by the device\n");
    printf("Type anything else if you want to exit\n");
    scanf("%c", &command);
    while (command == 'g' || command == 'r' || command == '\n')
    {
        if (command == 'g')
        {
            commandGen();
        }
        if (command == 'r')
        {
            readData();
        }
        printf("\nType in a new command:\n");
        scanf("%c", &command);
    }
    return 0;
}