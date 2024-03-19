#include<stdlib.h>
#include<stdio.h>
#include "loader.h"
#include "adt.h"
char* folder[20];
char* pathUserFile[40];
char* folder[20];
char* pathUserFile[40];
char* pathTweetFile[40];
char* pathReplyFile[40];
char* pathDrafFile[40];
char* pathThreadFile[40];
void inputFolder(){
    get_string(folder,20);
}/* menerima input dari pengguna berupa string nama folder config*/

void loadUser(){
    sprintf(pathUserFile, "%s/pengguna.config", folder);
}
void loadTweet(){
    sprintf(pathTweetFile, "%s/kicauan.config",folder);
}
void loadReply(){
    sprintf(pathReplyFile, "%s/balasan.config", folder);
}
void loadDraf(){
    sprintf(pathDrafFile, "%s/draf.config",folder);
}
void loadThread(){
    sprintf(pathThreadFile, "%s/thread.config",folder);
}
void loadAll(){
    inputFolder();
    loadUser();
    loadDraf();
    loadReply();
    loadThread();
    loadTweet();
}
void loadUserO(){
    
}
void loadTweetO(){
    
}
void loadReplyO(){

}
void loadDrafO(){

}
void loadThreadO(){

}


