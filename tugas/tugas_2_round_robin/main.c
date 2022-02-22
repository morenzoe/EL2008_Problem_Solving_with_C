#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print_array(int arr[5]){
    printf("[");
    int i;
    for(i=0;i<5;i++){
        printf("%d", arr[i]);
        if (i<4){
            printf(",");
        }
    }
    printf("]");
}

bool compare_array(int arr1[5], int arr2[5]){
    for (int i = 0; i < 5; i++)
        if (arr1[i] != arr2[i]){
            return false;
        }

    // If all elements were same.
    return true;
}

void print_waiting(int arr[5]){
    printf("[");

    int i;
    for(i=0;i<5-1;i++){
        if (arr[i]!=6){
            printf("%d", arr[i]);
        }
        if (arr[i+1]!=6){
            printf(",");
        }

    }
    if (arr[4]!=6){
        printf("%d", arr[4]);
    }
    printf("]");
}

int main()
{
    printf("Selamat datang di program Round Robin!\n");
    printf("Program ini akan mencetak urutan antrian dari 6 proses.\n");
    printf("Keenam proses diurutkan dari waktu kedatangan terkecil.\n\n");

    int arrival[6] = {0,0,0,0,0};
    int execution[6] = {0,0,0,0,0};
    int processed[6] = {0,0,0,0,0};
    int queue[6] = {-1,-1,-1,-1,-1,-1};

    printf("Masukan waktu kedatangan tiap proses!\n");
    int i;
    for(i=0;i<5;i++){
        printf("Waktu kedatangan proses P%d adalah: ", i);
        scanf("%d",&arrival[i]);
    }
    printf("\n");

    printf("Masukan durasi eksekusi tiap proses!\n");
    for(i=0;i<5;i++){
        printf("Waktu eksekusi proses P%d adalah: ", i);
        scanf("%d",&execution[i]);
    }
    printf("\n");

    int quantum_time;
    printf("Waktu kuantum mesin adalah: ");
    scanf("%d",&quantum_time);
    printf("\n");

    print_array(arrival);

    int total_time = arrival[0];
    printf("Waktu: %d", total_time);
    for (i=0;i<5;i++){
            printf("TP%d: %d", i, processed[i]);
    }


/*
    int machine_time = quantum_time;
    queue[0] = 0;
    int waiting = 1;
    int user = 0;
    int process_done = 0;

    while (!(process_done==6)) {


}
*/

