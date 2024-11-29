#include<stdio.h>
#include <stdint.h>
#include "main.h"
#include "command.h"
#include "utils.h"

/**
 * This function calculates the checksum of the input array and writes it to the output array.
*/
int checksum(int input[]){
    uint8_t checksum = 0;
    for (int i = 0; i < 7; i++) {
        checksum += input[i];
    }
    return (int)checksum;
}

void commandGen(){
    int command[8] = {0};
    gen_command(command);
    command[7] = checksum(command);
    printf("w");
    for (int j = 0; j < 8; j++)
    {
        printf("%02X", command[j]);
    }
    printf("\n\n");
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

void genTimesync() {
    int command[5] = {0x54};
    timesync_command(command);
    printf("l");
    for (int j = 0; j < 5; j++)
    {
        printf("%02X", command[j]);
    }
    printf("\n");
}

/**
 * The entry point of the program.
*/
int main(){
    char command;
    while (1)
    {
        printf("Type g if you want to generate a hexa command\n");
        printf("Type r if you want to read a hexa code, which was sent by the device\n");
        printf("Type t for timesync\n");
        printf("Press Ctrl + C at any point if you want to exit\n");
        scanf("%c", &command);
        if (command == 'g') commandGen();
        else if (command == 'r') readData();
        else if (command == 't') genTimesync();
    }
    return 0;
}