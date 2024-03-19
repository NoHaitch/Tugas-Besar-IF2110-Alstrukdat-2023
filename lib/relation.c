#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "get_string.h"
#include "relation.h"
#include "user.h"
#include "config.h"

char relation[MAX_USER][MAX_USER];
int relationCount[MAX_USER];
RequestQueuePointer requestQueue[MAX_USER];

void requestFriend(UserId requester, UserId requestee, int friendCount){
    RequestQueuePointer n = malloc(sizeof(RequestQueue));
    n->userId = requester;
    n->friendCount = friendCount;
    n->next = NULL;
    if(requestQueue[requestee] == NULL){
        requestQueue[requestee] = n;
    } else {
        RequestQueuePointer curr = requestQueue[requestee];
        if(curr->friendCount <= n->friendCount){
            n->next = requestQueue[requestee];
            requestQueue[requestee] = n;
        } else {
            while (curr->next != NULL && curr->next->friendCount > n->friendCount){
                curr = curr->next;
            }
            n->next = curr->next;
            curr->next = n;
        }
    }
}

int getFriendCount(UserId userId){
    return relationCount[userId];
}

boolean checkAlreadyRequested(UserId requester, UserId requestee){
    RequestQueuePointer curr = requestQueue[requestee];
    while(curr != NULL){
        if(curr->userId == requester) return true;
        curr = curr->next;
    }
    return false;
}

void addFriend(UserId a, UserId b){
    relation[b][a] = IsFriend;
    relation[a][b] = IsFriend;

    relationCount[b] += 1;
    relationCount[a] += 1;
}

void removeFriend(UserId a, UserId b){
    relation[a][b] = IsNothing;
    relation[b][a] = IsNothing;

    relationCount[a] -= 1;
    relationCount[b] -= 1;
}

boolean isFriend(UserId a, UserId b){
    return relation[a][b];
}

void displayFriendIO(){
    int count = 0;
    UserId friends[MAX_USER];
    for(int i = 0; i < MAX_USER; ++i){
        if(isFriend(loggedUser->id, i)){
            friends[count] = i;
            ++count;
        }
    }

    if(count == 0){
        printf("%s belum mempunyai teman\n", loggedUser->name);
        return;
    }

    printf("%s memiliki %d teman\n", loggedUser->name, count);
    printf("Daftar teman %s\n", loggedUser->name);
    for(int i = 0; i < count; ++i){
        printf("| %s\n", getUser(friends[i])->name);
    }
}

void removeFriendIO(){
    char tmpName[MAX_NAME];
    printf("Masukkan nama pengguna:\n");
    get_string(tmpName, MAX_NAME);
    User* friend = getUser(getUserIdByName(tmpName));
    if(!friend){
        printf("User %s tidak ditemukan\n", tmpName);
        return;
    }

    // addFriend(friend->id, loggedUser->id);
    printf("%d %d", loggedUser->id, friend->id);
    if(isFriend(friend->id, loggedUser->id) != IsFriend){
        printf("%s bukan teman Anda\n", tmpName);
        return;
    }

    // TODO: Generalize prompt
    int promptValue = -1;
    char tmpPrompt[10];
    do{
        printf("Apakah anda yakin ingin menghapus %s dari daftar teman anda? (YA/TIDAK) ",friend->name);
        get_string(tmpPrompt, 10);

        if(string_compare("YA", tmpPrompt) == 0) promptValue = 1;
        else if(string_compare("TIDAK", tmpPrompt) == 0) promptValue = 0;
    } while(
        (promptValue == -1) &&
        (printf("Input tidak valid\n") || true)
    );

    if(promptValue){
        removeFriend(friend->id, loggedUser->id);
        printf("%s berhasil dihapus dari daftar teman Anda\n", friend->name);
    } else {
        printf("Penghapusan teman dibatalkan\n");
    }
}

