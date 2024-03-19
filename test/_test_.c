#include <stdio.h>
#include "_test_.h"
#include "../lib/ADT/boolean.h"
#include "../lib/string.h"

void test(){
    printf("This is a test!\n");
}

static boolean intercepted;
static FILE* interceptor;
static FILE* feeder;
static FILE* originalStdOut;
static FILE* originalStdIn;
size_t len;

void interceptStdIO(char* bufIn, char** bufOut){
    if(intercepted) return;
    intercepted = true;

    interceptor = open_memstream(bufOut, &len);
    feeder = fmemopen(bufIn, string_length(bufIn), "r");

    originalStdIn = stdin;
    originalStdOut = stdout;

    stdin = feeder;
    stdout = interceptor;
}

void assert_integer_equal(char* err, int actual, int expected){
    assert_true(err, actual == expected, "Integer expected: %d, actual %d", expected, actual);
}

void assert_pointer_equal(char* err, void* actual, void* expected){
    assert_true(err, actual == expected, "Pointer expected: %p, actual %p", expected, actual);
}

void assert_string_equal(char* err, char* actual, char* expected){
    char fActual[MAX_ERROR], fExpected[MAX_ERROR];
    boolean b = string_compare(actual, expected) == 0;
    if(!b){
        string_replace(actual, fActual, "\n", "\\n", MAX_ERROR);
        string_replace(expected, fExpected, "\n", "\\n", MAX_ERROR);
    }
    assert_true(err, b, "String expected: \"%s\", actual: \"%s\"", fExpected, fActual);
}

void assert_string_include(char* err, char* actual, char* expected){
    char fActual[MAX_ERROR], fExpected[MAX_ERROR];
    boolean b = string_include(actual, expected);
    if (!b){
        string_replace(actual, fActual, "\n", "\\n", MAX_ERROR);
        string_replace(expected, fExpected, "\n", "\\n", MAX_ERROR);
    }
    assert_true(err, b, "String \"%s\" not included in \"%s\"", fExpected, fActual);
}

void prependError(char* err, char* str){
    if(*err){
        int l = string_length(str);
        char tmp[MAX_ERROR];
        string_copy(err, tmp, MAX_ERROR);

        string_copy(str, err, MAX_ERROR);
        string_copy(tmp, err + l, MAX_ERROR - l);
    }
}

void clearStdIO(){
    if(!intercepted) return;
    intercepted = false;

    fflush(interceptor);
    fclose(interceptor);
    fclose(feeder);

    stdin = originalStdIn;
    stdout = originalStdOut;
}