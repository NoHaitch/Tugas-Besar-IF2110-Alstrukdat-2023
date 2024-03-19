#include <stdio.h>
#include "string.h"
#include "ADT/boolean.h"

void string_append(char* start, char* end, char* to, int max){
    int startLength = string_length(start);
    string_copy(start, to, max);
    string_copy(end, &to[startLength], max - startLength);
}

void string_copy(char* from, char* to, int max){
    if(max == 0) return;

    int i = 0;
    for(; i < max - 1; ++i){
        if(from[i] == '\0') break;
        to[i] = from[i];
    }
    to[i] = '\0';
};

int string_compare(char* a, char* b){
    int ia = 0, ib = 0;
    while(a[ia] != '\0' && b[ib] != '\0'){
        if(a[ia] > b[ib]){
            return 1;
        } else if(a[ia] < b[ib]){
            return -1;
        }

        ia++; ib++;
    }

    if(a[ia] == '\0' && b[ib] == '\0') return 0;
    else if(a[ia] == '\0') return -1;
    else return 1;
}

boolean string_equal(char* a, char* b){
    return string_compare(a, b) == 0;
}

int string_length(char* a){
    int i = 0;
    while (a[i] != '\0'){
        i++;
    }
    return i;
}

boolean isAllBlank(char* a){
    int i = 0 ; 
    while (a[i] != '\0'){
        if (a[i] != ' ') return false;
        i++;
    }
    return true ; 
}

boolean string_include(char* str, char* substr){
    int strLen = string_length(str);
    int substrLen = string_length(substr);

    for(int i = 0; i <= strLen - substrLen; ++i){
        int m = 0;
        for(int j = 0; j < substrLen; ++j){
            if(str[i + j] == substr[j]) ++m;
            else break;
        }

        if(m == substrLen) return true;
    }
    return false;
}

void string_replace(char* target, char* result, char* from, char* to, int max){
    int targetLen = string_length(target);
    int fromLen = string_length(from);
    int toLen = string_length(to);

    char tmp[targetLen + 1];
    string_copy(target, tmp, max);

    int p = 0, i = 0;
    while(i <= targetLen - fromLen && p < max - 1){
        boolean found = true;
        int j = 0;
        while(found && j < fromLen){
            if(tmp[i + j] != from[j]) found = false;
            j++;
        }

        if(found){
            j = 0;
            while(j < toLen && p < max - 1){
                result[p] = to[j];
                j++; p++;
            }
            i += fromLen;
        } else {
            result[p] = tmp[i];
            i++; p++;
        }
    }
    result[p] = '\0';
}

boolean string_to_integer(char* buffer, int* value){
    int r = 0;

    int i = 0;
    boolean negated = false;
    if(buffer[i] == '-'){
        negated = true;
        ++i;
    }


    boolean status = true;
    while(buffer[i] != '\0'){
        int v = buffer[i] - '0';
        if(0 <= v && v <= 9){
            r = (r * 10) + v;
        } else {
            status = false;
        };
        ++i;
    }

    if(negated) r *= -1;
    *value = r;
    return status;
}

void lowercase(char* from, char* to, int max){
    int n;
    n = string_length(from);
    string_copy(from,to,max);
    for (int i = 0; i < n; i++){
        if (to[i] < 'a'){
            to[i] += 32;
        }
    }
}