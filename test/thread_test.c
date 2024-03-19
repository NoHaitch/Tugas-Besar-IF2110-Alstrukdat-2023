#include "_test_.h"
#include "../lib/ADT/boolean.h"
#include "../lib/thread.h"
#include "../lib/tweet.h"
#include "../lib/user.h"
#include "../lib/routine.h"
#include "../lib/string.h"

int main(){
    DEFINE_TEST("Utas", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(ida);

        TweetId tId1 = createTweet("haloo ini ciko!",ida);
        TweetId tId2 = createTweet("haloo ini afif!",idb);

        SUB_TEST(
            char in[] = "Hello BurBir!;YA;Apakah BurBir sehat?;YA;BurBir sangat sehat hari ini.;TIDAK;"; char* out;

            interceptStdIO(in, &out);
            //makeMainThreadIO(tId1);
            clearStdIO();

            assert_string_include(err, out, "berhasil dibuat");
            prependError(err, "Perintah UTAS [IDKicau]. Gagal, membuat utas. ");
        ,err); 
        
        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            //makeMainThreadIO(tId2);
            clearStdIO();

            assert_string_include(err, out, "bukan milik Anda");
            prependError(err, "Perintah UTAS [IDKicau]. Gagal, membuat utas. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            //makeMainThreadIO(100);
            clearStdIO();

            assert_string_include(err, out, "Kicauan tidak ditemukan");
            prependError(err, "Perintah UTAS [IDKicau]. Gagal, kicauan tidak ditemukan. ");
        ,err); 

        cleanup();
    , err);

    
    DEFINE_TEST("Sambung Utas", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(ida);
        
        TweetId twId1 = createTweet("kenapa deadline deket semua!",ida);
        //makeMainThreadIO(twId1);

        SUB_TEST(
            char in[] = "Mari menyambung BurBir!;"; char* out;

            interceptStdIO(in, &out);
            //continueThreadAtIO(n,1);
            clearStdIO();

            assert_string_include(err, out, "Masukkan kicauan");
            prependError(err, "Perintah SAMBUNG_UTAS [IDUtas] [index]. Gagal, menyambung utas. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            //continueThreadAtIO(n,4);
            clearStdIO();

            assert_string_include(err, out, "Index terlalu tinggi");
            prependError(err, "Perintah SAMBUNG_UTAS [IDUtas] [index]. Gagal, index utas terlalu tinggi. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            //continueThreadAtIO(99,1);
            clearStdIO();

            assert_string_include(err, out, "tidak ditemukan");
            prependError(err, "Perintah SAMBUNG_UTAS [IDUtas] [index]. Gagal, utas tidak ditemukan. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            //continueThreadAtIO(x,1);
            clearStdIO();

            assert_string_include(err, out, "tidak bisa menyambung");
            prependError(err, "Perintah SAMBUNG_UTAS [IDUtas] [index]. Gagal, utas tidak dapat disambung. ");
        ,err); 

        cleanup();
    , err);

    DEFINE_TEST("Hapus Utas", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(ida);
        
        TweetId twId1 = createTweet("kenapa deadline deket semua!",ida);
        //makeMainThreadIO(twId1);

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            //deleteThreadAtIO(1, 1);
            clearStdIO();

            assert_string_include(err, out, "berhasil dihapus");
            prependError(err, "Perintah HAPUS_UTAS [IDUtas] [index]. Gagal, menghapus utas. ");
        ,err); 

        SUB_TEST(
            char in[] = "Mari menyambung BurBir!;"; char* out;

            interceptStdIO(in, &out);
            //deleteThreadAtIO(1, 3);
            clearStdIO();

            assert_string_include(err, out, "tidak ditemukan pada utas");
            prependError(err, "Perintah HAPUS_UTAS [IDUtas] [index]. Gagal, menghapus utas yang tidak ditemukan pada utas. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            //deleteThreadAtIO(1, 0);
            clearStdIO();

            assert_string_include(err, out, "menghapus kicauan utama");
            prependError(err, "Perintah HAPUS_UTAS [IDUtas] [index]. Gagal, menghapus kicauan utama. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            //deleteThreadAtIO(21, 1);
            clearStdIO();

            assert_string_include(err, out, "tidak ditemukan");
            prependError(err, "Perintah HAPUS_UTAS [IDUtas] [index]. Gagal, utas tidak ditemukan. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
           // deleteThreadAtIO(5, 12);
            clearStdIO();

            assert_string_include(err, out, "tidak bisa menghapus");
            prependError(err, "Perintah HAPUS_UTAS [IDUtas] [index]. Gagal, utas tidak dapat dihapus. ");
        ,err); 

        cleanup();
    , err);

    DEFINE_TEST("Cetak Utas", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(ida);
        
        TweetId twId1 = createTweet("kenapa deadline deket semua!",ida);
        //makeMainThreadIO(twId1);

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            //displayThreadSeqIO(1, 1);
            clearStdIO();

            assert_string_include(err, out, "INDEX");
            prependError(err, "Perintah CETAK_UTAS [IDUtas]. Gagal, menampilkan utas. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            //displayThreadSeqIO(1, 1);
            clearStdIO();

            assert_string_include(err, out, "tidak ditemukan");
            prependError(err, "Perintah CETAK_UTAS [IDUtas]. Gagal, menampilkan utas yang tidak ditemukan. ");
        ,err); 

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            //displayThreadSeqIO(1, 1);
            clearStdIO();

            assert_string_include(err, out, "akun privat");
            prependError(err, "Perintah CETAK_UTAS [IDUtas]. Gagal, menampilkan utas akun privat. ");
        ,err); 

        cleanup();
    , err); 
}