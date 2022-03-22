/*EL2008 Pemecahan Masalah dengan C 2021/2022
*Hari dan Tanggal : Minggu, 20 Maret 2022
*Nama (NIM)       : Eraraya Morenzo Muten (18320003)
*Nama File        : rc_filter.c
*Deskripsi        : Program menerima data tegangan dalam juta
*					dan menghitung massa relativistik serta
*					kecepatan elektron dengan suatu rumus.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main(){
	const int R = 20000;
	const float C = 0.000000183008;
	const int V_in = 5;
	float t = (float) clock()/1000;
	
	printf("Vo tunak ketika mencapai nilai %d V\n", V_in);
	printf("%f",t);
	printf("%f", 1 - exp(-1 * t/(R * C)));
	while (1 - exp(-1 * t/(R * C)) != 1){
        float V_t = (float) V_in * ( 1 - exp(-1 * t / (R * C)));
        printf("Vo transien adalah %.2e V.\n", V_t);
        t = (float) clock()/1000;
    }
	
	return 0;
}