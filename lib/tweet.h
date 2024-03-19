#ifndef TWEET_H
#define TWEET_H

#define MAX_TWEET 281
#define MAX_DATETIME 20

typedef int TweetId;
typedef struct tweet* TweetPointer ;

#include "user.h"
#include "reply.h"
#include "thread.h"

typedef struct tweet{
    TweetId id;
    char content[MAX_TWEET];
    int like;
    UserId author;
    char dateTime[MAX_DATETIME];
    ThreadPointer firstThread; // firstThread = kicauan sambungan pertama
    int threadCount;
    Replies replies;
    int lastReplyId;
} Tweet;

typedef struct{
    TweetPointer buffer;
    int nEff; 
    int capacity ; 
}Tweets;

extern Tweets tweets;

boolean isIdValid(TweetId id) ; 
TweetPointer getTweet(TweetId id);
TweetId createTweet(char* content, UserId author);
void editTweet(TweetId id, UserId author, char* newContent) ; 
void likeTweet(TweetId id);
void displayTweet(TweetId id) ; 

void createTweetIO();
void editTweetIO(char* rawTweetId) ; 
void likeTweetIO(char* rawTweetId) ; 
void displayAllTweetIO() ; 

void tweetToConfig();
void configToTweet();
#endif