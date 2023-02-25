#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cust_order "/home/owais/Desktop/cust_order.txt"
#define SIZE 100

typedef struct{
    char name[20];
    char id[14];
    char u_a[30]; //user address
    char r_a[30]; //restaurant address

} delivery_details;//delivery details of one customer

typedef struct{
    char name[30];//name of dish
    int quantity;//quantity of dish
    food_details* next;
} food_details;//linkedlist of individual food items

typedef struct{
    delivery_details details;
    food_details food;
    deliveries* next;
} deliveries;//linkedlist of all deliveries


void orderaccept();
void orderdecline();
void show_order(delivery_details* a);
int check_file_for_changes();
delivery_details* read_details_from_file(FILE * p);
food_details* add_food_item(food_details* food_list_head,food_details* new_item);
deliveries* add_new_delivery(deliveries* delivery_list_head,deliveries* new_delivery);
deliveries* remove_delivery(deliveries* delivery_list_head,char id);//use id from delivery details inside deliveries to delete the element

deliveries* read_details_from_file(FILE * p){

    delivery_details* a = malloc(sizeof(delivery_details));
    food_details* food_list_head = malloc(sizeof(food_details)); 
    deliveries* delivery_list_head = malloc(sizeof(deliveries)); 

    food_details* new_item = malloc(sizeof(food_details)); 
    deliveries* new_deilvery = malloc(sizeof(deliveries)); 

    while(fscanf( p ,"%s %s %s %s", a->name, a->id, a->u_a, a->r_a)!=EOF){
        int n;//number of food items
        while(n--){
            
            fscanf(p ,"%s %s", new_item->name, new_item->number);
            food_list_head = add_food_item(food_list_headf, new_item);
            new_delivery->details = a;
            new_delivery->food = food_list_head;
            delivery_list_head = add_new_delivery(delivery_list_head, new_delivery);
        }
    }
    return delivery_list_head;
}


food_details* add_food_item(food_details* food_list_head,food_details* new_item){
//
}

deliveries* add_new_delivery(deliveries* delivery_list_head,deliveries* new_delivery){
//
}

deliveries* remove_delivery(deliveries* delivery_list_head,deliveries* delivery){
//
}

int show_order(delivery_details* a){//I'll fix this later(Owais)
    system("clear");
    printf("\t\t\t\tDelivery Available!\n\n\t\t\t\tRestaurant Address is %s\n\t\t\t\tDelivery Address is %s\n\n\t\t\t\tDo you want to accept the delivery or not?\n\t\t\t\tYes or No:",a->r_a,a->u_a);
    char r[3];
}

void orderaccept(){
//the deliveries that are accepted are put into a file, and then the customer can see that his order was accepted
}

void check_file_for_changes(FILE* p){
    do{
        fscanf(p,"%d",&newval);
        if(newval!=oldval){
            return;
        }
        oldval=newval;
        fclose(p);
    }while(1);
}

void main(){
    FILE* cust_order = fopen(cust_order,"r");
    int filechanged, newval, oldval = 0;
    char exit[4];
    do{//needs work, i'll do(Owais)
        check_file_for_changes(cust_order,"r");//Do we make a flag file?
        delivery_details* a = read_details_from_file(p);
        show_order(a);
        system("clear");
        printf("Do you want to exit the application?");
        scanf("%s",exit);
    }while(1);
}
