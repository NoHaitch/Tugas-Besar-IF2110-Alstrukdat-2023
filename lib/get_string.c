#include "get_string.h"
#include "ADT/boolean.h"
#include "display.h"
#include <stdio.h>

char currentChar;

static FILE *pita;
static int retval;

void ADV(){
    retval = fscanf(pita, "%c", &currentChar);
}

void START(){
    pita = stdin;
    ADV();
}

void ignore_blank(){
    while(currentChar == ' ' || currentChar == '\n') ADV();
}

void get_word(char* res, int size){
    printf("%s", GREEN);
    START();
    ignore_blank();

    int i = 0;
    while(currentChar != ' ' && currentChar != '\n' && currentChar != GET_STRING_MARK && i + 1 < size){
        res[i] = currentChar; ++i;
        ADV();
    }

    res[i] = '\0';
    printf("%s", NORMAL);
}

void get_string(char* res, int size){
    printf("%s", GREEN);
    START();

    /* Ignore carriage return */
    if(currentChar == '\n') ADV(); 

    int i = 0;
    while(currentChar != GET_STRING_MARK && currentChar != '\n' && i + 1 < size){
        res[i] = currentChar; ++i;
        ADV();
    }

    res[i] = '\0';
    printf("%s", NORMAL);
};