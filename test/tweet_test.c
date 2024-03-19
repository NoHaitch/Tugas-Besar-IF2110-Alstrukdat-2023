#include "_test_.h"
#include "../lib/ADT/boolean.h"
#include "../lib/tweet.h"
#include "../lib/relation.h"
#include "../lib/user.h"
#include "../lib/routine.h"
#include "../lib/string.h"

int main(){
    DEFINE_TEST("Kicau", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId id = createUser("Ciko", "");
        loggedUser = getUser(id);

        SUB_TEST(
            char in[] = "Hello Burbir!;"; char* out;

            interceptStdIO(in, &out);
            createTweetIO();
            clearStdIO();

            assert_string_include(err, out, "diterbitkan");
            prependError(err, "Perintah KICAU. Gagal, membuat kicauan. ");
        ,err); 
        
        SUB_TEST(
            char in[] = ";"; char* out;

            interceptStdIO(in, &out);
            createTweetIO();
            clearStdIO();

            assert_string_include(err, out, "tidak boleh");
            prependError(err, "Perintah KICAU. Gagal, membuat kicauan kosong. ");
        ,err); 

        SUB_TEST(
            char in[] = "Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since the 1500s, when an unknown printer took a galley of type and scrambled it to make a type specimen book. It has survived not only five centuries, but also the leap into electronic typesetting, remaining essentially unchanged.;"; char* out;

            interceptStdIO(in, &out);
            createTweetIO();
            clearStdIO();

            assert_string_include(err, out, "five cent");
            prependError(err, "Perintah KICAU. Gagal, memotong kicauan yang terlalu panjang. ");
        ,err); 

        cleanup();
    , err);

    DEFINE_TEST("Kicauan", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(ida);
        addFriend(idb, ida);

        createTweet("haloo ini ciko!",ida);
        createTweet("haloo ini afif!",idb);

        SUB_TEST(
            char in[] = "Hello Burbir!;"; char* out;

            interceptStdIO(in, &out);
            displayAllTweetIO();
            clearStdIO();

            assert_string_include(err, out, "haloo ini afif!");
            prependError(err, "Perintah KICAUAN. Gagal, menampilkan semua kicauan. ");
        ,err); 
        
        cleanup();
    , err);

    DEFINE_TEST("Suka Kicauan", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(ida);
        addFriend(idb, ida);


        TweetId tId1 = createTweet("haloo ini ciko!",ida);
        createTweet("haloo ini afif!",idb);

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            likeTweetIO("1000");
            clearStdIO();

            assert_string_include(err, out, "Tidak ditemukan");
            prependError(err, "Perintah SUKA_KICAUAN [IDKicau]. Gagal, kicauan tidak ditemukan. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            likeTweetIO("6");
            clearStdIO();

            assert_string_include(err, out, "kicauan telah disukai");
            prependError(err, "Perintah SUKA_KICAUAN [IDKicau]. Gagal, kicauan tidak berhasil disukai. ");
        ,err); 

        UserId idc = createUser("Berto", "");
        getUser(idc)->type = PRIVATE_USER;
        TweetId tId2 = createTweet("Halo ini berto!",idc);
        
        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            likeTweetIO("6");
            clearStdIO();

            assert_string_include(err, out, "kicauan telah disukai");
            prependError(err, "Perintah SUKA_KICAUAN [IDKicau]. Gagal, kicauan tidak berhasil disukai. ");
        ,err); 

        cleanup();
    , err);

    DEFINE_TEST("Ubah Kicauan", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(ida);

        TweetId tId1 = createTweet("haloo ini ciko!",ida);
        TweetId tId2 = createTweet("haloo ini afif!",idb);

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            editTweetIO("1");
            clearStdIO();

            assert_string_include(err, out, "bukan milikmu");
            prependError(err, "Perintah UBAH_KICAUAN [IDKicau]. Gagal, kicauan bukan milik pengguna. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            editTweetIO("999");
            clearStdIO();

            assert_string_include(err, out, "Tidak ditemukan");
            prependError(err, "Perintah UBAH_KICAUAN [IDKicau]. Gagal, kicauan tidak ditemukan. ");
        ,err); 

        SUB_TEST(
            char in[] = "Wilujeng enjing, BurBir!;"; char* out;

            interceptStdIO(in, &out);
            editTweetIO("9");
            clearStdIO();

            assert_string_include(err, out, "telah diterbitkan");
            prependError(err, "Perintah UBAH_KICAUAN [IDKicau]. Gagal, mengubah kicauan. ");
        ,err); 

        cleanup();
    , err);
}