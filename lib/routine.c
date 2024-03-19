#include <stdio.h>
#include <stdlib.h>
#include "routine.h"
#include "user.h"
#include "relation.h"
#include "draft.h"
#include "tagar.h"

void setup(){
    HashMap* hashmapHastag = (HashMap*)malloc(sizeof(HashMap));
    if (hashmapHastag == NULL){
        exit(EXIT_FAILURE);
    }
    createHastag(hashmapHastag); 
}

void cleanup(){
    userCleanupRoutine();
    relationCleanUpRoutine();
    draftCleanUpRoutine();
}