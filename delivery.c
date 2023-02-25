#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cust_order "/home/owais/Desktop/cust_order.txt"
#define SIZE 100

typedef struct{
    char name[30];//name of dish
    int quantity;//quantity of dish
} food_details;//food detials struct

typedef struct{
    food_details details;
    food_details* next;
} food_details_list;//linkedlist of individual food items

typedef struct{
    char name[20];
    char id[14];
    char u_a[30]; //user address
    char r_a[30]; //restaurant address
    food_details_list* foods;

} delivery_details;//delivery details of one customer

typedef struct{
    delivery_details details;
    delivery_details* next;
} deliveries;//linkedlist of all deliveries

void orderaccept();
void orderdecline();
void show_orders(deliveries* a);
void check_file_for_changes();
deliveries* read_details_from_file(FILE * p);
food_details_list* add_food_item(food_details_list* food_list_head,food_details* new_item);
deliveries* add_new_delivery(deliveries* delivery_list_head,delivery_details* new_delivery);
deliveries* remove_delivery(deliveries* delivery_list_head,char id);//use id from delivery details inside deliveries to delete the element

deliveries* read_details_from_file(FILE * p){

    delivery_details* a = malloc(sizeof(delivery_details));
    deliveries* delivery_list_head = malloc(sizeof(deliveries)); 
    food_details* new_item = malloc(sizeof(food_details)); 
    food_details_list* food_list_head = malloc(sizeof(food_details)); 

    while(fscanf( p ,"%s %s %s %s", a->name, a->id, a->u_a, a->r_a)!=EOF){
        int n;//number of food items
        while(n--){
            fscanf(p ,"%s %d", new_item->name, &new_item->quantity);
            //use your otp thing to add an otp at end of phone number to make it into a delivery id(Kausthubh)
            food_list_head = add_food_item(food_list_head, new_item);
            a->foods = food_list_head;
            delivery_list_head = add_new_delivery(delivery_list_head, a);
        }
    }
    return delivery_list_head;
}


food_details_list* add_food_item(food_details_list* food_list_head,food_details* new_item){
//(Kausthubh)
}

deliveries* add_new_delivery(deliveries* delivery_list_head,delivery_details* new_delivery){
//(Kausthubh)
}

deliveries* remove_delivery(deliveries* delivery_list_head, char id){
//(Kausthubh)
}

void show_orders(deliveries* a){//Need to make changes(Owais)
        system("clear");
    printf("\t\t\t\tDelivery Available!\n\n\t\t\t\tRestaurant Address is %s\n\t\t\t\tDelivery Address is %s\n\n\t\t\t\tDo you want to accept the delivery or not?\n\t\t\t\tYes or No:",(a->details).r_a,(a->details).u_a);
    char r[3];
}

void orderaccept(){
//the deliveries that are accepted are put into a file, and then the customer can see that his order was accepted(Kausthubh)
}

void check_file_for_changes(FILE* p){
    int oldval = 0;
    do{
        int newval;
        fscanf(p,"%d",&newval);
        if(newval!=oldval){
            return;
        }
        oldval=newval;
        fclose(p);
    }while(1);
}

void main(){
    FILE* order_file = fopen(cust_order,"r");
    int filechanged, newval, oldval = 0;
    char exit[4];
    do{
        check_file_for_changes(order_file);//Do we make a flag file?
        deliveries* a = read_details_from_file(order_file);
        show_orders(a);
        system("clear");
        printf("Do you want to exit the application?");
        scanf("%s",exit);
        while(1){
            printf("\t\t\t\tDo you want to\n\n\t\t\t\tCheck for new orders?(Press Yes)\n\n\t\t\t\tOr exit the application?(Press exit)\n\n\t\t\t\tResponse:");
            scanf("%s",r);
            if(strcmp(r,"exit")==0) break;
            else if(atoi(r)>0 && atoi(r)<=15){
                orderaccept(atoi(r));

            }
            else printf("\t\t\t\tInvalid Response, please try again");
        }
    }while(1);
}
