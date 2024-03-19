#include <stdio.h>
#include "boolean.h"
#include "time.h"

#define DAY_IN_SECOND 86400
#define HOUR_IN_SECOND 3600
#define MINUTE_IN_SECOND 60
#define SECOND_IN_SECOND 1

boolean IsTIMEValid(int H, int M, int S){
    return (0 <= H && H <= 23) && (0 <= M && M <= 59) && (0 <= S && S <= 59);
}

void CreateTime(TIME* T, int HH, int MM, int SS){
    Hour(*T) = HH;
    Minute(*T) = MM;
    Second(*T) = SS;
}

void BacaTIME(TIME* T){
    int h, m, s;
    scanf("%d %d %d", &h, &m, &s);
    while(!IsTIMEValid(h, m, s)){
        printf("Jam tidak valid\n");
        scanf("%d %d %d", &h, &m, &s);
    }
    CreateTime(T, h, m, s);
}

void TulisTIME(TIME T){
    printf("%.2d:%.2d:%.2d", Hour(T), Minute(T), Second(T));
}

long TIMEToDetik(TIME T){
    return HOUR_IN_SECOND * Hour(T) + MINUTE_IN_SECOND * Minute(T) + Second(T);
}

TIME DetikToTIME(long N){
    N += (N < 0) * DAY_IN_SECOND;
    N = N % DAY_IN_SECOND;

    int h = N / HOUR_IN_SECOND;
    N = N % HOUR_IN_SECOND;

    int m = N / MINUTE_IN_SECOND;
    N = N % MINUTE_IN_SECOND;

    int s = N;
    
    TIME T;
    CreateTime(&T, h, m, s);
    return T;
}

boolean TEQ(TIME T1, TIME T2){
    return (Hour(T1) == Hour(T2)) && (Minute(T1) == Minute(T2)) && (Second(T1) == Second(T2));
}

boolean TNEQ(TIME T1, TIME T2){
    return !TEQ(T1, T2);
}

boolean TLT(TIME T1, TIME T2){
    return TIMEToDetik(T1) < TIMEToDetik(T2); 
}

boolean TGT(TIME T1, TIME T2){
    return TIMEToDetik(T1) > TIMEToDetik(T2);
}

TIME NextNDetik(TIME T, int N){
    return DetikToTIME(TIMEToDetik(T) + N);
}

TIME NextDetik(TIME T){
    return NextNDetik(T, 1);
}

TIME PrevNDetik(TIME T, int N){
    return NextNDetik(T, (-1) * N);
}

TIME PrevDetik(TIME T){
    return PrevNDetik(T, 1);
}

long Durasi(TIME TAw, TIME TAkh){
    long SAw = TIMEToDetik(TAw);
    long SAkh = TIMEToDetik(TAkh);

    long diffOnly = SAkh - SAw;
    long offset = (SAw > SAkh) * 86400;

    return diffOnly + offset;
}