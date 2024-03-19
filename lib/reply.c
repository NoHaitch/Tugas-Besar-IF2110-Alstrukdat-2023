#include <stdio.h>
#include <stdlib.h>
#include "reply.h"
#include "string.h"
#include "relation.h"
#include "get_string.h"
#include "config.h"
#include "getCurrentTime.h"

void insertLastReplies(Replies* base, ReplyNodePointer value){
    if(*base == NULL){
        *base = value;
    } else {
        ReplyNodePointer curr = *base;
        while(curr->next != NULL) curr = curr->next;
        curr->next = value;
    }
}

ReplyId createReply(char* content, UserId author, TweetId tweetId, Replies* base, ReplyPointer* result){
    ReplyNodePointer newSubreply = malloc(sizeof(ReplyNode));
    newSubreply->base = base;

    Tweet *tweet = getTweet(tweetId);
    Reply *reply = &(newSubreply->reply);
    tweet->lastReplyId++;

    reply->id = tweet->lastReplyId;
    string_copy(content, (newSubreply->reply).content, MAX_REPLY);
    reply->author = author;
    getCurrentDATETIME(reply->dateTime);

    if(base == NULL) return -1;
    insertLastReplies(base, newSubreply);

    if(result != NULL) *result = reply;

    return reply->id;
}

ReplyNodePointer getReplyRecur(Replies start, ReplyId target){
    if(start == NULL) return NULL;

    ReplyNodePointer curr = start;
    while(curr != NULL){
        if(curr->reply.id == target) return curr;
        ReplyNodePointer r = getReplyRecur(curr->reply.replies, target);
        if(r) return r;
        curr = curr->next;
    }
    return NULL;
}

ReplyNodePointer getReplyNode(TweetId tweetId, ReplyId replyId){
    Tweet* tweet = getTweet(tweetId);
    if(!tweet) return NULL;
    return getReplyRecur(tweet->replies, replyId);
}

ReplyPointer getReply(TweetId tweetId, ReplyId replyId){
    ReplyNodePointer p = getReplyNode(tweetId, replyId);
    if(!p) return NULL;
    return &(p->reply);
}

Replies* getReplies(TweetId tweetId, ReplyId replyId){
    TweetPointer tweet = getTweet(tweetId);
    if(replyId == -1) return &(tweet->replies);

    ReplyNodePointer parent = getReplyNode(tweetId, replyId);
    if(parent == NULL) return NULL;

    return &(parent->reply.replies);
}

int countReplyRecur(Replies replies){
    if(replies == NULL) return 0;

    int count = 0;
    ReplyNodePointer curr = replies;
    while(curr != NULL){
        count += countReplyRecur(curr->reply.replies);
        ++count;
        curr = curr->next;
    }
    return count;
}

int countReply(TweetId tweetId){
    TweetPointer tweet = getTweet(tweetId);
    return countReplyRecur(tweet->replies);
}

void pt(int tab){
    for(int i = 0; i < tab; ++i) printf("\t");
}

void displaySingleReply(ReplyPointer reply, User* author, int t){
    pt(t); printf("| ID = %d\n", reply->id);
    pt(t); printf("| %s\n", author->name);
    pt(t); printf("| %s\n", reply->dateTime);
    pt(t); printf("| %s\n", reply->content);
}

void displaySinglePrivateReply(ReplyPointer reply, int t){
    pt(t); printf("| ID = %d\n", reply->id);
    pt(t); printf("| PRIVAT\n");
    pt(t); printf("| PRIVAT\n");
    pt(t); printf("| PRIVAT\n");
}

void displayReplyRecurIO(ReplyNodePointer start, int tab){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }
    ReplyNodePointer curr = start;
    while (curr != NULL){
        ReplyPointer reply = &(curr->reply);
        User* author = getUser(reply->author);

        if(
            author->type == PRIVATE_USER &&
            !isFriend(author->id, loggedUser->id) &&
            loggedUser->id != author->id
        ) {
            displaySinglePrivateReply(reply, tab);
        } else {
            displaySingleReply(reply, author, tab);
        }
        printf("\n");

        displayReplyRecurIO(reply->replies, tab + 1);
        curr = curr->next;
    }
}

void displayReplyIO(char* rawTweetId){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }
    TweetId tweetId;

    if(!string_to_integer(rawTweetId, &tweetId)){
        printf("\"%s\" bukanlah id tweet yang valid\n", rawTweetId);
        return;
    }

    if(getTweet(tweetId) == NULL){
        printf("Tidak ditemukan tweet dengan id %d", tweetId);
        return;
    }

    if(getTweet(tweetId)->replies == NULL){
        printf("Belum terdapat balasan\n");
        return;
    }
    displayReplyRecurIO(getTweet(tweetId)->replies, 0);
}

void deleteReplyRecur(Replies start){
    ReplyNodePointer curr = start;
    while(curr != NULL){
        deleteReplyRecur(curr->reply.replies);

        ReplyNodePointer next = curr->next;
        free(curr);
        curr = next;
    }
}

