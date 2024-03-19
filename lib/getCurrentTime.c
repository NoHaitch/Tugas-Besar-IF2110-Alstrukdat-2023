#include <time.h>
#include <stdio.h>

void getCurrentDATETIME(char* datetime){
    struct tm* timePtr;
    time_t now; 
    now = time(NULL);
    timePtr= localtime(&now);

    int sec, minute, hour, day, month, year; 

    sec = timePtr->tm_sec ; 
    minute = timePtr->tm_min ; 
    hour = timePtr->tm_hour;

    day = timePtr->tm_mday;
    month = timePtr->tm_mon; 
    year = timePtr->tm_year; 

    snprintf(datetime, 20, "%d/%d/%d %d:%d:%d", day, month, year, hour, minute, sec);
}

