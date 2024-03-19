#ifndef TAGAR_H
#define TAGAR_H

#include "user.h"
#include "tweet.h"

#define MAX_TAGAR 300
#define CAPACITY 10007

// typedef struct val{
//     Word key;
//     Kicauan *kic;
//     struct val* next;
// }Val;

// typedef struct{
//     Val* arr[1009];
//     int size;
// }Hashmap;
// typedef struct HashmapValue;
typedef struct hashmapValue{
    TweetId id;
    char key[MAX_TAGAR];
    struct HashmapValue* next;
} HashmapValue;

typedef struct hashMap {
    HashmapValue* tagar[CAPACITY];
    int size;
} HashMap;

void createHastag(HashMap* hashmapHastag);
int hash(char* hastag);
HashmapValue* newHashmapValue(TweetId id,char* key);
void insertHastag(HashMap* hashmapHastag, char* hastag, TweetId id);
void insertLastHastag(HashmapValue** root, HashmapValue* node);
void displayHastag(HashMap* hashmapHastag, char* hastag);

#endif
