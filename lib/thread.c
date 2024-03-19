#include <stdio.h>
#include <stdlib.h>

#include "tweet.h"
#include "user.h"
#include "relation.h"
#include "get_string.h"
#include "reply.h"
#include "string.h"
#include "config.h"
#include "getCurrentTime.h"

Threads threads ; 

// return true if threadId is a valid ThreadId
boolean isMainThreadIdValid(ThreadId threadId){
    return !(threadId > threads.nEff || threadId < 1);
}

// return true if threadIdx is a valid idx for a valid mainThreadId
boolean isThreadIdxValid(ThreadId mainThreadId, int threadIdx){
    return !(threadIdx > (threads.buffer[mainThreadId])->threadCount || threadIdx < 1);
}

// return true if TweetPointer pointing into a tweet that is also a thread 
boolean isThread(TweetPointer tweetPointer){
    for (int i = 1; i <= threads.nEff; i++){
        if (threads.buffer[i] == tweetPointer) return true ; 
    }
    return false;
}

// create a new thread and return the pointer 
ThreadPointer newThread(char* content){
    ThreadPointer thread = (ThreadPointer) malloc (sizeof(Thread));
    string_copy(content, thread->content, MAX_THREADS);
    getCurrentDATETIME(thread->dateTime);
    thread->nextThread = NULL ; 
    return thread ; 
}

ThreadPointer newThreadForConfig(char* content, char* dateTime){
    ThreadPointer thread = (ThreadPointer) malloc (sizeof(Thread));
    string_copy(content, thread->content, MAX_THREADS);
    string_copy(dateTime, thread->dateTime, MAX_DATETIME);
    thread->nextThread = NULL ; 
    return thread ; 
}

// make a pointer into a thread and return the pointer into that tweet
TweetPointer makeMainThread(TweetPointer mainThread) {
    if (threads.capacity == 0 ){
        threads.buffer = (TweetPointer*) malloc (sizeof(TweetPointer));
        threads.capacity = 1; 
    } else if (threads.capacity == threads.nEff){
        threads.buffer = (TweetPointer *) realloc (threads.buffer, sizeof(TweetPointer) * (threads.capacity * 2)) ;
        threads.capacity = threads.capacity * 2 ; 
    }

    if(!threads.buffer) return NULL; 
    threads.nEff ++ ; 
    threads.buffer[threads.nEff] = mainThread;;

    return threads.buffer[threads.nEff]; 
}

// reutrn the pointer of a thread with Id == mainThreadId
TweetPointer getMainThread(ThreadId mainThreadId) {
    return (threads.buffer[mainThreadId]);
}

// return the pointer of thread with threadId == mainThread and threadIdx == threadIdx
ThreadPointer getThread(TweetPointer mainThread, int threadIdx){
    ThreadPointer currThread = mainThread->firstThread;

    for(int i = 1 ; i < threadIdx ; i++){
        currThread = currThread->nextThread;
    }
    return currThread;
}

// I.S : mainThread is a valid Thread, threadIdx -1 is a valid thread IDx for that mainThread or threadIdx ==1
// F.S : insert new thread at mainThread with threadIdx and .content == content
void continueThreadAt(TweetPointer mainThread, int threadIdx, char* content) {
    ThreadPointer new = newThread(content);
    
    if (threadIdx == 1){
        new->nextThread = mainThread->firstThread;
        mainThread->firstThread = new;
    } else {
        ThreadPointer prev = getThread(mainThread, threadIdx -1);

        new->nextThread = prev->nextThread;
        prev->nextThread = new ; 
        
    }   
    mainThread->threadCount += 1; 
}

void continueThreadAtForConfig(TweetPointer mainThread, int threadIdx, char* content, char* dateTime) {
    ThreadPointer new = newThreadForConfig(content, dateTime);
    
    if (threadIdx == 1){
        new->nextThread = mainThread->firstThread;
        mainThread->firstThread = new;
    } else {
        ThreadPointer prev = getThread(mainThread, threadIdx -1);

        new->nextThread = prev->nextThread;
        prev->nextThread = new ; 
        
    }   
    mainThread->threadCount += 1; 
}

