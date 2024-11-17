#include<stdio.h>
#include "main.h"
#include "command.h"
#include "utils.h"

/**
 * This function calculates the checksum of the input array and writes it to the output array.
*/
int checksum(int input[]){
    int checksum = 0;
    for (int i = 0; i < 7; i++) {
        checksum += input[i];
    }
    return checksum;
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
    printf("\n");
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
        if (command == 'g') commandGen();
        else if (command == 'r') readData();
        else {
            printf("\nType in a new command:\n");
            scanf("%c", &command);
        }
    }
    return 0;
}