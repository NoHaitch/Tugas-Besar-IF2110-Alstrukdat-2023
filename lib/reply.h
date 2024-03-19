#ifndef REPLY_H
#define REPLY_H

#define MAX_REPLY 281

typedef int ReplyId;
typedef struct reply* ReplyPointer;
typedef struct replynode* ReplyNodePointer;
typedef ReplyNodePointer Replies;

#include "user.h"
#include "tweet.h"


typedef struct reply{
    ReplyId id;
    char content[MAX_REPLY];
    UserId author;
    char dateTime[MAX_DATETIME];
    ReplyNodePointer replies;
} Reply;

typedef struct replynode{
    struct reply reply;
    Replies* base;
    ReplyNodePointer next;
} ReplyNode;

ReplyPointer getReply(TweetId tweetId, ReplyId replyId);
ReplyNodePointer getReplyNode(TweetId tweetId, ReplyId replyId);
Replies* getReplies(TweetId tweetId, ReplyId replyId);

ReplyId createReply(char* content, UserId author, TweetId tweetId, Replies* base, ReplyPointer* result);
ReplyId createReplyFromConfig(char* content, UserId author, TweetId tweetId, Replies* base, ReplyPointer* result, char* dateTime);
ReplyNodePointer* getReplies(TweetId tweetId, ReplyId replyId);
int countReply(TweetId tweetId);
void deleteReply(ReplyNodePointer target);

void createReplyIO(char* rawTweetId, char* rawReplyId);
void displayReplyIO(char* rawTweetId);
void deleteReplyIO(char* rawTweetId, char* rawReplyId);

void replyToConfig();
void configToReply();

#endif