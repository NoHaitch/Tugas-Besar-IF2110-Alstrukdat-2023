#include <stdio.h>
#include "../lib/string.h"
#include "_test_.h"

int main(){
    DEFINE_TEST("IO intercept",
        char err[MAX_ERROR];
        char in[] = "1 2"; char* out;

        interceptStdIO(in, &out);

        int a;
        int b;
        scanf("%d %d", &a, &b);
        printf("%d", a + b);

        clearStdIO();

        assert_string_equal(err, out, "3");
    , err)
}