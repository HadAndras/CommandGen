#include "prompt.h"
#include <stdio.h>
#include <time.h>

long long ask_int(char* text, long long lower, long long higher) {
    long long result = lower-1;
    while (!(result >= lower && result <= higher)) {
        printf(text);
        scanf("%lld", &result);
    }
    return result;
}

long long ask_time(char* text) {
    if(ask_int("Is this an instant measurement? [0 = n, 1 = y]: ", 0, 1) == 1) {
        return 0xFFFFFFFF;
    }
    long long timestamp;
    timestamp = (long long)ask_int("Enter manually: (in decimal)", 0, 4294967295);
    // Absolute time
    /*
    int year, month, day, hour, minute, second;
    year = ask_int("Year [1970 - ]:", 1970, 10000);
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
    printf("Epoch timestamp: %ld\n", timestamp); */
    return timestamp;
}

int ask_threshold(char* text, int lower, int* voltage_output) {
    char prompt[100];
    sprintf(prompt, "%s [%d-3300 mV]: ", text, lower);
    int threshold = ask_int(prompt, lower, 3300);
    if(voltage_output != 0) *voltage_output = threshold;
    return ((double)threshold / (double)3300) * 4095;
}