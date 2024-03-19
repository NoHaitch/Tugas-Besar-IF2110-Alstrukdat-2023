#include <stdio.h>
#include "time.h"
#include "datetime.h"
#include <time.h>

boolean IsLeapYear(int Y){
    if(Y % 400 == 0) return true;
    else if(Y % 100 == 0) return false;
    else if(Y % 4 == 0) return true;
    else return false;
}

int MAX_DAY[] = {0, 31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int GetMaxDay(int M, int Y){
    if(M == 2){
        if(IsLeapYear(Y)) return 29;
        else return 28;
    } else return MAX_DAY[M];
}

boolean IsDATETIMEValid(int D, int M, int Y, int h, int m, int s){
    return IsTIMEValid(h, m, s) && 
            (1 <= D && D <= GetMaxDay(M, Y)) &&
            (1 <= M && M <= 12) &&
            (0 <= Y);
}

void CreateDATETIME(DATETIME* D, int DD, int MM, int YYYY, int hh, int mm, int ss){
    CreateTime(&(Time(*D)), hh, mm, ss);
    Day(*D) = DD;
    Month(*D) = MM;
    Year(*D) = YYYY;
}

void BacaDATETIME(DATETIME *D){
    int DD, MM, YY, h, m, s;
    scanf("%d %d %d %d %d %d", &DD, &MM, &YY, &h, &m, &s);
    while(!IsDATETIMEValid(DD, MM, YY, h, m, s)){
        printf("DATETIME tidak valid\n");
        scanf("%d %d %d %d %d %d", &DD, &MM, &YY, &h, &m, &s);
    }
    CreateDATETIME(D, DD, MM, YY, h, m, s);
}

void TulisDATETIME(DATETIME D){
    TIME t = Time(D);
    printf("%d/%d/%d %d:%d:%d", Day(D), Month(D), Year(D), Hour(t), Minute(t), Second(t));
}

boolean DEQ(DATETIME D1, DATETIME D2){
    return TEQ(Time(D1), Time(D2)) && (Day(D1) == Day(D2)) && (Month(D1) == Month(D2)) && (Year(D1) == Year(D2)); 
}

boolean DNEQ(DATETIME D1, DATETIME D2){
    return !DEQ(D1, D2);
}

boolean DLT(DATETIME D1, DATETIME D2){
    if(Year(D1) == Year(D2) && Month(D1) == Month(D2) && Day(D1) == Day(D2)) return TLT(Time(D1), Time(D2));
    else {
        if(Year(D1) < Year(D2)) return true;
        else if(Year(D1) == Year(D2)) {
            if(Month(D1) < Month(D2)) return true;
            else if(Month(D1) == Month(D2)) {
                return Day(D1) < Day(D2);
            }
        }
    }
    return false;
}

boolean DGT(DATETIME D1, DATETIME D2){
    if(Year(D1) == Year(D2) && Month(D1) == Month(D2) && Day(D1) == Day(D2)) return TGT(Time(D1), Time(D2));
    else {
        if(Year(D1) > Year(D2)) return true;
        else if(Year(D1) == Year(D2)) {
            if(Month(D1) > Month(D2)) return true;
            else if(Month(D1) == Month(D2)) {
                return Day(D1) > Day(D2);
            }
        }
    }
    return false;
}

DATETIME DATETIMENextNDetik(DATETIME D, int N){
    long seconds = TIMEToDetik(Time(D));
    seconds += N;

    Day(D) += seconds / (60 * 60 * 24);
    seconds = seconds % (60 * 60 * 24);
    Time(D) = DetikToTIME(seconds);

    while(Day(D) > GetMaxDay(Month(D), Year(D))){
        Day(D) -= GetMaxDay(Month(D), Year(D));
        if(Month(D) == 12){
            Month(D) = 1;
            Year(D) += 1;
        } else {
            Month(D) += 1;
        }
    }

    return D;
}

DATETIME DATETIMEPrevNDetik(DATETIME D, int N){
    long seconds = TIMEToDetik(Time(D));
    seconds -= N;

    Day(D) += seconds / (60 * 60 * 24);
    seconds = seconds % (60 * 60 * 24);
    if(seconds < 0){
        Day(D) -= 1;
        seconds += (60 * 60 * 24);
    }
    Time(D) = DetikToTIME(seconds);

    while(Day(D) < 0){
        if(Month(D) == 1){
            Month(D) = 12;
            Year(D) -= 1;
        } else {
            Month(D) -= 1;
        }
        Day(D) += GetMaxDay(Month(D), Year(D));
    }

    return D;
}

long int DATETIMEDurasi(DATETIME DAw, DATETIME DAkh){
    long selisih = Durasi(Time(DAw), Time(DAkh));

    if(TGT(Time(DAw), Time(DAkh))) {
        selisih -= 86400;
    }

    long dayDiff = 0;
    while(Year(DAkh) != Year(DAw) || Month(DAkh) != Month(DAw)){
        if(Month(DAkh) == 1){
            Month(DAkh) = 12;
            Year(DAkh) -= 1;
        } else {
            Month(DAkh) -= 1;
        }
        dayDiff += GetMaxDay(Month(DAkh), Year(DAkh));
    }

    dayDiff += Day(DAkh) - Day(DAw);

    return selisih + (3600 * 24) * dayDiff;
}

// DATETIME getCurrentDATETIME(){
//     struct tm* timePtr;
//     time_t now; 
//     now = time(NULL);
//     timePtr= localtime(&now);

//     int sec, minute, hour, day, month, year; 

//     sec = timePtr->tm_sec ; 
//     minute = timePtr->tm_min ; 
//     hour = timePtr->tm_hour;

//     day = timePtr->tm_mday;
//     month = timePtr->tm_mon; 
//     year = timePtr->tm_year; 


//     DATETIME res; 
//     CreateDATETIME(&res, day, month, year, hour, minute, sec);
//     return res; 
// }