//
// Created by andras on 2025.05.03..
//

#include "ReadingMode.h"


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "ReadCommands.h"
#include <unistd.h>



int identifyCommand(char com[]){
    char* command = com;
    char* argument;
    int uargument;
    char* tok = strtok(command, " ");
    if(!strcmp(command, "h\n")){
        help();
    }
    else if (!strcmp(command, "lsh\n"))
    {
        listHeaders();
    }
    else if (!strcmp(tok, "sh"))
    {
        argument = strtok(NULL, " ");
        sscanf(argument, "%d", &uargument);
        selectHeader(uargument);
    }
    else if (!strcmp(tok, "ih")) {
        tok = strtok(NULL, " ");
        inputHeader(tok);
    }
    else if (!strcmp(tok, "id\n"))
    {
        inputData();
    }
    else if (!strcmp(tok, "is"))
    {
        tok = strtok(NULL, " ");
        inputSelfTest(tok);
    }
    else if (!strcmp(tok, "ie"))
    {
        tok = strtok(NULL, " ");
        inputError(tok);
    }
    else if(!strcmp(tok, "rd")){
        tok = strtok(NULL, " ");
        rawDecoding(tok);
    }
    else if(!strcmp(command, "e\n")){
        return 1;
    }
    else
    {
        printf("Invalid command\n");
    }
    return 0;
}


void ReadMode(){
    //Variables
    size_t COMMANDLENGTH = 100;
    char* command;

    printf("First you have to enter the number of headers. Number of headers: ");
    scanf("%d", &numberOfHeaders);
    headers = (Header*)(malloc(numberOfHeaders*sizeof(Header)));
    help();

    command = (char*)malloc(COMMANDLENGTH*sizeof(char));
    while (1)
    {
        printf("Enter a command: ");
        getline(&command, &COMMANDLENGTH, stdin);
        printf("\nCommand: %s", command);
        if (identifyCommand(command)) {
            free(command);
            free(headers);
            return;
        }

    }
}


