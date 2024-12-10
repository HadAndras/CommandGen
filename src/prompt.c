#include "prompt.h"
#include <stdio.h>
#include <time.h>

int ask_int(char* text, int lower, int higher) {
    int result = lower-1;
    while (!(result >= lower && result <= higher)) {
        printf(text);
        scanf("%d", &result);
    }
    return result;
}

long ask_time(char* text) {
    // Absolute time
    int year, month, day, hour, minute, second;
    year = ask_int("Year [1971 - ]:", 1970, 10000);
    month = ask_int("Month [1-12]:", 1, 12);
    day = ask_int("Day [1-31]:", 1, 31);
    hour = ask_int("Hour [0-23]:", 0, 23);
    minute = ask_int("Minute [0-59]:", 0, 59);
    second = ask_int("Second [0-59]:", 0, 59);

    struct tm timeinfo = {0};
    timeinfo.tm_year = year - 1900;
    timeinfo.tm_mon = month - 1;
    timeinfo.tm_mday = day;
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = minute;
    timeinfo.tm_sec = second;

    time_t timestamp = mktime(&timeinfo);
    printf("Epoch timestamp: %ld\n", timestamp);
    return (long)timestamp;
}

int ask_threshold(char* text, int lower, int* voltage_output) {
    char prompt[100];
    sprintf(prompt, "%s [%d-3300 mV]: ", text, lower);
    int threshold = ask_int(prompt, lower, 3300);
    if(voltage_output != 0) *voltage_output = threshold;
    return ((double)threshold / (double)3300) * 4095;
}