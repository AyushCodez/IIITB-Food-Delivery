#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct food_item {

    char nameofdish[50]; 
    char typeofdish[20];
    char categoryofdish[20];
    char priceofdish[10];
};

struct hotel { 
    char name[50];
    int num_items;
    struct food_item menu[50];
};

void add_item(struct hotel *h, char *name, char *type,char *category,char *price) {
    struct food_item item;
    strcpy(item.nameofdish, name);
    strcpy(item.typeofdish, type);
    strcpy(item.categoryofdish, category);
    strcpy(item.priceofdish, price);    
    (*h).menu[(*h).num_items] = item;
    (*h).num_items++;
}

void print_menu(struct hotel *h) {
    printf("Menu for %s:\n", h->name);
    for (int i = 0; i < h->num_items; i++) {
        printf("%d %s %s %s %s\n", i+1, h->menu[i].nameofdish,h->menu[i].typeofdish, h->menu[i].categoryofdish, h->menu[i].priceofdish);
    }
}

int main() {

    FILE *fptr;
    int cadd;
    fptr = fopen("dish_file", "r");
    struct food_item d[100];
    for(int i = 0;i<100;i++){
        fscanf(fptr,"%s %s %s %s",d[i].nameofdish,d[i].typeofdish,d[i].categoryofdish,d[i].priceofdish);
        
    }
 
    for(int i = 0;i<100;i++){
        if(strcmp(d[i].nameofdish,"") == 0){
            cadd = i;
            break;
        }
    }
    fclose(fptr);

    struct hotel my_hotel;
    strcpy(my_hotel.name, "My Hotel");
    my_hotel.num_items = 0;

    for(int i = 0;i<cadd;i++){
        //printf("%s %s %s %s\n",d[i].nameofdish,d[i].typeofdish,d[i].categoryofdish,d[i].priceofdish);
        add_item(&my_hotel,d[i].nameofdish,d[i].typeofdish,d[i].categoryofdish,d[i].priceofdish);
    }

    print_menu(&my_hotel);

    int cart[50];
    int num_items = 0;
    int choice = 0;
    do {
        printf("Enter item number to add to cart (0 to finish): ");
        scanf("%d", &choice);
        if (choice != 0) {
            cart[num_items] = choice - 1;
            num_items++;
        }
    } while (choice != 0);

    printf("Items in cart:\n");
    int total = 0;
    for (int i = 0; i < num_items; i++) {
        int index = cart[i];
        printf("%s %s %s %s\n", my_hotel.menu[index].nameofdish,my_hotel.menu[index].typeofdish,my_hotel.menu[index].categoryofdish, my_hotel.menu[index].priceofdish);
        total += atoi(my_hotel.menu[index].priceofdish);
    }
    printf("Total: %d\n", total);

    return 0;
}
