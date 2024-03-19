#include "_test_.h"
#include "../lib/user.h"
#include "../lib/ADT/boolean.h"
#include "../lib/routine.h"

int main(){
    DEFINE_TEST("Daftar Pengguna", 
        setup();
        char err[MAX_ERROR] = "\0";

        SUB_TEST(
            char in[] = "Yati;Aku suka Waluh Kukus;"; char* out;

            interceptStdIO(in, &out);
            signUp();
            clearStdIO();

            assert_string_include(err, out, "Masukkan kata sandi");
            prependError(err, "Perintah DAFTAR. Gagal, masukan nama. ");
        ,err);   

        SUB_TEST(
            char in[] = "Yatu;Aku suka Waluh Kukus;"; char* out;

            interceptStdIO(in, &out);
            signUp();
            clearStdIO();

            assert_string_include(err, out, "berhasil terdaftar");
            prependError(err, "Perintah DAFTAR. Gagal, masukan kata sandi. ");
        ,err);

        SUB_TEST(
            char in[] = "Yati;;;"; char* out;
            
            interceptStdIO(in, &out);
            signUp();            
            clearStdIO();

            assert_string_include(err, out, "Nama telah dipakai");
            prependError(err, "Perintah DAFTAR. Gagal, nama sudah dipakai. ");
        ,err);        

        SUB_TEST(
            char in[] = "Yati; Yate;password;"; char* out;
            
            interceptStdIO(in, &out);
            signUp();
            clearStdIO();

            assert_string_include(err, out, "Masukkan kata sandi");
            prependError(err, "Perintah DAFTAR. Gagal, nama sudah dipakai, dilanjutkan nama baru. ");
        ,err);        

         SUB_TEST(
            char in[] = "Yati; Yato;;"; char* out;
            
            interceptStdIO(in, &out);
            signUp();
            clearStdIO();

            assert_string_include(err, out, "berhasil terdaftar");
            prependError(err, "Perintah DAFTAR. Gagal, nama sudah dipakai, dilanjutkan nama baru. ");
        ,err);        
        
        cleanup();
    , err);

    DEFINE_TEST("Masuk Pengguna", 
        setup();
        char err[MAX_ERROR] = "\0";

        UserId id = createUser("Tuan Bri", "TuanHakJahad");

        SUB_TEST(
            char in[] = "Tuan Hak;Tuan Bri;VincentC3mungud;TuanHakJahad;"; char* out;
            
            interceptStdIO(in, &out);
            //signIn();
            clearStdIO();

            assert_string_include(err, out, "signIn seg fault");
            // assert_string_include(err, out, "User tidak ditemukan");
            prependError(err, "Perintah MASUK. Gagal, user tidak ditemukan. ");
        ,err);


        SUB_TEST(
            char in[] = "Tuan Hak;Tuan Bri;VincentC3mungud;TuanHakJahad;"; char* out;
            
            interceptStdIO(in, &out);
            signIn();
            clearStdIO();

            assert_string_include(err, out, "Masukkan kata sandi");
            prependError(err, "Perintah MASUK. Gagal, meminta nama user baru. ");
        ,err);

        SUB_TEST(
            char in[] = "Tuan Hak;Tuan Bri;VincentC3mungud;TuanHakJahad;"; char* out;
            
            interceptStdIO(in, &out);
            signIn();
            clearStdIO();

            assert_string_include(err, out, "Periksa kembali kata sandi");
            prependError(err, "Perintah MASUK. Gagal, kata sandi salah. ");
        ,err);

        SUB_TEST(
            char in[] = "Tuan Hak;Tuan Bri;VincentC3mungud;TuanHakJahad;"; char* out;
            
            interceptStdIO(in, &out);
            signIn();
            clearStdIO();
            
            assert_string_include(err, out, "Periksa kembali kata sandi");
            prependError(err, "Perintah MASUK. Gagal, kata sandi salah. ");
        ,err);

        SUB_TEST(
            char in[] = "Tuan Hak;Tuan Bri;VincentC3mungud;TuanHakJahad;"; char* out;
            
            interceptStdIO(in, &out);
            signIn();
            clearStdIO();

            assert_string_include(err, out, "Anda telah berhasil masuk");
            prependError(err, "Perintah MASUK. Gagal, pengguna tidak login. ");
        ,err);

        UserId id2 = createUser("temp","");
        loggedUser = getUser(id2);

        SUB_TEST(
            char in[] = ""; char* out;
            
            interceptStdIO(in, &out);
            signIn();
            clearStdIO();

            assert_string_include(err, out, "Anda sudah masuk");
            prependError(err, "Perintah MASUK. Gagal, pengguna sudah login. ");
        ,err);   

      cleanup();
    , err);

    DEFINE_TEST("Keluar Pengguna", 
        setup();
        char err[MAX_ERROR] = "\0";

        SUB_TEST(
            char in[] = ""; char* out;
            
            interceptStdIO(in, &out);
            signOut();
            clearStdIO();

            assert_string_include(err, out, "Anda belum login");
            prependError(err, "Perintah KELUAR. Gagal, pengguna belum login. ");
        ,err);

        UserId id = createUser("temp","");
        loggedUser = getUser(id);

        SUB_TEST(
            char in[] = ""; char* out;
            
            interceptStdIO(in, &out);
            signOut();
            clearStdIO();

            assert_string_include(err, out, "Anda berhasil logout");
            prependError(err, "Perintah KELUAR. Gagal, pengguna belum keluar. ");
        ,err);

      cleanup();
    , err);

    DEFINE_TEST("Ganti Profil", 
        setup();
        char err[MAX_ERROR] = "\0";
        UserId id = createUser("TuanHak","");
        loggedUser = getUser(id);

        SUB_TEST(    
            char in[] = "Aku cinta tubes <3;08a a-;0811111111;Pahig;;"; char* out;
            interceptStdIO(in, &out);
            changeProfileIO();
            clearStdIO();
        
            assert_string_include(err, out, "Weton:");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, menampilkan profil. ");
        ,err);

        SUB_TEST(    
            char in[] = "Aku cinta tubes <3;08a a-;0811111111;Pahig;;"; char* out;
            interceptStdIO(in, &out);
            changeProfileIO();
            clearStdIO();
        
            assert_string_include(err, out, "Masukkan No HP");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, mengubah bio akun. ");
        ,err);

        SUB_TEST(    
            char in[] = "Aku cinta tubes <3;08a a-;0811111111;Pahig;;"; char* out;
            interceptStdIO(in, &out);
            changeProfileIO();
            clearStdIO();
        
            assert_string_include(err, out, "HP tidak valid");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, No HP tidak valid. ");
        ,err);
        
        SUB_TEST(    
            char in[] = "Aku cinta tubes <3;08a a-;0811111111;Pahig;;"; char* out;
            interceptStdIO(in, &out);
            changeProfileIO();
            clearStdIO();
        
            assert_string_include(err, out, "Masukkan Weton:");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, mengubah No HP. ");
        ,err);
        
        SUB_TEST(    
            char in[] = "Aku cinta tubes <3;08a a-;0811111111;Pahig;;"; char* out;
            interceptStdIO(in, &out);
            changeProfileIO();
            clearStdIO();
        
            assert_string_include(err, out, "Weton anda tidak valid");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, weton tidak valid. ");
        ,err);

        SUB_TEST(    
            char in[] = "Aku cinta tubes <3;08a a-;0811111111;Pahig;;"; char* out;
            interceptStdIO(in, &out);
            changeProfileIO();
            clearStdIO();
        
            assert_string_include(err, out, "berhasil diperbarui");
            prependError(err, "Perintah GANTI_PROFIL. Gagal, mengubah weton dengan string kosong. ");
        ,err);
        
        cleanup();
    , err);

    DEFINE_TEST("Lihat Profil", 
        setup();
        char err[MAX_ERROR] = "\0";
        UserId id1 = createUser("TuanHak","");
        UserId id2 = createUser("TuanBri","");
        UserId id3 = createUser("TuanPrim","");
        loggedUser = getUser(id1);
        getUser(id2)->type = PUBLIC_USER;
        getUser(id3)->type = PRIVATE_USER;

        SUB_TEST(    
            char in[] = ""; char* out;
            interceptStdIO(in, &out);
            displayProfileIO(getUser(id2)->name);
            clearStdIO();
        
            assert_string_include(err, out, "Nama");
            prependError(err, "Perintah LIHAT_PROFIL. Gagal, menampilkan profil public. ");
        ,err);

        SUB_TEST(    
            char in[] = ""; char* out;
            interceptStdIO(in, &out);
            displayProfileIO(getUser(id3)->name);
            clearStdIO();
        
            assert_string_include(err, out, "privat");
            prependError(err, "Perintah LIHAT_PROFIL. Gagal, menampilkan profil privat. ");
        ,err);
        
        cleanup();
    , err);

    DEFINE_TEST("Atur Jenis Akun", 
        setup();
        char err[MAX_ERROR] = "\0";
        UserId id = createUser("TuanHak","");
        loggedUser = getUser(id);
        getUser(id)->type = PUBLIC_USER;

        SUB_TEST(    
            char in[] = "TIDAK;"; char* out;
            interceptStdIO(in, &out);
            changeAccountTypeIO();
            clearStdIO();
        
            assert_string_include(err, out, "akun Publik");
            prependError(err, "Perintah ATUR_JENIS_AKUN. Gagal, menampilkan jenis akun. ");
        ,err);

        SUB_TEST(    
            char in[] = "YA;"; char* out;
            interceptStdIO(in, &out);
            changeAccountTypeIO();
            clearStdIO();
        
            assert_string_include(err, out, "akun Privat");
            prependError(err, "Perintah ATUR_JENIS_AKUN. Gagal, mengubah jenis akun. ");
        ,err);
        
        getUser(id)->type = PRIVATE_USER;

        SUB_TEST(    
            char in[] = "TIDAK;"; char* out;
            interceptStdIO(in, &out);
            changeAccountTypeIO();
            clearStdIO();
        
            assert_string_include(err, out, "akun Privat");
            prependError(err, "Perintah ATUR_JENIS_AKUN. Gagal, menampilkan jenis akun. ");
        ,err);

        cleanup();
    , err);

    DEFINE_TEST("Ubah Foto Profil", 
        setup();
        char err[MAX_ERROR] = "\0";
        UserId id = createUser("TuanHak","");
        loggedUser = getUser(id);
        getUser(id)->type = PUBLIC_USER;

        SUB_TEST(    
            char in[] = "R * R * R * R * R *\nR * G @ B * G @ R *\nR * G @ G @ G @ R *\nR * G @ B * G @ R *\nR * R * R * R * R *;"; 
            char* out;
            interceptStdIO(in, &out);
            changePhotoProfileIO();
            clearStdIO();
        
            assert_string_include(err, out, "Foto profil");
            prependError(err, "Perintah UBAH_FOTO_PROFIL. Gagal, menampilkan foto saat ini. ");
        ,err);

        SUB_TEST(    
            char in[] = "YA;"; char* out;
            interceptStdIO(in, &out);
            changePhotoProfileIO();
            clearStdIO();
        
            assert_string_include(err, out, "berhasil diganti");
            prependError(err, "Perintah UBAH_FOTO_PROFIL. Gagal, mengubah foto profil. ");
        ,err);
        
        getUser(id)->type = PRIVATE_USER;

        cleanup();
    , err);
}