#ifndef LOADER_H
#define LOADER_H
extern char* folder[20];
extern char* pathUserFile[40];
extern char* pathTweetFile[40];
extern char* pathReplyFile[40];
extern char* pathDrafFile[40];
extern char* pathThreadFile[40];
void inputFolder();
void loadUser();
void loadTweet();
void loadReply();
void loadDraf();
void loadThread();
void loadAll();
void loadUserO();
void loadTweetO();
void loadReplyO();
void loadDrafO();
void loadThreadO();

#endif