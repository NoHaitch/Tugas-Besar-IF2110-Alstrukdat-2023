#ifndef DRAFT_H
#define DRAFT_H

#include "tweet.h"
#include "string.h"
#include "get_string.h"
#include "ADT/boolean.h"
#include "getCurrentTime.h"

typedef struct Draft* DraftAddress;
typedef struct Draft{
    char content[MAX_TWEET];
    DraftAddress next;    
    char dateTime[MAX_DATETIME];
} Draft;

/* Create new empty Draft */
DraftAddress newDraft();

/* Create a Draft */
void createDraft(UserId id, char* newcontent);

/* Get Last Draft */
DraftAddress getDraft(UserId id);

/* Check if Draft is Empty */
boolean isDraftEmpty(UserId id);

/* Get amount of Draft of a user */
int draftLength(UserId id);

/* Delete last Draft */
void deleteDraft(UserId id);

/* Publish last Draft, use IO for displayTweetIO() */
void publishDraftIO();

/* Display last Draft */
void displayLastDraftIO();

/* Display Draft and ask for command */
void displayDraftIO();

/* Read Draft and ask for command */
void createDraftIO();

/* Read commands for Draft (HAPUS, SIMPAN, UBAH, TERBIT, KEMBALI) */
void readDraftCommandIO();

/* Convert Draft data to Config */
void draftToConfig();
void configToDraft();

/* Memberishkan draft */
void draftCleanUpRoutine();

#endif