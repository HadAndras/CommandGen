/**
 * This module handles command generation over various steps.
*/
#include "command.h"
#include "utils.h"
#include <stdio.h>

void ask_int(char* text, int* result, int lower, int higher);

typedef struct Command {
    char *name;
    int code;
    void (*command)(int* data);
} Command;

void timesync(int* data);
void set_dur(int *data);
void set_scale(int *data);
void request_measure(int *data);

Command commands[] = {
    {"Timesync", 0x36, timesync},
    {"Set duration", 0xE0, set_dur},
    {"Set scale", 0xD0, set_scale},
    {"Request measurement", 0x07, request_measure},
};

void ask_int(char* text, int* result, int lower, int higher) {
    while (!(*result >= lower && *result <= higher)) {
        printf(text);
        scanf("%d", result);
    }
}

void gen_command(int* command_data) {
    printf("Select a command:\n");
    for (int i = 0; i < 4; i++) printf("[%d]. %s\n", i, commands[i].name);
    printf("Choose from [0-3]: ");
    int command_key;
    scanf("%d", &command_key);
    Command command = commands[command_key];
    command_data[0] = command.code;
    int command_id = -1;
    ask_int("Command Id [0-255]:", &command_id, 0, 255);
    command_data[1] = command_id;

    command.command(command_data);
}

void set_dur(int* data) {
    printf("Set duration command\n");
    int mode = -1;
    ask_int("MAX_HITS [0] or MAX_TIME mode[1]?",&mode, 0, 1);
    int okaying = -1;
    ask_int("Okaying (0 = no, 1 = yes)?", &okaying, 0, 1);
    int repetitions = -1;
    ask_int("Repetitions [0-63]?", &repetitions, 0, 63);
    int repetition_byte = repetitions << 2 | mode << 1 | okaying;
    
    int duration = -1;
    ask_int("Duration [0-65535]:", &duration, 0, 65535);
    int breaktime = -1;
    ask_int("Breaktime (the time between two measurement in seconds) [0-65535]?", &breaktime, 0, 65535);

    data[2] = repetition_byte;
    data[3] = duration >> 8;
    data[4] = duration & 0xFF;
    data[5] = breaktime >> 8;
    data[6] = breaktime & 0xFF;
}

void set_scale(int * data) {
    printf("Set scale command\n");
}

void timesync(int* data) {
    printf("Timesync command\n");
}

void request_measure(int* data) {
    printf("Request measurement command\n");
}