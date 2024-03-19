#include <stdio.h>
#include <stdlib.h>
#include "tweet.h"
#include "tagar.h"
#include "string.h"

void createHastag(HashMap* hashmapHastag){
    for (int i = 0; i < CAPACITY; i++){
        hashmapHastag->tagar[i] = NULL;
        // printf("index: %d\n",i);
    }
}

/* menerima tagar (tanpa pagar) dari kicauan dan mengembalikan nilai kuncinya*/
int hash(char* hastag){

    int p = 31, m = 10007;
    int key = 0;
    long long power = 1;
    int n;
    n = string_length(hastag);
    for (int i = 0; i < n; i++){
        key = (key + ((hastag[i] - 'a' + 1) * (power))) % m;
        power = (power * p) % m;
    }
    return key;
}

HashmapValue* newHashmapValue(TweetId id,char* hastag){
    HashmapValue* hashmap = (HashmapValue*)malloc(sizeof(HashmapValue));
    hashmap->id = id;
    string_copy(hastag,hashmap->key,MAX_TAGAR);
    hashmap->next = NULL;
    return hashmap;
}

void insertHastag(HashMap* hashmapHastag,char* hastag, TweetId id){
    char hastagtemp[MAX_TAGAR];
    lowercase(hastag,hastagtemp,MAX_TAGAR);

    int index = hash(hastagtemp);
    HashmapValue* hashmap = newHashmapValue(id,hastag);

    if (hashmapHastag->tagar[index] == NULL){
        hashmapHastag->tagar[index] = hashmap;
    } else {
        insertLastHastag(&hashmapHastag->tagar[index],hashmap);
    }
}

void insertLastHastag(HashmapValue** root, HashmapValue* node){
    // if (*root == NULL){
    //     *root = node;
    // } else {
    //     HashmapValue* m = *root;
    //     while (m->next != NULL){
    //         m = m->next;
    //     }

    //     m->next = node;
    // }
}

void displayHastag(HashMap* hashmapHastag, char* hastag){
//     int count = 0;
//     char hastagtemp[MAX_TAGAR];
//     lowercase(hastag,hastagtemp, MAX_TAGAR);
    
//     int index = hash(hastagtemp);
//     HashmapValue* m = hashmapHastag->tagar[index];

//     char ayam [MAX_TAGAR];
//     string_copy(m->key,ayam,MAX_TAGAR);
//     lowercase(ayam,ayam,MAX_TAGAR);

//     if (string_compare(ayam,hastagtemp) == 0){
//         while(m != NULL){
//             if(string_compare(ayam,hastagtemp) == 0){
//                 displayTweet(m->id);
//                 count++;
//             }
//             m = m->next;
//         }
//         if(count > 1 && string_compare(ayam,hastagtemp) == 0){
//             displayTweet(m->id);
//         }
//     } else {
//         printf("Tidak ditemukan kicauan dengan tagar\n");
//         printf("#%s!\n",hastag);

//     }
}