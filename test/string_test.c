#include "_test_.h"
#include "../lib/ADT/boolean.h"
#include "../lib/string.h"

int main(){
    DEFINE_TEST("String length", 
        char err[MAX_ERROR] = "";
        int l = string_length("12345");
        assert_integer_equal(err, 5, l);
    , err)
    
    DEFINE_TEST("String copy",
        char a[] = "abcdefgh";
        char b[10] = "\0";

        string_copy(a, b, 10);

        boolean res = string_compare(a, b) == 0;

        char err[MAX_ERROR] = "";
        assert_string_equal(err, b, a);
    , err);

    DEFINE_TEST("String compare",
        int t; char err[MAX_ERROR] = "";

        SUB_TEST(
            int t = string_compare("a", "b");
            assert_true(err, t, "Since a < b, expected -1. Instead got %d", t);
        , err)

        SUB_TEST(
            int t = string_compare("a", "b");
            assert_true(err, t == -1, "Since a < b, expected -1. Instead got %d", t);
        , err)

        SUB_TEST(
            int t = string_compare("b", "a");
            assert_true(err, t == 1, "Since b < a, expected 1. Instead got %d", t);
        , err)

        SUB_TEST(
            int t = string_compare("a", "aa");
            assert_true(err, t == -1, "Since a < aa, expected -1. Instead got %d", t);
        , err)

        SUB_TEST(
            int t = string_compare("aa", "a");
            assert_true(err, t == 1, "Since aa < a, expected 1. Instead got %d", t);
        , err)

        SUB_TEST(
            int t = string_compare("aaa", "aaa");
            assert_true(err, t == 0, "Since aaa = aaa, expected 0. Instead got %d", t);
        , err)
    , err)

    DEFINE_TEST("String include",
        char err[MAX_ERROR] = "";
        assert_string_include(err, "abcd", "bc");
    , err);
}