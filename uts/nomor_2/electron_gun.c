/*EL2008 Pemecahan Masalah dengan C 2021/2022
*Hari dan Tanggal : Kamis, 17 Maret 2022
*Nama (NIM)       : Eraraya Morenzo Muten (18320003)
*Nama File        : binary_operation.c
*Deskripsi        : Program menerima data tegangan dalam juta
*					dan menghitung massa relativistik serta
*					kecepatan elektron dengan suatu rumus.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxLen 255
#include <math.h>

int main(){
	int j, i = 0;
	float volt[maxLen];
	float mass[maxLen];
	float speed[maxLen];
	const float e = 1.602;
	const float m_o = 9.109;
	const float c = 2.9979;
	
	// Membaca data dari file
	FILE *file = fopen("data.txt", "r");
	char row[maxLen];
	char* token;
	
	// Parsing setiap baris file
	while(fgets(row, maxLen, file)){
		token = strtok(row, "\n");
		volt[i] = atof(token);
		++i;
	}
	
	// Melakukan perhitungan
	// V*e = m*c^2 - m_o*c^2
	// m = (v*e)/c^2 + m_o
	for(j=0; j<i; ++j){
		mass[j] = ((volt[j] * e)/pow(c,2)) * pow(10,-2) + m_o;
		speed[j] = c * sqrt(1-pow(mass[j]/m_o,-2));
		//printf("Tegangan: %f*10^6 V\tMassa: %f*10^-31 kg\tKecepatan: %f*10^8 m/s\n", volt[j], mass[j], speed[j]);
		printf("%f\n", (speed[j]/c));
	}
	
	return 0;
}