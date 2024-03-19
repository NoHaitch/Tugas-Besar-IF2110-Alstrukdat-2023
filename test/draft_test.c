#include "_test_.h"
#include "../lib/draft.h"
#include "../lib/user.h"
#include "../lib/ADT/boolean.h"
#include "../lib/routine.h"

int main(){
    DEFINE_TEST("Buat Draf", 
        setup();
        char err[MAX_ERROR] = "\0";
        UserId id = createUser("ciko", "");
        loggedUser = getUser(id);

        SUB_TEST(
            char in[] = "isi Draf;SIMPAN;"; char* out;
            
            interceptStdIO(in, &out);
            createDraftIO();
            clearStdIO();

            assert_string_include(err, out, "Apakah anda ingin menghapus");
            prependError(err, "Perintah BUAT_DRAFT. Gagal mengisi Konten. ");
        ,err);        
        
        SUB_TEST(
            char in[] = "isi Draf;SIMPAN;"; char* out;
            
            interceptStdIO(in, &out);
            createDraftIO();
            clearStdIO();

            assert_string_include(err, out, "berhasil disimpan");
            prependError(err, "Perintah BUAT_DRAFT. Gagal menyimpan. ");
        ,err);      

        SUB_TEST(
            char in[] = "isi Draft;HAPUS;"; char* out;
            
            interceptStdIO(in, &out);
            createDraftIO();
            clearStdIO();

            assert_string_include(err, out, "berhasil dihapus");
            prependError(err, "Perintah BUAT_DRAFT. Gagal menghapus. ");
        ,err);

        SUB_TEST(
            char in[] = "isi Draft;TERBIT;"; char* out;
            
            interceptStdIO(in, &out);
            createDraftIO();
            clearStdIO();

            assert_string_include(err, out, "kicauan telah diterbitkan");
            prependError(err, "Perintah BUAT_DRAFT. Gagal menerbitkan. ");
        ,err);

        cleanup();
    , err);
    
    DEFINE_TEST("Lihat Draft", 
        setup();
        char err[MAX_ERROR] = "\0";
        UserId id = createUser("ciko", "");
        loggedUser = getUser(id);

        SUB_TEST( 
            char in[] = ""; char* out;

            interceptStdIO(in, &out);
            displayDraftIO();
            clearStdIO();

            assert_string_include(err, out, "belum memiliki draf");
            prependError(err, "Perintah LIHAT_DRAF. Gagal tidak ada draf. ");
        ,err);

        createDraft(id,"isi Draft");

        SUB_TEST(
            char in[] = "KEMBALI;"; char* out;

            interceptStdIO(in, &out);
            displayDraftIO();
            clearStdIO();

            assert_string_include(err, out, "draf terakhir");
            prependError(err, "Perintah LIHAT_DRAF. Gagal menampilkan draf. ");
        ,err);        
        
        SUB_TEST(
            char in[] = "HAPUS;"; char* out;

            interceptStdIO(in, &out);
            displayDraftIO();
            clearStdIO();

            assert_string_include(err, out, "berhasil dihapus");
            prependError(err, "Perintah LIHAT_DRAF. Gagal menghapus draf. ");
        ,err);      

        createDraft(id,"isi Draft");

        SUB_TEST(
            char in[] = "TERBIT;"; char* out;
            
            interceptStdIO(in, &out);
            displayDraftIO();
            clearStdIO();

            assert_string_include(err, out, "kicauan telah diterbitkan");
            prependError(err, "Perintah LIHAT_DRAF. Gagal menerbitkan draf. ");
        ,err);

        createDraft(id,"isi Draft");

        SUB_TEST(
            char in[] = "UBAH; isi baru Draft;SIMPAN;"; char* out;
            
            interceptStdIO(in, &out);
            displayDraftIO();
            clearStdIO();

            assert_string_include(err, out, "Masukkan draf baru:");
            prependError(err, "Perintah LIHAT_DRAF. Gagal mengubah draf. ");
        ,err);      

        cleanup();
    , err);

    DEFINE_TEST("draftToConfig", 
        setup();
        char err[MAX_ERROR] = "\0";
        
        UserId id1 = createUser("ciko", "");
        UserId id2 = createUser("afif", "");
        loggedUser = getUser(id1);
        createDraft(id1, "draft ciko 1");
        createDraft(id1, "draft ciko 2");
        createDraft(id1, "draft ciko 3");
        createDraft(id2, "draft afif 1");
        createDraft(id2, "draft afif 2");

        char in[] = ""; char* out;

        interceptStdIO(in, &out);
        draftToConfig();
        clearStdIO();
        
        assert_string_include(err, out, "draft afif 1");
        prependError(err, "Perintah draftToConfig gagal");
        cleanup();
    , err);
}