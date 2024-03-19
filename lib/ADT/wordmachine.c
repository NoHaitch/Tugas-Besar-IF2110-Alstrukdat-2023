#include "boolean.h"
#include "wordmachine.h"
#include "charmachine.h"

boolean EndWord;
Word currentWord;

void IgnoreBlanks(){
    while(currentChar == BLANK && currentChar != MARK){
        ADV();
    }
}

void STARTWORD(){
    EndWord = false;
    currentWord.Length = 0;

    START();
    IgnoreBlanks();
    ADVWORD();
}

void ADVWORD(){
    if(currentChar == MARK){
        EndWord = true;
    } else {
        CopyWord();
    }
}

void CopyWord(){
    currentWord.Length = 0;
    while(currentChar != BLANK && currentChar != MARK){
        if(currentWord.Length < NMax){
            currentWord.TabWord[currentWord.Length++] = currentChar;
        }
        ADV();
    }
    IgnoreBlanks();
}