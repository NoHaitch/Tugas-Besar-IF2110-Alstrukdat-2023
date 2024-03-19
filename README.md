<!-- Back to Top Link-->
<a name="readme-top"></a>


<br />
<div align="center">
  <h1 align="center">Tugas Besar IF2110 Algoritma & Struktur Data ITB</h1>

  <p align="center">
    <h3> BurBir (Burung Biru)</h3>
    <h4> Program simulasi Social Media berbasis CLI (command-line interface) dalam bahasa C </h4>
    <br />
    <a href="https://github.com/mrsuiii/Tubes-Alstrukdat/issues">Report Bug</a>
    ·
    <a href="https://github.com/mrsuiii/Tubes-Alstrukdat/issues">Request Feature</a>
<br>
<br>

[![MIT License][license-shield]][license-url]

  </p>
</div>

<!-- CONTRIBUTOR -->
<div align="center" id="contributor">
  <strong>
    <h3>Dibuat oleh Kelompok K02 - C</h3>
    <table align="center">
      <tr>
        <td style="text-align: center;">NIM</td>
        <td style="text-align: center;">Nama</td>
      </tr>
      <tr>
        <td style="text-align: center;">13522079</td>
        <td style="text-align: center;">Emery Fathan Zwageri</td>
      </tr>
      <tr>
        <td style="text-align: center;">13522086</td>
        <td style="text-align: center;">Muhammad Atpur Rafif</td>
      </tr>
      <tr>
        <td style="text-align: center;">13522091</td>
        <td style="text-align: center;">Raden Francisco Trianto Bratadiningrat</td>
      </tr>
      <tr>
        <td style="text-align: center;">13522093</td>
        <td style="text-align: center;">Matthew Vladimir Hutabarat</td>
      </tr>
      <tr>
        <td style="text-align: center;">13522118</td>
        <td style="text-align: center;">Berto Richardo Togatorop</td>
      </tr>
    </table>
  </strong>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#instruction">Instruction</a></li>
        <li>
        <details>
          <summary><a href="#features">Features</a></summary>
          <ol>
            <li><a href="#1-initialization-inisialisasi">Inisialisasi</a></li>
            <li><a href="#2-commands-perintah">Commands</a></li>
            <li><a href="#3-user-pengguna">User</a></li>
            <li><a href="#4-profile-profil">Profile</a></li>
            <li><a href="#5-friend-teman">Friend</a></li>
            <li><a href="#6-friend-request-permintaan-pertemanan">Friend Request</a></li>
            <li><a href="#7-tweet-kicauan">Tweet</a></li>
            <li><a href="#8-reply-balasan">Reply</a></li>
            <li><a href="#9-tweet-draft-draf-kicauan">Tweet Draft</a></li>
            <li><a href="#10-thread-utas">Thread</a></li>
            <li><a href="#11-save-and-load-simpan-dan-muat">Save & Load</a></li>
          <ol>
        </details>
        </li>
      </ul>
    </li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#special-thanks">Special Thanks</a></li>
  </ol>
</details>

## External Links

