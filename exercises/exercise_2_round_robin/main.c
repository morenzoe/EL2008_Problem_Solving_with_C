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
    printf("Program ini akan mencetak urutan antrian dari lima proses.\n");
    printf("Kelima proses diurutkan dari waktu kedatangan terkecil.\n\n");

    int arrival[5] = {0,0,0,0,0};
    int execution[5] = {0,0,0,0,0};
    int processed[5] = {0,0,0,0,0};

    printf("Masukan waktu kedatangan tiap proses!\n");
    int i;
    for(i=0;i<5;i++){
        printf("Waktu kedatangan proses P%d adalah: ", i);
        scanf("%d",&arrival[i]);
    }
    printf("\n");

    printf("Masukan waktu eksekusi tiap proses!\n");
    for(i=0;i<5;i++){
        printf("Waktu eksekusi proses P%d adalah: ", i);
        scanf("%d",&execution[i]);
    }
    printf("\n");

    int quantum_time = 0;
    printf("Waktu kuantum mesin adalah: ");
    scanf("%d",&quantum_time);
    printf("\n");

    print_array(arrival);

    int total_time = arrival[0];
    int machine_time = quantum_time;
    int queue[5] = {0,6,6,6,6};
    int waiting = 1;
    int user = 0;
    while (!compare_array(arrival,execution)){
        printf("%d | ", total_time);
        print_waiting(queue);
        printf("\n");

        if (execution[user]-processed[user]<machine_time){
            processed[user]=execution[user];
            user++

        } else if (user<4 && arrival[user+1]-total_time<machine_time){
            total_time=arrival[user+1]

        }

}


