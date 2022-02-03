#include <stdio.h>

#define fileName_size 50
#define val_size 5

int main () {
    char fileName [fileName_size];
    unsigned char val[val_size];
    FILE *pfile;

    printf("Program ini dapat menentukan jenis file PDF atau JPG berdasarkan file signatures, bukan nama file.\n");
    printf("File harus ada di directory yang sama dengan program ini.\n");
    printf("Masukkan nama file lengkap (bersama extension) yang ingin ditentukan jenisnya.\n");
    printf("Contoh: example.pdf\n\n");
    printf("Ketikkan nama file: ");
    scanf("%s", fileName);
    printf("\n");

    pfile = fopen(fileName,"r");
    if (pfile != NULL){
        fread(val, val_size, 1, pfile); // value, value size, object, input stream
        printf("File signatures: %X %X %X %X %X\n", val[0],val[1],val[2],val[3],val[4]);

        if ((val[0]==0x25)&&(val[1]==0x50)&&(val[2]==0x44)&&(val[3]==0x46)&&(val[4]==0x2D)) {
            printf("File %s adalah file PDF.\n", fileName);
        } else if ((val[0]==0xFF)&&(val[1]==0xD8)&&(val[2]==0xFF)) {
            printf("File %s adalah file JPG.\n", fileName);
        } else {
            printf("Bukan file JPG maupun PDF.\n");
        }

    } else {
        printf("File tidak ditemukan di directory program ini.\n");
    }

    fclose(pfile);

    return 0;
}