- [Link Drive Pusat](https://drive.google.com/drive/folders/1D6GTJ9Fq_8P79lhSrxI7DJDdBFtoojR0)
- [Link Spesifikasi](https://docs.google.com/document/d/1yy0SLsXEE0e-ZBxMSrd0Gz9AOSWqJw1trtTqDjeyfsk/edit)
- [Link Pedoman](https://docs.google.com/document/d/1vnoqQK18ECL8PEAkYbjM-9g1MRGTI7hOLv6GKHlGnuc/edit)
- [Link Q&A](https://docs.google.com/spreadsheets/d/1S8pEorkaomHjgonWgp44o_AvLxFdENWVEXE3NrO2P_o/edit#gid=1259903967)
- [Link Data Kelompok](https://docs.google.com/spreadsheets/d/1Q_TMzWjDSr5ZXc-hv2KoGYySJbb_LyA7Z5_KCdIE6ko/edit#gid=1406958191)
- [Link Laporan](https://docs.google.com/document/d/1fNNBXmFtielWkc9g6uuZ2GXbgkTjwqqK/edit)

<!-- ABOUT THE PROJECT -->
## About The Project

Untuk Melatih Penggunaan Struktur-Struktur Data berbasis ADT (Abstact Data Types) yang sudah dipelajari dalam mata kuliah IF2110 Algoritma & Struktur Data ITB, maka dibuatlah tugas besar ini.  

<p align="center">
Untuk Lebih dalam mengenal Tugas sekaligus Projek ini, Anda dapat melihat spesifikasi tugas pada link berikut :
<br>
<a href="https://docs.google.com/document/d/1yy0SLsXEE0e-ZBxMSrd0Gz9AOSWqJw1trtTqDjeyfsk/edit"> <Strong>Spesifikasi Tugas Besar IF2110 Algoritma & Struktur Data 2023/2024</Strong>
</a>
</p>

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## Getting Started

### Prerequisites

Untuk melakukan kompilasi dan penggunaan Makefile diperlukan 

* Makefile 
  ```sh
  # untuk Linux Ubuntu
  sudo apt install make
  ```
* GCC
  ```sh
  # untuk Linux Ubuntu
  sudo apt install gcc
  ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Installation

_Di bawah ini adalah contoh installasi dengan asumsi pengguna menggunakan Linux Ubuntu_

1. Clone the repo
   ```sh
   git clone https://github.com/mrsuiii/Tubes-Alstrukdat
   ```
2. Install GCC
   ```sh
   sudo apt install gcc
   ```
3. Install Make
   ```sh
   sudo apt install make
   ```
4. Use Makefile to run the program
   ```sh
   make all
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- INSTURCTION -->
## Instruction
Instruksi-instruksi yang dapat dilakukan :

`make build` : To build from source to binary into bin/main  
`make all` : Run binary directly after building   
`make clean` : Remove all build generated files  
`make ADT.test` : Running test for ADT test file, for example ( `make time.test` )  
`make test.all` : Running all test  


<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- FEATURES -->
## Features

### 1. Initialization (Inisialisasi)

Ketika Program dijalankan dilakukan Inisialisasi Program seperti [memuat](#11-save--load-simpan-dan-muat) konfigurasi dan output pembuka program.  

### 2. Commands (Perintah)

Membaca Perintah dan mengeksekusi memanggil fungsi-fungsi dari ADT.

### 3. User (Pengguna)

Program dapat membuat seorang pengguna yang terdiri dari Nama dan Password Akun.  
Daftar Perintah :
- `DAFTAR`: Menambahkan pengguna.  
- `MASUK`: Login dengan menggunakan nama dan kata sandi.  
- `KELUAR`: Log out dan kembali ke menu utama.


### 4. Profile (Profil)

Seorang Pengguna memiliki profil yang terdiri dari bio, nomor hp, weton, jenis akun, dan foto profil.  
Daftar Perintah : 
- `GANTI_PROFIL`: Mengubah profil pengguna yang terdiri dari nama, bio, no. HP, weton.  
- `LIHAT_PROFIL [NAMA]`: Melihat profil lengkap dari user dengan nama [NAMA].  
- `ATUR_JENIS_AKUN`: Mengubah akun menjadi akun privat dari publik dan sebaliknya.   
- `UBAH_FOTO_PROFIL`: Mengubah foto profil dari pengguna yang sedang login. Foto profil direpresentasikan dengan matrix. 

### 5. Friend (Teman)

Dapat dijalinkan Pertemanan antara Pengguna.  
Daftar Perintah :  
- `DAFTAR_TEMAN`: Menampilkan banyak teman dan daftar teman dari pengguna saat ini.  
- `HAPUS_TEMAN`: Menghapus salah satu teman dari pengguna saat ini.  

### 6. Friend Request (Permintaan Pertemanan)

Seorang Pengguna dapat melakukan permintaan pertemanan kepada Pengguna lain.  
Daftar Perintah :
- `TAMBAH_TEMAN`: Mengirimkan perimintaan pertemanan ke pengguna lain.  
- `DAFTAR_PERMINTAAN_PERTEMANAN`: Menampilkan daftar permintaan pertemanan yang diajukan ke pengguna sekarang.  
- `SETUJUI_PERTEMANAN`: Menyetujui permintaan pertemanan yang diajukan ke user sekarang.  

### 7. Tweet (Kicauan)

Membuat Kicauan atau tweet yang memiliki isi, pembuat, waktu, dan jumlah like.  
Daftar Perintah :  
- `KICAU`: Menerbitkan kicauan baru.  
- `KICAUAN`: Menampilkan semua kicauan yang telah dibuat oleh user sekarang.  
- `SUKA_KICAUAN [IDKicau]`: Menyukai kicauan dengan id = IDKicau.  
- `UBAH_KICAUAN [IDKicau]`: Mengubah isi kicauan dari kicauan dengan id = IDKicau.  


### 8. Reply (Balasan)

Membuat balasan terhadap suatu kicauan atau balasan lain.  
Daftar Perintah :
- `BALAS [IDKicau] [IDBalasan]`: Menambah balasan pada balasan dengan id = IDBalasan pada kicauan dengan id = IDKicau.  
- `BALASAN [IDKicau]`: Melihat daftar balasan pada kicau. Jika terdapat balasan dalam balasan maka tampilkan balasan yang di dalam lebih ke kanan. Jika akun pengguna diprivat, nama, waktu, dan balasan dari pengguna diubah menjadi PRIVAT.  
- `HAPUS_BALASAN [IDKicau] [IDBalasan]`: Menghapus balasan pada balasan dengan id = IDBalasan pada kicauan dengan id = IDKicau.


### 9. Tweet Draft (Draf Kicauan)

Membuat Draf Kicauan yang dapat disimpan, diubah, dihapus, dan diterbitkan menjadi Kicauan.  
Daftar Perintah : 
- `BUAT_DRAFT`: Menambahkan sebuah draft kicauan. Setelah itu, draft dapat dihapus, disimpan, atau diterbitkan.   
- `LIHAT_DRAF`: Melihat draf terakhir yang dibuat.  

### 10. Thread (Utas)

Suatu Kicauan mungkin tidak cukup untuk menulis suatu pesan. Maka suatu kicauan dapat dibuat menjadi utas.  
Daftar Perintah :
- `UTAS [IDKicau]`: Membuat sebuah utas baru dengan kicauan pertamanya adalah kicauan dengan id = IDKicau.  
- `SAMBUNG_UTAS [IDUtas] [index]`: Menambah sebuah kicauan baru dalam sebuah utas dengan id = IDUtas pada posisi index.  
- `HAPUS_UTAS [IDUtas] [index]`: Menghapus kicauan dalam sebuah utas dengan id = IDUtas. Kicauan utas yang dihapus sesuai dengan index.   
- `CETAK_UTAS [IDUtas]`: Mencetak keseluruhan kicauan dalam sebuah utas dengan id = IDUtas termasuk kicauan utama.  

### 11. Save & Load (Simpan dan Muat)

State Akhir program dapat disimpan pada file konfigurasi. Konfigurasi dapat dimuat saat program dimulai.    
Daftar Perintah :
- `SIMPAN`: Menyimpan konfigurasi pengguna, kicauan, balasan, draft, dan utas ke folder yang akan dipilih kemudian.  
- `MUAT`: Memuat setiap konfigurasi dari folder yang akan dipilih kemudian.  

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTRIBUTING -->
## Contributing

Jika Anda ingin berkontribusi atau melanjutkan perkembangan program, silahkan fork repository ini dan gunakan branch fitur.  

Permintaan Pull __sangat diperbolehkan dan diterima dengan hangat__.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## Licensing

The code in this project is licensed under MIT license.  
Code dalam projek ini berada di bawah lisensi MIT.

## Special Thanks
- [Best-README-Template](https://github.com/othneildrew/Best-README-Template) by othneildrew

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<br>
<h3 align="center"> THANK YOU! </h3>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[issues-url]: https://github.com/mrsuiii/Tubes-Alstrukdat/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/othneildrew/Best-README-Template/blob/master/LICENSE.txt
