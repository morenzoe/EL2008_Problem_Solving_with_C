/*EL2008 Pemecahan Masalah dengan C 2021/2022
*Hari dan Tanggal : Kamis, 17 Maret 2022
*Nama (NIM)       : Eraraya Morenzo Muten (18320003)
*Nama File        : binary_operation.c
*Deskripsi        : Program menerima matriks sebesar m kali n,
*					melakukan transpos konjugat, memeriksa sifat
*					matriks, dan menampilkan sifat tersebut.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void decToBin(int dec, int* bin, int len){
	// dengan menggunakan division method
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

/*
const char* binToHex(int bin){
	char hex[2+1];
	
	
	return hex;
}

int binToSig(int bin){
	int sig;
	
	
	return sig;
}
*/

int main()
{
    char nim[8+1] = "";
	char nimPart[5+1] = "";
	int i;
	int AFull[17];
	int A;
	int hasil[8];
	int y[8];
	
	//signed x, y;
	
	// Meminta input NIM
	printf("Masukkan NIM (8 digit): ");
	scanf("%s", nim);
	
	// Mengambil digit ke 2, 3, 6, 7, dan 8 NIM
	strncat(nimPart, &nim[1], 1);
	strncat(nimPart, &nim[2], 1);
	strncat(nimPart, &nim[5], 1);
	strncat(nimPart, &nim[6], 1);
	strncat(nimPart, &nim[7], 1);
	
	// debugging
	// printf("nimPart: %s\n", nimPart);
	
	// Mengisi matriks biner
	for(i=0; i<17+1;++i){
		AFull[i] = -1;
	}
	
	// Mendapatkan binary dari NIM
	decToBin(atoi(nimPart), AFull, 17);
	
	// debugging
	/*
	for(i=0; i<17;++i){
		printf("%d", AFull[i]);
	}
	printf("\n");
	*/
	
	// Mengambil last significant byte dari NIM
	for(i=0; i<8; ++i){
		A += AFull[i+9] * pow(10, 7-i);
	}
	
	// debugging
	//printf("%d", A);
	
	// Operasi 1: (A & y) ^ x 
	// x = 1010 0101 = 165
	// y = 1110 1111 = 239
	decToBin(((binToDec(A) & 239) ^ 165), hasil, 8);
	
	// Mencetak Hasil Binary
	printf("1: ");
	for(i=0; i<8;++i){
		printf("%d", hasil[i]);
	}
	printf("\n");
	
    return 0;
}
