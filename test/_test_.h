#ifndef TEST
#define TEST

#include <stdio.h>
#include "../lib/string.h"

#define MAX_ERROR 1000
#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"

#define DEFINE_TEST(_name, _test, _error) {\
    _test;\
    if(!(*_error)){\
        printf("\x1B[32m✓ \x1B[0m%s\n", _name);\
    }else{\
        printf("\x1B[31m✗ \x1B[0m%s ", _name);\
        if(*_error) printf("(%s)", _error);\
        printf("\n");\
    }\
}

#define SUB_TEST(_test, _error){\
    if(!(*_error)){\
        _test;\
    }\
}

/* DANGEROUS, since we allow for 10.000 char to be writen to 1.000 buffer, can cause Buffer-Overflow */
#define assert_true(err, res, ...) {\
    if(!(res)) snprintf(err, MAX_ERROR * 10, __VA_ARGS__);\
    else (err)[0] = '\0';\
}


void assert_integer_equal(char* err, int actual, int expected);
void assert_pointer_equal(char* err, void* actual, void* expected);
void assert_string_equal(char* err, char* actual, char* expected);
void assert_string_include(char* err, char* actual, char* expected);

void test();
void prependError(char* err, char* str);
void interceptStdIO(char* bufIn, char** bufOut);
void clearStdIO();

#endif