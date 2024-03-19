#include "_test_.h"
#include "../lib/get_string.h"
#include "../lib/string.h"
#include "../lib/ADT/boolean.h"

boolean isGreater(int a, int b){
    return a > b;
}

boolean isLess(int a, int b){
    return a > b;
}

void greet(){
    char* s;
    get_string(s, 100);
    printf("Halo, %s!", s);
}

int main(){
    DEFINE_TEST("isGreater Function",
        char err[MAX_ERROR];
        assert_true(err, isGreater(2, 1), "1 > 2");
    , err);

    DEFINE_TEST("isLess Function", 
        char err[MAX_ERROR];
        assert_true(err, isLess(1, 2), "1 < 2");
    , err);

    DEFINE_TEST("Greet IO",
        char in[] = "Bondowoso;"; char* out;

        interceptStdIO(in, &out);
        greet();
        clearStdIO();

        char expected[] = "Hello, Bondowoso!";
        boolean res = string_compare(expected, out) == 0;

        char err[MAX_ERROR];
        assert_string_equal(err, out, expected)
    , err)
}