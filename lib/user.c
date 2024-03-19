#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include "relation.h"
#include "string.h"
#include "get_string.h"
#include "pcolor.h"
#include "config.h"

User* loggedUser;
int userCount = 0;
static User* users[MAX_USER];

int isFull(){
    return userCount == MAX_USER;
}

UserId createUser(char* name, char* pass){
    int newId = userCount;
    ++userCount;

    User* user = malloc(sizeof(User));
    if(!user) return -1;

    user->id = newId;
    string_copy(name, user->name, MAX_NAME);
    string_copy(pass, user->pass, MAX_PASS);
    string_copy("", user->bio, MAX_BIO);
    string_copy("", user->phone, MAX_PHONE);
    string_copy("", user->weton, MAX_WETON);
    users[newId] = user;

    string_copy("RRRRRRRRRRRRRRRRRRRRRRRRR", user->pictureColor,MAX_COLOR);
    string_copy("*************************", user->pictureChar,MAX_PICTURE);
    return newId;
}

User* getUser(UserId id){
    if(id == -1) return NULL;
    return users[id];
}

UserId getUserIdByName(char* name){
    for(int i = 0; i < userCount; ++i){
        User* user = getUser(i);
        if(!user) continue;
        if(string_compare(name, user->name) == 0) return i;
    }
    return -1;
}

boolean checkPhoneValid(char* phone){
    int i = 0;
    while (phone[i] != '\0'){
        if (phone[i] < '0' || phone[i] > '9'){
            return false;
        }
        i++;
    }

    return true;
}

boolean checkWetonValid(char* weton){
    int i = 0;
    char pahingValid[MAX_WETON] = "pahing", kliwonValid[MAX_WETON] = "kliwon";
    char wageValid[MAX_WETON] = "wage", ponValid[MAX_WETON] = "pon";
    char legiValid[MAX_WETON] = "legi";


    if (weton[0] == '\0'){
        return true;
    }

    while (weton[i] != '\0'){
        if (weton[i] < 'a'){
            weton[i] += 32;
        }
        i++;
    }

    if (
        string_length(weton) == 0 ||
        string_compare(pahingValid,weton) == 0 ||
        string_compare(kliwonValid,weton) == 0 ||
        string_compare(wageValid,weton) == 0 ||
        string_compare(ponValid,weton) == 0 ||
        string_compare(legiValid,weton) == 0
    ){
        return true;
    } else {
        return false;
    }
}

void signUp(){
    if(loggedUser){
        printf("Anda telah login\n");
        return;
    }

    if(isFull()){
        printf("User telah penuh\n");
        return;
    }

    char tmpName[MAX_NAME];
    do{
        printf("Masukkan nama: \n");
        get_string(tmpName, MAX_NAME);
    } while(
        (getUserIdByName(tmpName) != -1) && 
        (printf("Nama telah dipakai\n") || true)
    );

    char tmpPass[MAX_PASS];
    printf("Masukkan kata sandi: \n");
    get_string(tmpPass, MAX_PASS);
    printf("Pengguna berhasil terdaftar.\nMasuk untuk menikmati fitur-fitur BurBir.\n");
}

void signIn(){
    if(loggedUser){
        printf("Anda telah login\n");
        return;
    }

    char tmpName[MAX_NAME];
    User *user;

    while(true){
        printf("Masukkan nama: \n");
        get_string(tmpName, MAX_NAME);
        user = getUser(getUserIdByName(tmpName));

        if(!user){
            printf("User tidak ditemukan\n");
            continue;
        }
        break;
    }

    while(true){
        char tmpPass[MAX_PASS];
        printf("Masukkan pass: \n");
        get_string(tmpPass, MAX_PASS);

        if(string_compare(tmpPass, user->pass) != 0){
            printf("Password anda salah\n");
            continue;
        }
        break;
    }

    loggedUser = user;
    printf("Anda telah berhasil masuk dengan nama pengguna \"%s\". Mari menjelajahi BurBir bersama Ande-Ande Lumut!\n", loggedUser->name);
}

void signOut(){
    if(!loggedUser){
        printf("Anda belum login!\n");
        return;
    }

    loggedUser = NULL;
    printf("Anda berhasil logout.\n");
}

// TODO: Clear relation after delete
void deleteUser(UserId id){
    free(users[id]);
    users[id] = NULL;
}

void displayPhotoProfileIO(UserId id){
    User* user = getUser(id);
    for (int i = 0; i < PICTURE_LENGTH; i++){
        void (*printer) (char) = NULL;

        switch (user->pictureColor[i]){
            case 'R':
                printer = print_red;
                break;
            case 'G':
                printer = print_green;
                break;
            case 'B':
                printer = print_blue;
                break;
        }

        if(printer != NULL) printer(user->pictureChar[i]);
        else printf("%c", user->pictureChar[i]);

        if(i % 5 == 4) printf("\n");
    }
}

void changeProfileIO(){
    char tmpBio[MAX_BIO], tmpPhone[MAX_PHONE],tmpWeton[MAX_WETON];
    User* user = getUser(loggedUser->id);

    displayProfileIO(user->name);
    printf("Masukkan Bio Akun:\n");
    get_string(tmpBio,MAX_BIO);
    if (string_length(tmpBio) != 0){
        string_copy(tmpBio,user->bio,MAX_BIO);
    }

    do {    
        printf("Masukkan No HP:\n");
        get_string(tmpPhone,MAX_PHONE);

        if (string_length(tmpPhone) != 0){
            if (!checkPhoneValid(tmpPhone)){
                printf("No HP tidak valid. Masukkan lagi yuk!\n");
            } else {
                string_copy(tmpPhone,user->phone,MAX_PHONE);
            }
        }
    } while(!checkPhoneValid(tmpPhone));
    
    do {
        printf("Masukkan Weton:\n");
        get_string(tmpWeton,MAX_WETON);
        
        if (!checkWetonValid(tmpWeton)){
            printf("Weton anda tidak valid.\n");
        } else {
            tmpWeton[0] -= 32;
            string_copy(tmpWeton,user->weton,MAX_WETON);
            tmpWeton[0] += 32;
        }
    } while (!checkWetonValid(tmpWeton));

}

