#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include ".h"
#include ".h"
#include ".h"

void main(){
    char r;
    do{
        printf("To Login as customer, Press 1:\nTo Login as a deliverer, Press 2:\n To Login as a restaurant owner, Press 3:\nTo exit, Press 4:");
        scanf("%c",&r);
        if(c == '1')
            customer_main();
        else if(c == '2')
            deliverer_main();
        else if(c == '3')
            restaurant_main();
        else if(c == '4')
            break;
        else
            printf("Invalid Input\n");
    }while(1);
}
