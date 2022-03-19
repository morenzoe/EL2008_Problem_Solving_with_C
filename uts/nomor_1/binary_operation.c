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

void decToBin(int dec, int* bin){
	// dengan menggunakan division method
	int remain, i = 1, j = 16;

	while (dec != 0) {
		remain = dec % 2;
		dec /= 2;
		bin[j] = remain;
		printf("%d\n", remain);
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
	int APart[8];
	
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
	printf("nimPart: %s\n", nimPart);
	
	// Mengisi matriks biner
	for(i=0; i<17+1;++i){
		AFull[i] = -1;
	}
	
	decToBin(atoi(nimPart), AFull);
	
	// debugging
	for(i=0; i<17;++i){
		printf("%d", AFull[i]);
	}
	printf("\n");
	
	for(i=0; i<8; ++i){
		APart[i] = AFull[i+9];
	}
	
	// debugging
	for(i=0; i<8;++i){
		printf("%d", APart[i]);
	}
	printf("\n");
	
	/*
	AFull = itoa(A);
	
	for(i=
		strncat(APart, &AFull[i], 1);
	
	printf("A sting: %s\n", A);
	printf("A int: %d\n", atoi(A));
	printf("A&y: %d\n", decToBin((atoi(A) & 165)));	
	printf("hasil: %d\n", decToBin((atoi(A) & 165)^239));
	*/
	
	//printf("A: %lld", A);
	
    return 0;
}