void deleteReply(ReplyNodePointer target){
    deleteReplyRecur(target->reply.replies);

    ReplyNodePointer curr = *(target->base);
    if(curr == target){
        *(target->base) = target->next;
    } else {
        while(curr != NULL){
            if(curr->next == target) break;
            curr = curr->next;
        }
        curr->next = target->next;
    }

    free(target);
}

void createReplyIO(char* rawTweetId, char* rawReplyId){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }
    TweetId tweetId; ReplyId replyId;

    if(!string_to_integer(rawTweetId, &tweetId)){
        printf("\"%s\" bukanlah id tweet yang valid\n", rawTweetId);
        return;
    }

    if(!string_to_integer(rawReplyId, &replyId)){
        printf("\"%s\" bukanlah id reply yang valid\n", rawReplyId);
        return;
    }

    Tweet* tweet = getTweet(tweetId);
    if(!tweet){
        printf("Wah, tidak terdapat kicauan yang ingin Anda balas!\n");
        return;
    }

    Replies* replies = getReplies(tweetId, replyId);
    if(!replies){
        printf("Wah, tidak terdapat balasan yang ingin Anda balas!\n");
        return;
    }

    User *parentAuthor = getUser(replyId == -1 ? tweet->author : (*replies)->reply.author);
    if(
        parentAuthor->type == PRIVATE_USER &&
        !isFriend(parentAuthor->id, loggedUser->id) &&
        loggedUser->id != parentAuthor->id
    ){
        printf("Wah, akun tersebut merupakan akun privat dan anda belum berteman akun tersebu!\n");
        return;
    }

    char tmpReply[MAX_REPLY];
    printf("Masukkan balasan:\n");
    get_string(tmpReply, MAX_REPLY);

    ReplyPointer rp;
    ReplyId id = createReply(tmpReply, loggedUser->id, tweetId, replies, &rp);

    printf("Selamat! balasan telah diterbitkan!\nDetil balasan:\n");
    displaySingleReply(rp, loggedUser, 0);
}

void deleteReplyIO(char* rawTweetId, char* rawReplyId){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }
    TweetId tweetId; ReplyId replyId;

    if(!string_to_integer(rawTweetId, &tweetId)){
        printf("\"%s\" bukanlah id tweet yang valid\n", rawTweetId);
        return;
    }

    if(!string_to_integer(rawReplyId, &replyId)){
        printf("\"%s\" bukanlah id reply yang valid\n", rawReplyId);
        return;
    }

    Tweet* tweet = getTweet(tweetId);
    if(!tweet){
        printf("Kicauan tidak ditemukan\n");
        return;
    }

    ReplyNodePointer rp = getReplyNode(tweetId, replyId);
    if(!rp){
        printf("Balasan tidak ditemukan\n");
        return;
    }

    if(rp->reply.author != loggedUser->id){
        printf("Balasan bukan milik anda\n");
        return;
    }

    deleteReply(rp);
    printf("Balasan berhasil dihapus\n");
}

int maxLine = 1000;
int maxConfig = 1000000;

void repliesToConfig(Replies replies, int parent){
    ReplyNodePointer current = replies;
    while(current){
        Reply reply = current->reply;

        User *user = getUser(reply.author);
        printf("%d %d\n%s\n%s\n%s\n", parent, reply.id, reply.content, user != NULL ? getUser(reply.author)->name : "UNKNOWN_USER", reply.dateTime);

        repliesToConfig(reply.replies, reply.id);
        current = current->next;
    }
}

void replyToConfig(){
    TweetPointer tweet[tweets.nEff];
    int tweetCount = 0;
    for(int id = 1; id <= tweets.nEff; ++id){
        TweetPointer tp = getTweet(id);
        if(tp->replies != NULL){
            tweet[tweetCount] = tp;
            ++tweetCount;
        }
    }

    printf("%d\n", tweetCount);

    for(int i = 0; i < tweetCount; ++i){
        printf("%d\n", tweet[i]->id);
        printf("%d\n", countReply(tweet[i]->id));
        repliesToConfig(tweet[i]->replies, -1);
    }
}

void configToReply(){
    int tweetCount = readInt(); nextLine();

    for(int i = 0; i < tweetCount; ++i){
        TweetId tweetId = readInt(); nextLine();

        int maxId = 0;
        int replyCount = readInt(); nextLine();
        for(int j = 0; j < replyCount; ++j){
            ReplyId parent = readInt(); nextWord();
            ReplyId id = readInt(); nextLine();

            if(id > maxId) maxId = id;

            char content[MAX_REPLY];
            readTill(content, "\n", MAX_REPLY); nextLine();

            char name[MAX_USER];
            readTill(name, "\n", MAX_USER); nextLine();

            char datetime[20];
            readTill(datetime, "\n", 20); nextLine();

            ReplyPointer res;
            createReply(content, getUserIdByName(name), tweetId, getReplies(tweetId, parent), &res);
            res->id = id;
            string_copy(datetime, res->dateTime, MAX_DATETIME);
        }

        getTweet(tweetId)->lastReplyId = maxId;
    }
}