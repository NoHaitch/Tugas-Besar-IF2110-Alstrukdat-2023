#include <stdio.h>
#include "lib/get_string.h"
#include "lib/config.h"
#include "lib/routine.h"
#include "lib/user.h"
#include "lib/relation.h"
#include "lib/tweet.h"
#include "lib/string.h"
#include "lib/draft.h"
#include "lib/thread.h"
#include "lib/display.h"
#include "lib/max_heap.h"
#include "lib/kelompokteman.h"
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    setup();

    char basePath[1000], userPath[MAX_PATH], tweetPath[MAX_PATH], replyPath[MAX_PATH], draftPath[MAX_PATH], threadPath[MAX_PATH];
    while(true){
        printf("Masukan path konfigurasi: ");
        get_string(basePath, 1000);

        if(!checkDirectoryExsistence(basePath)){
            printf("Directory tidak ditemukan\n");
            continue;
        }

        char *err = "";

        string_append(basePath, "/pengguna.config", userPath, MAX_PATH);
        if(!checkFileExist(userPath)) err = "pengguna";

        string_append(basePath, "/kicauan.config", tweetPath, MAX_PATH);
        if(!checkFileExist(tweetPath)) err = "kicauan";

        string_append(basePath, "/balasan.config", replyPath, MAX_PATH);
        if(!checkFileExist(replyPath)) err = "balasan";

        string_append(basePath, "/draf.config", draftPath, MAX_PATH);
        if(!checkFileExist(draftPath)) err = "draf";

        string_append(basePath, "/utas.config", threadPath, MAX_PATH);
        if(!checkFileExist(threadPath)) err = "utas";

        if(string_length(err) != 0){
            printf("Konfigurasi %s tidak ditemukan\n", err);
            continue;
        } else {
            printf("Konfigurasi berhasil dimuat\n");
            break;
        }
    }

    startReadFile(userPath);
    configToUser();
    configToRelation();

    startReadFile(tweetPath);
    configToTweet();

    startReadFile(replyPath);
    configToReply();

    startReadFile(draftPath);
    configToDraft();

    startReadFile(threadPath);
    configToThread();

    printLogo();

    while(true){
        printf("> ");

        int argv = 0;
        char argc[4][100];
        currentChar = '\0';
        while(currentChar != GET_STRING_MARK){
            get_word(argc[argv], 100);
            argv += 1;
            if(argv >= 4) continue;
        }

        if(argv == 1 && string_equal(argc[0], "TUTUP_PROGRAM")){
            break;
        } 

        if(argv > 1 && string_length(argc[1]) == 0) argv = 1;

        if (argv > 2 && string_length(argc[2]) == 0) argv = 2;

        // User
        if(argv == 1 && string_equal(argc[0], "DAFTAR")) signUp();
        else if(argv == 1 && string_equal(argc[0], "MASUK")) signIn();
        else if(argv == 1 && string_equal(argc[0], "KELUAR")) signOut();

        // Profile
        else if(argv == 1 && string_equal(argc[0], "GANTI_PROFIL")) changeProfileIO();
        else if(argv == 2 && string_equal(argc[0], "LIHAT_PROFIL")) displayProfileIO(argc[1]);
        else if(argv == 1 && string_equal(argc[0], "ATUR_JENIS_AKUN")) changeAccountTypeIO();
        else if(argv == 1 && string_equal(argc[0], "UBAH_FOTO_PROFIIL")) changePhotoProfileIO();

        // Relation
        else if(argv == 1 && string_equal(argc[0], "TAMBAH_TEMAN")) requestFriendIO();
        else if(argv == 1 && string_equal(argc[0], "DAFTAR_TAMBAH_TEMAN")) displayRequestedFriendIO();
        else if(argv == 1 && string_equal(argc[0], "SETUJUI_PERTEMANAN")) acceptFriendIO();

        // Tweet
        else if(argv == 1 && string_equal(argc[0], "KICAU")) createTweetIO();
        else if(argv == 1 && string_equal(argc[0], "KICAUAN")) displayAllTweetIO();
        else if(argv == 2 && string_equal(argc[0], "SUKA_KICAUAN")) likeTweetIO(argc[1]);
        else if(argv == 2 && string_equal(argc[0], "UBAH_KICAUAN")) editTweetIO(argc[1]);

        // Reply
        else if(argv == 3 && string_equal(argc[0], "BALAS")) createReplyIO(argc[1], argc[2]);
        else if(argv == 2 && string_equal(argc[0], "BALASAN")) displayReplyIO(argc[1]);
        else if(argv == 3 && string_equal(argc[0], "HAPUS_BALASAN")) deleteReplyIO(argc[1], argc[2]);

        // Draft
        else if(argv == 1 && string_equal(argc[0], "BUAT_DRAF")) createDraftIO();
        else if(argv == 1 && string_equal(argc[0], "LIHAT_DRAF")) displayDraftIO();

        // Thread
        else if(argv == 2 && string_equal(argc[0], "UTAS")) makeMainThreadIO(argc[1]);
        else if(argv == 3 && string_equal(argc[0], "SAMBUNG_UTAS")) continueThreadAtIO(argc[1], argc[2]);
        else if(argv == 3 && string_equal(argc[0], "HAPUS_TAS")) deleteThreadAtIO(argc[1], argc[2]);
        else if(argv == 2 && string_equal(argc[0], "CETAK_UTAS")) displayThreadSeqIO(argc[1]);

        //bonus
        else if(argv == 1 && string_equal(argc[0], "FYB")) showFYB();
        else if(argv == 1 && string_equal(argc[0], "KELOMPOK_TEMAN")) showFriendGroup();

        // Save
        else if(argv == 1 && string_equal(argc[0], "SIMPAN")) saveIO();
        else {
            printf("Command \"%s%s%s\" dengan %d argumen tidak diketahui\n", GREEN, argc[0], NORMAL, argv - 1);
        }
        
    }

    cleanup();
}