// I.S : mainThread is a valid Thread, threadIdx is a valid thread 
// F.S : delete the thread of mainThread at idx == threadIdx
void deleteThreadAt(TweetPointer mainThread, int threadIdx){
    if (threadIdx == 1 ){
        ThreadPointer first = mainThread->firstThread;
        mainThread->firstThread = first->nextThread;
        free(first);
    } else {
        ThreadPointer prev = getThread(mainThread, threadIdx -1);
        ThreadPointer delete = prev->nextThread;
        prev->nextThread = delete->nextThread;
        free(delete);
        mainThread->threadCount --;
    }
}

// I.S : mainThreadId is a valid thread 
// F.S : display the tweet with ThreadId == mainThreadId 
void displayThreadSeqIO(char* rawThreadId){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }
    ThreadId mainThreadId;

    if(!string_to_integer(rawThreadId, &mainThreadId)){
        printf("\"%s\" bukanlah id thread yang valid\n", rawThreadId);
        return;
    }


    if (mainThreadId > threads.nEff || mainThreadId < 1){
        printf("Utas tidak ditemukan!\n");
    } else {
        TweetPointer mainThread = getMainThread(mainThreadId);
        User* user = getUser(mainThread->author);
        if(user->type && !isFriend(loggedUser->id, user->id) && user->id != loggedUser->id){
            printf("Akun yang membuat utas ini adalah akun privat! Ikuti dahulu akun ini untuk melihat utasnya!\n");
        } else {
            ThreadPointer currThread = mainThread->firstThread;
            int count = 1 ; 
            printf("| ID: %d\n", mainThread-> id);
            printf("| %s\n", user-> name);
            printf("| %s\n", mainThread->dateTime);
            printf("| %s\n\n", mainThread -> content);

            while (currThread != NULL){
                printf("   | INDEX: %d\n", count);
                printf("   | %s\n", user->name);
                printf("   | %s\n", currThread->dateTime);
                printf("   | %s\n\n",  currThread -> content);
                currThread = currThread->nextThread;

                count ++;
            }
        }
    }
}

// I.S bebas 
// F.S menampilkan pesan kesalahan jika parameter tidak valid atau menginsert thread baru pada parameter yang diberikan
// I.S bebas 
// F.S menampilkan pesan kesalahan jika parameter tidak valid atau menginsert thread baru pada parameter yang diberikan
void continueThreadAtIOParsed(ThreadId mainThreadId, int threadIdx){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }
    if (!(isMainThreadIdValid(mainThreadId)) && mainThreadId != 1){
        printf("Utas tidak ditemukan!\n");
    } else if (!(isThreadIdxValid(mainThreadId, threadIdx-1)) && threadIdx!=1){
        printf("Index terlalu tinggi!\n");

    } else {
        TweetPointer mainThread = getMainThread(mainThreadId);

        if (loggedUser->id != mainThread->author){
            printf("Anda tidak bisa menyambung kicauan dalam utas ini!\n");
        } else{
            printf("Masukkan kicauan: \n");
            char content[MAX_THREADS];
            get_string(content,MAX_THREADS);

            continueThreadAt(mainThread, threadIdx, content);
        }
    }
}

void continueThreadAtIO(char* rawMainThreadId, char* rawThreadIdx){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }
    ThreadId mainThreadId; int threadIdx;

    if(!string_to_integer(rawMainThreadId, &mainThreadId)){
        printf("\"%s\" bukanlah id thread yang valid\n", rawMainThreadId);
        return;
    }

    if(!string_to_integer(rawThreadIdx, &threadIdx)){
        printf("\"%s\" buknalah index thread yang valid\n", rawThreadIdx);
        return;
    }

    continueThreadAtIOParsed(mainThreadId, threadIdx);
}