void requestFriendIO(){
    if(requestQueue[loggedUser->id] != NULL){
        printf("Terdapat permintaan pertemanan yang belum Anda setujui. Silakan kosongkan daftar permintaan pertemanan untuk Anda terlebih dahulu.\n");
        return;
    }

    char tmpName[MAX_NAME];
    printf("Masukkan nama pengguna:\n");
    get_string(tmpName, MAX_NAME);
    User* user = getUser(getUserIdByName(tmpName));
    if(!user){
        printf("Pengguna bernama %s tidak ditemukan\n", tmpName);
        return;
    }

    if(checkAlreadyRequested(loggedUser->id, user->id)){
        printf("Anda sudah mengirimkan permintaan pertemanan kepada David. Silakan tunggu hingga permintaan Anda disetujui.\n");
        return;
    }

    if(isFriend(loggedUser->id, user->id)){
        printf("Anda sudah berteman\n");
        return;
    }

    requestFriend(loggedUser->id, user->id, getFriendCount(user->id));
    printf("Permintaan pertemanan kepada %s telah dikirim. Tunggu beberapa saat hingga permintaan Anda disetujui.\n", tmpName);
};

int countFriendRequest(UserId requestee){
    int size = 0;
    RequestQueuePointer curr = requestQueue[requestee];
    while(curr != NULL){
        ++size;
        curr = curr->next;
    }

    return size;
}

void displayRequestedFriendIO(){
    RequestQueuePointer top = requestQueue[loggedUser->id];

    if(top == NULL){
        printf("Tidak ada permintaan pertemanan untuk Anda\n");
        return;
    }

    int size = countFriendRequest(loggedUser->id);

    printf("Terdapat %d permintaan pertemanan untuk Anda\n\n", size);

    RequestQueuePointer curr = top;
    while (curr != NULL){
        printf("| %s\n", getUser(curr->userId)->name);
        printf("| Jumlah teman: %d\n\n", curr->friendCount);
        curr = curr->next;
    }
}

void acceptFriendIO(){
    RequestQueuePointer top = requestQueue[loggedUser->id];
    UserId requester = top != NULL ? top->userId : -1;

    if(requester == -1){
        printf("Tidak ada permintaan pertemanan untuk Anda\n");
        return;
    }

    User* user = getUser(requester);
    printf("Permintaan pertemanan teratas dari %s\n", user->name);
    printf("| %s\n", user->name);
    printf("| Jumlah teman: %d\n\n", top->friendCount);

    int promptValue = -1;
    char tmpPrompt[10];
    do{
        printf("Apakah Anda ingin menyetujui permintaan pertemanan ini? (YA/TIDAK) ");
        get_string(tmpPrompt, 10);

        if(string_compare("YA", tmpPrompt) == 0) promptValue = 1;
        else if(string_compare("TIDAK", tmpPrompt) == 0) promptValue = 0;
    } while(
        (promptValue == -1) &&
        (printf("Input tidak valid\n") || true)
    );

    if(promptValue){
        addFriend(loggedUser->id, requester);
        printf("Permintaan pertemanan dari %s telah disetujui. Selamat! Anda telah berteman dengan %s.\n",user->name,user->name);
    } else {
        printf("Permintaan pertemanan dari %s telah ditolak.\n", user->name);
    }

    requestQueue[loggedUser->id] = top->next;
    free(top);
}

void relationCleanUpRoutine(){
    for(int i = 0; i < MAX_USER; ++i){
        for(int j = 0; j < MAX_USER; ++j) {
            relation[i][j] = IsNothing;
        }
    }   
}

void relationToConfig(){
    for(int i = 0; i < userCount; ++i){
        for(int j = 0; j < userCount; ++j){
            if(i == j) printf("1 ");
            else printf("%d ", relation[i][j]);
        }
        printf("\n");
    }

    int friendRequestCount = 0;
    for(int i = 0; i < userCount; ++i){
        friendRequestCount += countFriendRequest(i);
    }
    printf("%d\n", friendRequestCount);

    for(int i = 0; i < userCount; ++i){
        RequestQueuePointer curr = requestQueue[i];
        while(curr != NULL){
            printf("%d %d %d\n", curr->userId, i, curr->friendCount);
            curr = curr->next;
        }
    }
}

void configToRelation(){
    for(int i = 0; i < userCount; ++i){
        for(int j = 0; j < userCount; ++j){
            boolean value = readInt(); nextWord();

            relation[i][j] = value;
            relation[j][i] = value;
        }
    }

    int count = readInt(); nextLine();
    for(int i = 0; i < count; ++i){
        int requester = readInt(); nextWord();
        int requestee = readInt(); nextWord();
        int friendCount = readInt(); nextLine();

        requestFriend(requester, requestee, friendCount);
    }
}