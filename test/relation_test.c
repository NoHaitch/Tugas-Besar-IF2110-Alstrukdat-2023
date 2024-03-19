#include "_test_.h"
#include "../lib/ADT/boolean.h"
#include "../lib/relation.h"
#include "../lib/user.h"
#include "../lib/routine.h"
#include "../lib/string.h"

int main(){
    DEFINE_TEST("Daftar Teman", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(ida);

        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayFriendIO();
            clearStdIO();

            assert_string_include(err, out, "belum mempunyai teman");
            prependError(err, "Perintah DAFTAR_TEMAN. Gagal, tidak memiliki teman. ");
        ,err);

        requestFriend(ida,idb, getFriendCount(idb));
        addFriend(ida,idb); 
        
        SUB_TEST(
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayFriendIO();
            clearStdIO();

            assert_string_include(err, out, "Daftar teman");
            prependError(err, "Perintah DAFTAR_TEMAN. Gagal, menampilkan teman. ");
            
        ,err);

        cleanup();
    , err)


    DEFINE_TEST("Hapus Teman", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        loggedUser = getUser(ida);
        
        SUB_TEST( 
            char in[] = "Afif;"; char* out;

            interceptStdIO(in, &out);
            removeFriendIO();
            clearStdIO();

            assert_string_include(err, out, "bukan teman Anda");
            prependError(err, "Perintah HAPUS_TEMAN. Gagal, menghapus teman. ");
        ,err)

        addFriend(ida, idb);

        SUB_TEST( 
            char in[] = "Afif;TIDAK;"; char* out;

            interceptStdIO(in, &out);
            removeFriendIO();
            clearStdIO();

            assert_string_include(err, out, "Penghapusan teman dibatalkan");
            prependError(err, "Perintah HAPUS_TEMAN. Gagal, pembatalan hapus. ");
        ,err)

        SUB_TEST( 
            char in[] = "Afif;YA;"; char* out;

            interceptStdIO(in, &out);
            removeFriendIO();
            clearStdIO();

            assert_string_include(err, out, "berhasil dihapus");
            prependError(err, "Perintah HAPUS_TEMAN. Gagal, menghapuskan teman. ");
        ,err)

        cleanup();
    , err)

    DEFINE_TEST("Tambah Teman", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        UserId idc = createUser("Berto", "");
        loggedUser = getUser(ida);
        
        SUB_TEST( 
            char in[] = "Afif;"; char* out;

            interceptStdIO(in, &out);
            requestFriendIO();
            clearStdIO();

            assert_string_include(err, out, "telah dikirim");
            prependError(err, "Perintah TAMBAH_TEMAN. Gagal, meminta pertemanan. ");
        ,err)

        SUB_TEST( 
            char in[] = "Carol;"; char* out;

            interceptStdIO(in, &out);
            requestFriendIO();
            clearStdIO();

            assert_string_include(err, out, "tidak ditemukan");
            prependError(err, "Perintah TAMBAH_TEMAN. Gagal, pengguna tidak ditemukan. ");
        ,err)

        requestFriend(idc,ida);

        SUB_TEST( 
            char in[] = ";"; char* out;

            interceptStdIO(in, &out);
            requestFriendIO();
            clearStdIO();

            assert_string_include(err, out, "kosongkan daftar permintaan");
            prependError(err, "Perintah TAMBAH_TEMAN. Gagal, pengguna tidak ditemukan. ");
        ,err)

        cleanup();
    , err)

    DEFINE_TEST("Daftar Permintaan Pertemanan", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        UserId idc = createUser("Berto", "");
        loggedUser = getUser(ida);
        
        SUB_TEST( 
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayRequestedFriendIO();
            clearStdIO();

            assert_string_include(err, out, "Tidak ada permintaan");
            prependError(err, "Perintah DAFTAR_PERMINTAAN_PERTEMANAN. Gagal, menunjukan daftar permintaan kosong. ");
        ,err)

        requestFriend(idb,ida);
        requestFriend(idc,ida);

        SUB_TEST( 
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayRequestedFriendIO();
            clearStdIO();

            assert_string_include(err, out, "permintaan pertemanan untuk Anda");
            prependError(err, "Perintah DAFTAR_PERMINTAAN_PERTEMANAN. Gagal, menunjukan daftar permintaan pertemanan. ");
        ,err)

        cleanup();
    , err)

    DEFINE_TEST("Setujui Pertemanan", 
        setup();
        
        char err[MAX_ERROR] = "\0";
        UserId ida = createUser("Ciko", "");
        UserId idb = createUser("Afif", "");
        UserId idc = createUser("Berto", "");
        loggedUser = getUser(ida);
        requestFriend(idb,ida);
        requestFriend(idc,ida);
        
        SUB_TEST( 
            char in[] = "YA;"; char* out;

            interceptStdIO(in, &out);
            acceptFriendIO();
            clearStdIO();

            assert_string_include(err, out, "telah berteman");
            prependError(err, "Perintah SETUJUI_PERTEMANAN. Gagal, menyetujui pertemanan. ");
        ,err)

        SUB_TEST( 
            char in[] = "TIDAK;"; char* out;

            interceptStdIO(in, &out);
            acceptFriendIO();
            clearStdIO();

            assert_string_include(err, out, "telah ditolak");
            prependError(err, "Perintah SETUJUI_PERTEMANAN. Gagal, menyetujui pertemanan. ");
        ,err)

        cleanup();
    , err)
}

