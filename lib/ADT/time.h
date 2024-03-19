/* File: time.h */
/* Tanggal: 3 September 2022 */
/* Definisi ADT TIME */

#ifndef TIME_H
#define TIME_H

#include "boolean.h"

/* *** Definisi TYPE TIME <HH:MM:SS> *** */
typedef struct { 
	int HH; /* integer [0..23] */
	int MM; /* integer [0..59] */
	int SS; /* integer [0..59] */
} TIME;

/* *** Notasi Akses: selektor TIME *** */
#define Hour(T) (T).HH
#define Minute(T) (T).MM
#define Second(T) (T).SS

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */

/* Mengirim true jika H,M,S dapat membentuk T yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
boolean IsTIMEValid (int H, int M, int S);

/* *** Konstruktor: Membentuk sebuah TIME dari komponen-komponennya *** */

/* Membentuk sebuah TIME dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk TIME */
void CreateTime (TIME * T, int HH, int MM, int SS);

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */

/* I.S. : T tidak terdefinisi */
/* F.S. : T terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk T */
/* yang valid. Tidak mungkin menghasilkan T yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika TIME tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh: 
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk TIME <1,3,4> */
void BacaTIME (TIME * T);
   
/* I.S. : T sembarang */
/* F.S. : Nilai T ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen T ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/ 
void TulisTIME (TIME T);

/* ***************************************************************** */
/* KELOMPOK KONVERSI TERHADAP TYPE                                   */
/* ***************************************************************** */

/* Diberikan sebuah TIME, mengkonversi menjadi jumlah detik dari pukul 0:0:0 */
/* Rumus : detik = 3600*HH + 60*MM + SS */
/* Nilai maksimum = 3600*23+59*60+59 */
long TIMEToDetik (TIME T);

/* Mengirim  konversi detik ke TIME */
/* Catatan: Jika N >= 86400, maka harus dikonversi dulu menjadi jumlah detik yang 
   mewakili jumlah detik yang mungkin dalam 1 hari, yaitu dengan rumus: 
   N1 = N mod 86400, baru N1 dikonversi menjadi TIME */
TIME DetikToTIME (long N); 

/* ***************************************************************** */
/* KELOMPOK OPERASI TERHADAP TYPE                                    */
/* ***************************************************************** */
/* *** Kelompok Operator Relational *** */

/* Mengirimkan true jika T1=T2, false jika tidak */
boolean TEQ (TIME T1, TIME T2);

/* Mengirimkan true jika T1 tidak sama dengan T2 */
boolean TNEQ (TIME T1, TIME T2);

/* Mengirimkan true jika T1<T2, false jika tidak */
boolean TLT (TIME T1, TIME T2);

/* Mengirimkan true jika T1>T2, false jika tidak */
boolean TGT (TIME T1, TIME T2);

/* *** Operator aritmatika TIME *** */

/* Mengirim 1 detik setelah T dalam bentuk TIME */
TIME NextDetik (TIME T);

/* Mengirim N detik setelah T dalam bentuk TIME */
TIME NextNDetik (TIME T, int N);

/* Mengirim 1 detik sebelum T dalam bentuk TIME */
TIME PrevDetik (TIME T);

/* Mengirim N detik sebelum T dalam bentuk TIME */
TIME PrevNDetik (TIME T, int N);

/* *** Kelompok Operator Aritmetika *** */

/* Mengirim TAkh-TAw dlm Detik, dengan kalkulasi */
/* Jika TAw > TAkh, maka TAkh adalah 1 hari setelah TAw */
long Durasi (TIME TAw, TIME TAkh);

#endif