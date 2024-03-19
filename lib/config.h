#ifndef CONFIG
#define CONFIG

#define CONFIG_MARK '\n'
#define MAX_CONFIG 1000000
#define MAX_LINE 1000
#define MAX_PATH 1100

#include "ADT/boolean.h"

void finishWriteFile();
void startWriteFile(char* path);

void startReadFile(char* path);
void finishReadFile();
void readNext(char* str, char* mark, int max);

void ignore(char* chars);
void readTill(char* buff, char* mark, int max);
int readInt();

void nextLine();
void nextWord();
void saveIO();

boolean checkDirectoryExsistence(char* path);
boolean checkFileExist (char *filename);

#endif