// I.S bebas 
// F.S menampilkan pesan kesalahan jika parameter tidak valid atau menghapus thread pada parameter yang diberikan
void deleteThreadAtIO(char* rawMainThreadId, char* rawThreadIdx){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }
    ThreadId mainThreadId; int threadIdx;

    if(!string_to_integer(rawMainThreadId, &mainThreadId)){
        printf("\"%s\" bukanlah id thread yang valid\n", rawMainThreadId);
        return;
    }

    if(!string_to_integer(rawThreadIdx, &threadIdx)){
        printf("\"%s\" buknalah index thread yang valid\n", rawThreadIdx);
        return;
    }

    printf("\n");
    if (!(isMainThreadIdValid(mainThreadId)) && mainThreadId != 1){
        printf("Utas tidak ditemukan!\n");
    } else if ((!isThreadIdxValid(mainThreadId, threadIdx-1) && threadIdx!=1)){
        printf("Index terlalu tinggi!\n");
    } else {
        printf("masuk");
        TweetPointer mainThread = getMainThread(mainThreadId);
        deleteThreadAt(mainThread, threadIdx);
    }
}

// I.S bebas
// F.S menjadikan tweet dengan Id == tweetId menjadi sebuah thread 
void makeMainThreadIO(char* rawTweetId){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }
    TweetId tweetId;

    if(!string_to_integer(rawTweetId, &tweetId)){
        printf("\"%s\" bukanlah id tweet yang valid\n", rawTweetId);
        return;
    }

    printf("\n");
    if (tweetId < 1 || tweetId > tweets.nEff){
        printf("Kicauan tidak ditemukan!\n");
    } else if (getTweet(tweetId)->firstThread != NULL){
        printf("Utas telah dibuat sebelumnya!\n");
    } else if (loggedUser->id != getTweet(tweetId)->author){
        printf("Utas ini bukan milik Anda\n");
    } else{
        printf("Utas berhasil dibuat!\n");

        TweetPointer mainThread =  getTweet(tweetId);
        makeMainThread(mainThread);
        ThreadId mainThreadId = threads.nEff;

        char input[6];
        do {
            continueThreadAtIOParsed(mainThreadId, (mainThread->threadCount) + 1);
            printf("\n");
            printf("Apakah Anda ingin melanjutkan Utas ini? (YA/TIDAK) ");
            get_string(input, 6);
        } while(!string_compare(input, "YA")); //string_compare(a,b) == 0 <-> a = b
        printf("Utas selesai!\n");
    }
}

void threadToConfig(){
    printf("%d\n", threads.nEff); 
    int i ; 
    for (i = 1 ; i <= threads.nEff; i ++){ 
        TweetPointer mainThread = threads.buffer[i];
        if (mainThread->firstThread != NULL){
            printf("%d\n", mainThread->id) ; 
            printf("%d\n", mainThread->threadCount) ; 
            
            ThreadPointer currThread  = mainThread->firstThread ; 
            char* userName = getUser(mainThread->author)->name ; 
            do{
              printf("%s\n",currThread->content);
              printf("%s\n", userName);
              printf("%s\n", currThread->dateTime);
              currThread = currThread->nextThread;
            } while (currThread != NULL);
        }
    }
}

void configToThread(){
    int tweetCount = readInt(); nextLine();

    for(int i = 0; i < tweetCount; ++i){
        TweetId tweetId = readInt(); nextLine();
        TweetPointer tweet = getTweet(tweetId);
        makeMainThread(tweet);

         int threadCount = readInt(); nextLine();

        for(int j = 0; j < threadCount; ++j){
            char content[MAX_THREADS];
            readTill(content, "\n", MAX_THREADS); nextLine();

            char name[MAX_NAME];
            readTill(name, "\n", MAX_NAME); nextLine();

            char date[MAX_DATETIME];
            readTill(date, "\n", MAX_DATETIME); nextLine();

            continueThreadAtForConfig(tweet, j + 1, content, date);
        }

    }

}