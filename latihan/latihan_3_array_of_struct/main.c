#include <stdio.h>
#include <stdlib.h>

int numMahasiswa, i;
struct mahasiswa {
        int nim;
        char nama[80];
        int kehadiran;
    };


int main()
{
    printf("Selamat datang di program cek persentase kehadiran mahasiswa!\n");
    printf("Program ini dapat menerima input 8 digit NIM, \n80 karakter dalam 1 kata nama, dan integer persentase kehadiran.\n");
    printf("Program kemudian akan menampilkan NIM dan nama \ndari mahasiswa yang memiliki kehadiran kurang dari 80%%.\n\n");

    printf("Masukan jumlah mahasiswa: ");
    scanf("%d",&numMahasiswa);
    printf("\n");

    struct mahasiswa kelas[numMahasiswa];

    for (i=0;i<numMahasiswa;i++){
            printf("Mahasiswa ke-%d\n", i+1);
            printf("Masukkan NIM: ");
            scanf("%d",&kelas[i].nim);
            printf("Masukkan nama: ");
            scanf("%s",&kelas[i].nama);
            printf("Masukkan persentase kehadiran: ");
            scanf("%d",&kelas[i].kehadiran);
            printf("\n");
    }

    printf("Mahasiswa yang memiliki kehadiran kurang dari 80%:\n");
    printf("      NIM | Nama\n");
    for (i=0;i<numMahasiswa;i++){
        if (kelas[i].kehadiran<80){
            printf(" %d | %s\n", kelas[i].nim, kelas[i].nama);
        }
    }
}
