/*EL2008 Pemecahan Masalah dengan C 2021/2022
*Hari dan Tanggal : Kamis, 17 Maret 2022
*Nama (NIM)       : Eraraya Morenzo Muten (18320003)
*Nama File        : binary_operation.c
*Deskripsi        : Program menerima NIM kemudian melakukan
*					berbagai operasi terhadap bilangan
*					biner dari NIM.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void decToBin(int dec, int* bin, int len){
	// Menggunakan division method
	int remain, i = 1, j = len-1;

	while (dec != 0) {
		remain = dec % 2;
		dec /= 2;
		bin[j] = remain;
		 j -= 1;
	}
	
	return;
}

int binToDec(int bin){
	// Menggunakan basis 10
	int dec = 0;
	int remain, i = 0;
	
	while (bin != 0) {
		remain = bin % 10;
		bin /= 10;
		dec += remain * pow(2, i);
		++i;
	}
	
	return dec;
}

int matrixToInt(int* matrix){
	// Mengubah bilangan biner bentuk matriks
	// menjadi bentuk integer
	int bin = 0;
	int i;
	
	for(i=0; i<8; ++i){
		bin += matrix[i] * pow(10, 7-i);
	}
	
	return bin;
}

int binToHex(int bin){
	// Menggunakan basis 16 dan
	// format hexadecimal di C
	int hex = 0;
	int remain, i = 1;
	
	while (bin != 0){
      remain = bin % 10;
      hex = hex + remain * i;
      i = i * 2;
      bin = bin / 10;
   }
	
	return hex;
}

int binToSigned(int* bin){
	int sig = 0;
	int i;
	
	for(i=1; i<8; ++i){
		sig += bin[i] * pow(10, 7-i);
	}
	
	if(bin[0] == 1){
		return -1*binToDec(sig);
	} else if(bin[0] == 0){
		return binToDec(sig);
	}
}

void printHasil(int* hasil, int i){
	printf("Operasi %d: \n", i);
	printf("Binary: ");
	for(i=0; i<8; ++i){
		printf("%d", hasil[i]);
	}
	printf("\n");
	printf("Hexadecimal: %X\n", binToHex(matrixToInt(hasil)));
	printf("Unsigned: %d\n", binToDec(matrixToInt(hasil)));
	printf("Signed: %d\n", binToSigned(hasil));
	printf("\n");
	
	return;
}

int main()
{
    char nim[8+1] = "";
	char nimPart[5+1] = "";
	int i;
	int AFull[17];
	int A;
	int hasil[8];
	int y[8];
	
	// Meminta input NIM
	printf("Masukkan NIM (8 digit): ");
	scanf("%s", nim);
	
	// Mengambil digit ke 2, 3, 6, 7, dan 8 NIM
	strncat(nimPart, &nim[1], 1);
	strncat(nimPart, &nim[2], 1);
	strncat(nimPart, &nim[5], 1);
	strncat(nimPart, &nim[6], 1);
	strncat(nimPart, &nim[7], 1);
	
	// Mengisi matriks biner
	for(i=0; i<17+1;++i){
		AFull[i] = -1;
	}
	
	// Mendapatkan binary dari NIM
	decToBin(atoi(nimPart), AFull, 17);
	
	// Mengambil last significant byte dari NIM
	for(i=0; i<8; ++i){
		A += AFull[i+9] * pow(10, 7-i);
	}
	
	// Operasi 1: (A & y) ^ x 
	// x = 1010 0101 = 165
	// y = 1110 1111 = 239
	decToBin(((binToDec(A) & 239) ^ 165), hasil, 8);
	
	// Mencetak Hasil Binary
	printHasil(hasil, 1);

	// Operasi 2: (~(y >> 4) && x) + A 
	// x = 1101 1011 = 219
	// y = 1111 0011 = 243
	decToBin((((~(243 >> 4)) && 219) + binToDec(A)), hasil, 8);
	
	// Mencetak Hasil Binary
	printHasil(hasil, 2);
	
	// Operasi 3: ((x >> 2) | y) * A 
	// x = 0010 1111 = 47
	// y = 1010 0101 = 165
	decToBin((((47 >> 2) | 165) * binToDec(A)), hasil, 8);
	
	// Mencetak Hasil Binary
	printHasil(hasil, 3);
	
    return 0;
}
