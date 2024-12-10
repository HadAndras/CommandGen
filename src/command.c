/**
 * This module handles command generation over various steps.
*/
#include "command.h"
#include <stdio.h>
#include "prompt.h"
#include <stdlib.h>

typedef struct Command {
    char *name;
    int code;
    void (*command)(int* data);
} Command;

void set_dur(int *data);
void set_scale(int *data);
void request_measure(int *data);
void request_selftest(int * data);

Command commands[] = {
    {"Set duration", 0xE0, set_dur},
    {"Set scale", 0xD0, set_scale},
    {"Request measurement", 0x07, request_measure},
    {"Request selftest", 0x06, request_selftest}
};

void gen_command(int* command_data) {
    printf("Select a command:\n");
    for (int i = 0; i < 4; i++) printf("[%d]. %s\n", i, commands[i].name);
    int command_key = ask_int("Choose command [0-3]: ", 0, 3);
    Command command = commands[command_key];
    command_data[0] = command.code;
    command_data[1] = ask_int("Command Id [0-255]:", 0, 255);

    command.command(command_data);
}

void set_dur(int* data) {
    printf("Set duration command\n");
    int mode = ask_int("MAX_TIME [0] or MAX_HITS mode[1]?", 0, 1);
    int okaying = ask_int("Okaying (0 = no, 1 = yes)?", 0, 1);
    int repetitions = ask_int("Repetitions [0-63]?", 0, 63);
    int repetition_byte = repetitions << 2 | mode << 1 | okaying;

    int duration = ask_int("Duration [0-65535]:", 0, 65535);
    int breaktime = ask_int("Breaktime (the time between two measurement in seconds) [0-65535]?", 0, 65535);

    data[2] = repetition_byte;
    data[3] = duration >> 8;
    data[4] = duration & 0xFF;
    data[5] = breaktime >> 8;
    data[6] = breaktime & 0xFF;
}

void set_scale(int * data) {
    printf("Set scale command\n");
    int min_voltage_raw = 0;
    int min_voltage = ask_threshold("Minimum voltage", 0, &min_voltage_raw);
    int max_voltage = ask_threshold("Maximum voltage", min_voltage_raw, 0);
    
    data[2] = min_voltage >> 4;
    data[3] = (min_voltage & 0xF) << 4 | max_voltage >> 8;
    data[4] = max_voltage & 0xFF;

    data[5] = ask_int("Resolution [1-255]:", 1, 255);
    data[6] = ask_int("Sampling [1-255]:", 1, 255);
}

void request_measure(int* data) {
    printf("Request measurement command\n");
    long timestamp = ask_time("Enter the timestamp");

    // Timestamp is coded in reverse order because the satellite needs little-endian timestamps
    data[5] = timestamp >> 24;
    data[4] = (timestamp >> 16) & 0xFF;
    data[3] = (timestamp >> 8) & 0xFF;
    data[2] = timestamp & 0xFF;

    int priority = ask_int("Is the measurement priority? [0 = n, 1 =y]: ", 0, 1);
    int header = ask_int("Does the measurement need a header packet? [0 = n, 1 = y]", 0, 1);

    data[6] = priority << 7 | (header << 6);
}

void request_selftest(int* data) {
    printf("Request selftest command\n");
    long timestamp = ask_time("Enter the timestamp");

    // Timestamp is coded in reverse order because the satellite needs little-endian timestamps
    data[5] = timestamp >> 24;
    data[4] = (timestamp >> 16) & 0xFF;
    data[3] = (timestamp >> 8) & 0xFF;
    data[2] = timestamp & 0xFF;

    data[6] = ask_int("Is the measurement priority? [0 = n, 1 =y]: ", 0, 1);
}

void timesync_command(int* command_data) {
    printf("Timesync command\n");
    long timestamp = ask_time("Enter the timestamp");
    command_data[3] = timestamp >> 24;
    command_data[2] = (timestamp >> 16) & 0xFF;
    command_data[1] = (timestamp >> 8) & 0xFF;
    command_data[0] = timestamp & 0xFF;
}