void displayProfileIO(char* name){
    if(loggedUser == NULL){
        printf("Anda belum login\n");
        return;
    }

    UserId userId = getUserIdByName(name);

    if(userId == -1) {
        printf("Profil tidak ditemukan\n");
        return;
    }

    User* user = getUser(getUserIdByName(name));
    
    printf("| Nama: %s\n", user->name);
    printf("| Bio Akun: %s\n", user->bio);
    printf("| No HP: %s\n", user->phone);
    printf("| Weton: %s\n\n", user->weton);
    printf("Foto profil akun %s\n", user->name);
    displayPhotoProfileIO(user->id);
    printf("\n");
}

void changeAccountTypeIO(){
    char input[MAX_BIO];
    User* user = getUser(loggedUser->id);
    if (user->type == PUBLIC_USER){
        printf("Saat ini, akun Anda adalah akun Publik.\n"); 
        printf("Ingin mengubah ke akun Privat?\n");
        do {
            printf("(YA/TIDAK) ");
            get_string(input,MAX_BIO);
            if (string_compare(input,"YA") == 0){
                user->type = PRIVATE_USER;
                printf("Akun anda sudah diubah menjadi akun Privat.\n");
            } else if (string_compare(input,"TIDAK") != 0 && string_compare(input,"YA") != 0){
                printf("Input Salah!\n");
            }
        } while (string_compare(input,"YA") != 0 && string_compare(input,"TIDAK") != 0);
    } else if (user->type == PRIVATE_USER){
        printf("Saat ini, akun Anda adalah akun Private.\n"); 
        printf("Ingin mengubah ke akun Public?\n");
        do {
            printf("(YA/TIDAK) ");
            get_string(input,MAX_BIO);
            if (string_compare(input,"YA") == 0){
                user->type = PUBLIC_USER;
                printf("Akun anda sudah diubah menjadi akun Public.\n");
            } else if (string_compare(input,"TIDAK") != 0 && string_compare(input,"YA") != 0){
                printf("Input Salah!\n");
            }
        } while (string_compare(input,"YA") != 0 && string_compare(input,"TIDAK") != 0);
    }
}

void changePhotoProfileIO(){
    char inputColor[MAX_COLOR], inputChar[MAX_PICTURE];
    User *user = getUser(loggedUser->id);
    printf("Foto profil Anda saat ini adalah\n");
    displayPhotoProfileIO(user->id);
    printf("\nMasukkan foto profil yang baru\n");

    char buff[2];
    for(int i = 0; i < PICTURE_LENGTH; ++i){
        get_word(buff, 2);
        inputColor[i] = buff[0];
        get_word(buff, 2);
        inputChar[i] = buff[0];
    }

    string_copy(inputColor, user->pictureColor, MAX_COLOR);
    string_copy(inputChar, user->pictureChar, MAX_PICTURE);

    printf("\nFoto profil anda sudah berhasil diganti!\n");
}

void userCleanupRoutine(){
    for(int i = 0; i < userCount; ++i){
        free(users[i]);
        users[i] = NULL;
    }
}

void userToConfig(){
    printf("%d\n", userCount);

    for (int i = 0; i < userCount; ++i){
        User *user = getUser(i);
        printf("%s\n", user->name);
        printf("%s\n", user->pass);
        printf("%s\n", user->bio);

        printf("%s\n", user->phone);
        printf("%s\n", user->weton);
        printf("%s\n", user->type == PUBLIC_USER ? "Publik" : "Privat");

        for(int i = 0; i < PICTURE_LENGTH; ++i){
            printf("%c %c ", user->pictureColor[i], user->pictureChar[i]);
            if(i % 5 == 4) printf("\n");
        }
    }
}

void configToUser(){
    ignore(" \n");
    int count = readInt();
    nextLine();

    for(int i = 0; i < count; ++i){
        char name[MAX_NAME];
        readTill(name, "\n", MAX_NAME); nextLine();

        char pass[MAX_PASS];
        readTill(pass, "\n", MAX_PASS); nextLine();

        UserId id = createUser(name, pass);
        User *user = getUser(id);

        char bio[MAX_BIO];
        readTill(user->bio, "\n", MAX_PASS); nextLine();

        char phone[MAX_PHONE];
        readTill(user->phone, "\n", MAX_PHONE); nextLine();

        char weton[MAX_WETON];
        readTill(user->weton, "\n", MAX_WETON); nextLine();

        char accountType[100];
        readTill(accountType, "\n", 100); nextLine();
        if(string_compare(accountType, "Privat") == 0){
            user->type = PRIVATE_USER;
        } else {
            user->type = PUBLIC_USER;
        };

        char picture[MAX_PICTURE];
        char color[MAX_COLOR];

        for(int i = 0; i < PICTURE_LENGTH; ++i){
            ignore(" \n");
            readTill(&(color[i]), " \n", 2);
            ignore(" \n");
            readTill(&(picture[i]), " \n", 2);
        }
        nextLine();

        string_copy(picture, user->pictureChar, MAX_PICTURE);
        string_copy(color, user->pictureColor, MAX_COLOR);
    }
}