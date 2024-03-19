#include "_test_.h"
#include "../lib/ADT/boolean.h"
#include "../lib/reply.h"
#include "../lib/relation.h"
#include "../lib/tweet.h"
#include "../lib/user.h"
#include "../lib/routine.h"
#include "../lib/string.h"

int main(){
    char rawTweetId[10];
    char rawReplyId[10];

    DEFINE_TEST("Balas", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(idb);
        getUser(ida)->type = PUBLIC_USER;

        TweetId tweetId = createTweet("haloo ini ciko!",ida);
        snprintf(rawTweetId, 10, "%d", tweetId);

        SUB_TEST(
            char in[] = "Hello BurBir!;"; char* out;

            interceptStdIO(in, &out);
            createReplyIO(rawTweetId, "-1");
            clearStdIO();

            assert_string_include(err, out, "terbit");
            prependError(err, "Perintah BALAS [IDKicau] [IDBalasan]. Gagal, membuat balasan akun publik. ");
        ,err); 

        getUser(ida)->type = PRIVATE_USER;
        
        SUB_TEST(
            char in[] = "Hello BurBir!;"; char* out;

            interceptStdIO(in, &out);
            createReplyIO(rawTweetId, "-1");
            clearStdIO();

            assert_string_include(err, out, "akun privat");
            prependError(err, "Perintah BALAS [IDKicau] [IDBalasan]. Gagal, membuat balasan akun privat. ");
        ,err); 
        
        addFriend(ida,idb);

        SUB_TEST(
            char in[] = "Hello BurBir!;"; char* out;

            interceptStdIO(in, &out);
            createReplyIO(rawTweetId, "-1");
            clearStdIO();

            assert_string_include(err, out, "balasan telah diterbitkan");
            prependError(err, "Perintah BALAS [IDKicau] [IDBalasan]. Gagal, membuat balasan akun privat yang telah bertaman. ");
        ,err); 

        SUB_TEST(
            char in[] = "Hello BurBir!;"; char* out;

            interceptStdIO(in, &out);
            createReplyIO(rawTweetId, "100");
            clearStdIO();

            assert_string_include(err, out, "tidak terdapat balasan");
            prependError(err, "Perintah BALAS [IDKicau] [IDBalasan]. Gagal, tidak terdapat balasan. ");
        ,err); 

        SUB_TEST(
            char in[] = "Hello BurBir!;"; char* out;

            interceptStdIO(in, &out);
            createReplyIO("100", "-1");
            clearStdIO();

            assert_string_include(err, out, "tidak terdapat kicauan");
            prependError(err, "Perintah BALAS [IDKicau] [IDBalasan]. Gagal, tidak terdapat kicauan. ");
        ,err); 

        cleanup();
    , err);

    DEFINE_TEST("Balasan", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(idb);
        loggedUser->type = PUBLIC_USER;

        TweetId tId1 = createTweet("haloo ini ciko1!",ida);
        TweetId tId2 = createTweet("haloo ini ciko2!",ida);
        snprintf(rawTweetId, 10, "%d", tId1);

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayReplyIO(rawTweetId);
            clearStdIO();

            assert_string_include(err, out, "Belum terdapat balasan");
            prependError(err, "Perintah BALASAN [IDKicau]. Gagal, tidak ada balasan. ");
        ,err); 

        ReplyPointer r;
        createReply("Ini reply", ida, tId1, getReplies(tId1, -1), &r);

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayReplyIO(rawTweetId);
            clearStdIO();

            assert_string_include(err, out, "Ini reply");
            prependError(err, "Perintah BALASAN [IDKicau]. Gagal, menampilkan balasan. ");
        ,err); 

        getUser(ida)->type = PRIVATE_USER;

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayReplyIO(rawTweetId);
            clearStdIO();

            assert_string_include(err, out, "PRIVAT");
            prependError(err, "Perintah BALASAN [IDKicau]. Gagal, balasan kicauan akun privat. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayReplyIO("100");
            clearStdIO();

            assert_string_include(err, out, "Tidak ditemukan tweet");
            prependError(err, "Perintah BALASAN [IDKicau]. Gagal, tidak ditemukan tweet id. ");
        ,err); 

        cleanup();
    , err);

    DEFINE_TEST("Hapus Balasan", 
        setup();

        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(idb);
        loggedUser->type = PUBLIC_USER;

        TweetId tId1 = createTweet("haloo ini ciko1!",ida);
        snprintf(rawTweetId, 10, "%d", tId1);
            
        ReplyPointer r;
        createReply("Ini reply", idb, tId1, getReplies(tId1, -1), &r);
        snprintf(rawReplyId, 10, "%d", r->id);

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            deleteReplyIO(rawTweetId, rawReplyId);
            clearStdIO();

            assert_string_include(err, out, "berhasil dihapus");
            prependError(err, "Perintah HAPUS_BALASAN [IDKicau] [IDBalasan]. Gagal, menghapus balasan. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            deleteReplyIO(rawTweetId, "5");
            clearStdIO();

            assert_string_include(err, out, "tidak ditemukan");
            prependError(err, "Perintah HAPUS_BALASAN [IDKicau] [IDBalasan]. Gagal, balasan tidak ditemukan. ");
        ,err); 

        createReply("Ini reply", ida, tId1, getReplies(tId1, -1), &r);
        snprintf(rawReplyId, 10, "%d", r->id);

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            deleteReplyIO(rawTweetId, rawReplyId);
            clearStdIO();

            assert_string_include(err, out, "bukan milik anda");
            prependError(err, "Perintah HAPUS_BALASAN [IDKicau] [IDBalasan]. Gagal, balasan bukan milik pengguna. ");
        ,err); 

        cleanup();
    , err);
}