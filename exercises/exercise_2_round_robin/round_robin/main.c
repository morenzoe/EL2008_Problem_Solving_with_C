#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arrival[5] = {0,0,0,0,0};
    int execution[5] = {0,0,0,0,0};

    int i;
    for(i=0;i<5;i++){
        printf("Waktu kedatangan proses P%d adalah: ", i);
        scanf("%d",&arrival[i]);
    }

    printf("\n");

    for(i=0;i<5;i++){
        printf("Waktu eksekusi proses P%d adalah: ", i);
        scanf("%d",&execution[i]);
    }

    printf("\n");

    print_array(arrival);

}

int print_array(int arr[5]){
    printf("[");

    int i;
    for(i=0;i<5-1;i++){
        printf("%d", arr[i]);
        printf(",");
    }

    printf("%d", arr[4]);
    printf("]");
}


