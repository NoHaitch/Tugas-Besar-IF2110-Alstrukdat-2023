#ifndef STRING_H
#define STRING_H

#include "ADT/boolean.h"
#define MAX_NUMBER 20

void string_append(char* start, char* end, char* to, int max);
void string_copy(char* from, char* to, int max);
int string_compare(char* a, char* b);
boolean string_equal(char* a, char* b);
int string_length(char* a);
boolean string_include(char* str, char* substr);
boolean isAllBlank(char* a);
void string_replace(char* target, char* result, char* from, char* to, int max);
boolean string_to_integer(char* buffer, int* value);
void lowercase(char* from, char* to, int max);
#endif