#include "_test_.h"
#include "../lib/greet.h"
#include "../lib/ADT/boolean.h"
#include "../lib/string.h"

int main(){
    DEFINE_TEST("Greet IO Lib",
        char err[MAX_ERROR];
        char in[] = ""; char* out;

        interceptStdIO(in, &out);
        greet("Bondowoso");
        clearStdIO();

        char expected[] = "Hello, Bondowoso!";
        assert_string_include(err, out, "Bondowoso")
    , err)
}