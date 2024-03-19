# include <stdlib.h>
#include <stdio.h>

#include "tweet.h"
#include "user.h"
#include "relation.h"
#include "get_string.h"
#include "reply.h"
#include "string.h"
#include "thread.h"
#include "config.h"
#include "tagar.h"
#include "getCurrentTime.h"


Tweets tweets; 
HashMap* hashmapHastag;
boolean isIdValid(TweetId id){
    return (id >= 1 && id <= tweets.nEff);
}

TweetPointer getTweet(TweetId id){
    if(!isIdValid(id)) return NULL;
    return &(tweets.buffer[id - 1]) ; 
}

TweetId createTweet(char* content, UserId author){
    if (tweets.capacity == 0 ){
        tweets.buffer = (TweetPointer) malloc (sizeof(Tweet));
        tweets.capacity = 1; 
    } else if (tweets.capacity == tweets.nEff){
        tweets.buffer = (Tweet *) realloc (tweets.buffer, sizeof(Tweet) * (tweets.capacity * 2)) ;
        tweets.capacity = tweets.capacity * 2 ; 
    }

    if(!tweets.buffer) return -1; 
    tweets.nEff ++ ; 
    TweetPointer tweet = getTweet(tweets.nEff) ; 
    tweet -> id =  tweets.nEff ; 
    string_copy(content, tweet->content, MAX_TWEET) ;
    getCurrentDATETIME(tweet->dateTime);
    tweet -> like = 0 ; 
    tweet -> author =  author;   
    tweet->firstThread = NULL ; 
    tweet->threadCount = 0 ; 
    tweet -> replies = NULL ;  
    tweet->lastReplyId = 0 ;  

    return tweet->id ; 
}

void editTweet(TweetId id, UserId author, char* newContent){
    TweetPointer tweet = getTweet(id) ; 
    string_copy(newContent, tweet->content, MAX_TWEET) ; 
}

void likeTweet(TweetId id){
    TweetPointer tweet = getTweet(id); 
    tweet->like ++ ; 
}

// Pemrosesan IO //
void createTweetIO(){

    if(!loggedUser){
        printf("Anda belum login!\n");
        return;

    }
    printf("Masukkan kicauan: \n"); 
    char content [MAX_TWEET] ; 
    get_string(content, MAX_TWEET) ; 

    TweetId newTweetId = createTweet(content, loggedUser->id);
    
    printf("\nMasukkan tagar:\n");
    char hastag [MAX_TAGAR];
    get_string(hastag,MAX_TAGAR);
    HashMap* cobadulu = (HashMap*)malloc(sizeof(HashMap));
    createHastag(cobadulu);
    insertHastag(cobadulu,hastag,newTweetId);
    if (isAllBlank(content)){
        printf("Kicauan tidak boleh hanya berisi spasi!\n");
    } else {
        printf("Selamat! kicauan telah diterbitkan!\n"); 
        displayTweet(newTweetId);
    }
}

void editTweetIO(char* rawTweetId) {
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }
    int id;

    if(!string_to_integer(rawTweetId, &id)){
        printf("\"%s\" bukan id yang valid\n", rawTweetId);

    }
    if( loggedUser->id == 0 ){
        printf("Anda belum login");
        return ; 
    }

    if (!isIdValid(id)){
        printf("Tidak ditemukan kicauan dengan ID ==%d!\n",id);
    } else {
        TweetPointer tweet = getTweet(id) ; 
        User* tweeter = getUser(tweet->author) ;  // tweeeter = pengicau
        if (loggedUser != tweeter){
            printf("Kicauan dengan ID = %d bukan milikmu!\n",id);
        } else {
            printf("Masukkan kicauan baru: \n");

            char newContent [MAX_TWEET] ; 
            get_string(newContent, MAX_TWEET);

            if (isAllBlank (newContent)){
                printf("Kicauan tidak boleh hanya berisi spasi!\n");
            }
            else {
                printf("Selamat! kicauan telah diterbitkan!\n");
                printf("Detil kicauan:\n");
                editTweet(id, loggedUser->id, newContent);
                displayTweet(id);
            }
        }
    }
}

void likeTweetIO(char* rawTweetId){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }

    int id;

    if(!string_to_integer(rawTweetId, &id)){
        printf("\"%s\" bukan id yang valid\n", rawTweetId);
        return;
    }

    if (!isIdValid(id)){
        printf("Tidak ditemukan kicauan dengan ID ==%d;\n",id);
    } else {
        TweetPointer tweet = getTweet(id) ; 
        User* tweeter = getUser(tweet->author) ;  // tweeeter = pengicau
        if (tweeter->type == 1  && !isFriend(loggedUser->id, tweeter->id)){
            printf("Wah, kicauan tersebut dibuat oleh akun privat! Ikuti akun itu dulu ya\n");
        } else {
            likeTweet(id);
            printf("Selamat! kicauan telah disukai!\n");
            printf("Detik kicauan: \n");
            displayTweet(id);
        }
    }
}

void displayTweet(TweetId id){
    TweetPointer tweet = getTweet(id) ; 
    User* user = getUser(tweet->author);
    
    printf("| ID: %d\n", tweet-> id);
    printf("| %s\n", user-> name);
    printf("| %s\n", tweet->dateTime);
    printf("| %s\n", tweet -> content);
    printf("| Disukai: %d\n\n", tweet->like);
}

void displayAllTweetIO() {
    if (!loggedUser){
        printf("Anda belum login\n");
        return ; 
    }
    for(int i = tweets.nEff  ; i >= 1; i --){
        Tweet *tweet = getTweet(i) ; 
        
        if(
            !isFriend(loggedUser->id, tweet->author) &&
            tweet->author != loggedUser->id
        ) continue;
        displayTweet(i); 
    }
}

void tweetToConfig(){
    printf("%d\n", tweets.nEff); 
    int i ; 
    for (i = 1 ; i <= tweets.nEff; i ++){
        TweetPointer tweet = getTweet(i); 
        User* author = getUser(tweet->author);
        printf("%d\n", i );
        printf("%s\n", tweet->content);
        printf("%d\n", tweet->like);
        printf("%s\n", author ? author->name : "UNKNOWN_USER");
        printf("%s\n", tweet->dateTime);
    }
}

void configToTweet(){
    int count = readInt(); nextLine();

    Tweet tweets[100];
    for(int i = 0; i < count; ++i){
        int id = readInt(); nextLine();
        TweetPointer tweet = &(tweets[id - 1]);

        readTill(tweet->content, "\n", MAX_TWEET); nextLine();

        int like = readInt(); nextLine();
        tweet->like = like;

        char author[MAX_NAME];
        readTill(author, "\n", MAX_NAME); nextLine();
        tweet->author = getUserIdByName(author);

        readTill(tweet->dateTime, "\n", 20); nextLine();
    }

    for(int i = 0; i < count; ++i){
        Tweet *src = &(tweets[i]);
        Tweet *dst = getTweet(createTweet(src->content, src->author));
        dst->like = src->like;
        string_copy(src->dateTime, dst->dateTime, MAX_DATETIME);
    }
}