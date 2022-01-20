/*
Eraraya Morenzo Muten
Teknik Biomedis
18320003
*/

#include <stdio.h>
#include <stdlib.h>

int max(int x, int y){
    if (x>y){
        return x;
    } else {
    return y;
    }
}

int min(int x, int y){
    if (x<y){
        return x;
    } else {
    return y;
    }
}

int main()
{
    //print welcome
    int volumes[2] = {0,0}; // [volumeA, volumeB]
    int instruction = 0;

    //while
    printf("Volume A: %d | Volume B: %d\n\n", volumes[0], volumes[1]);

    printf("Pilihan Instruksi:\n");
    printf("1. Isi ember A sampai penuh\n");
    printf("2. Isi ember B sampai penuh\n");
    printf("3. Tuang ember A ke ember B sampai ember B penuh\n");
    printf("4. Tuang ember B ke ember A sampai ember A penuh\n");
    printf("5. Kosongkan ember A\n");
    printf("6. Kosongkan ember B\n");
    printf("Pilihan angka instruksi: ");
    scanf("%d", &instruction);

    /*
    if (instruction == 1){
        fillA(volumes);
    }
    else if (instruction == 2){
        fillB(volumes);
    }
    else if (instruction == 3){
        AtoB(volumes);
    }
    else if (instruction == 4){
        BtoA(volumes);
    }
    else if (instruction == 5){
        emptyA(volumes);
    }
    else if (instruction == 6){
        emptyB(volumes);
    } else {
        printf("Instruksi tidak ada.");
    }
    */

    switch(instruction){
    case 1:
        fillA(volumes);
        break;
    case 2:
        fillB(volumes);
        break;
    case 3:
        AtoB(volumes);
        break;
    case 4:
        BtoA(volumes);
        break;
    case 5:
        emptyA(volumes);
        break;
    case 6:
        emptyB(volumes);
        break;
    default:
        printf("Instruksi tidak ada.\n");
        break;
    }

    printf("\n");


    printf("Volume A: %d | Volume B: %d\n", volumes[0], volumes[1]);


    return 0;
}

void fillA(int volumes[2]){
    volumes[0] = 3;
}

void fillB(int volumes[2]){
    volumes[1] = 5;
}

void AtoB(int volumes[2]){
    int A = volumes[0];
    int B = volumes[1];
    volumes[0] = max(A+B-5, 0);
    volumes[1] = min(A+B, 5);
}

void BtoA(int volumes[2]){
    int A = volumes[0];
    int B = volumes[1];
    volumes[1] = max(A+B-3,0);
    volumes[0] = min(A+B,3);
}

void emptyA(int volumes[2]){
    volumes[0] = 0;
}

void emptyB(int volumes[2]){
    volumes[1] = 0;
}
