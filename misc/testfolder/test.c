#include <stdio.h>


void main(void){
    unsigned int num;

    while(num!=69420){
        printf("give number: ");
        scanf("%d", &num);

        printf("\nnum: %d \nwhole: %d \nremainder: %d \n\n", num, num/10, \
                                                             num%10);

    }
    


    return;
}