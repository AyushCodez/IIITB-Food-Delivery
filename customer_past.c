//Whole file written by Ayush Gupta and Samyak Jain

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define cust_order "cust_order.txt"
#define accept_file "accept_file.txt"
#define delivered_file "delivered_file.txt"


typedef struct{
    char name[30];//name of dish
    int quantity;//quantity of dish
} food_details;//food detials struct

struct food_details_list{
    food_details details;
    struct food_details_list* next;
};//linkedlist of individual food items

typedef struct{
    char delivery_id[20];
    char name[30];
    char id[11];
    char u_a[30]; //user address
    char r_a[30]; //restaurant address
    int n;
    int OTP;
    char order_id[10];
    float amount;
    float commission;
    struct food_details_list* foods;

} delivery_details;//delivery details of one customer

struct deliveries{
    delivery_details details;
    struct deliveries* next;
};//linkedlist of all deliveries

struct food_details_list* add_food_item(struct food_details_list* food_list_head,food_details* new_item);
struct deliveries* add_new_delivery(struct deliveries* delivery_list_head,delivery_details* new_delivery);
struct deliveries* read_details_from_file(char* f_address);
int read_number_of_deliveries(char* f_address);
void print_delivery(delivery_details current_delivery,FILE * p);





struct food_details_list* add_food_item(struct food_details_list* food_list_head,food_details* new_item){
    struct food_details_list* new_food_list = malloc(sizeof(struct food_details_list));
    new_food_list -> details = *(new_item);
    if(food_list_head == NULL){
        new_food_list->next = NULL;
        return new_food_list;
    }
    struct food_details_list* head_copy = food_list_head;
    while(food_list_head->next != NULL){
        food_list_head = food_list_head->next;
    }
    food_list_head->next = new_food_list;
    return head_copy;
}

struct deliveries* add_new_delivery(struct deliveries* delivery_list_head,delivery_details* new_delivery){
    struct deliveries * new_delivery_list = malloc(sizeof(struct deliveries));
    new_delivery_list->details = *(new_delivery);
    if(delivery_list_head == NULL){
        new_delivery_list->next = NULL;
        return new_delivery_list;
    }
    struct deliveries * head_copy = delivery_list_head;
    while(delivery_list_head->next != NULL){
        delivery_list_head = delivery_list_head->next;
    }
    delivery_list_head->next = new_delivery_list;
    return head_copy;
}

struct deliveries* read_details_from_file(char* f_address){
    FILE* p = fopen(f_address,"r");
    struct deliveries* delivery_list_head = malloc(sizeof(struct deliveries)); 
    delivery_list_head = NULL;
    while(1){
        delivery_details* a = malloc(sizeof(delivery_details));
        if(fscanf( p ,"%s %s %s %s %s %d %s %f %f", a->delivery_id, a->name, a->id, a->u_a, a->r_a, &a->OTP, a->order_id, &a->amount, &a->commission) == EOF) break;
        int n;
        fscanf(p,"%d",&n);
        a->n = n;
        struct food_details_list* food_list_head = malloc(sizeof(struct food_details_list));
        food_list_head = NULL;
        while(n--){
            food_details* new_item = malloc(sizeof(food_details)); 
            fscanf(p ,"%s %d", new_item->name, &new_item->quantity);
            food_list_head = add_food_item(food_list_head, new_item);
            a->foods = food_list_head;
        }
        delivery_list_head = add_new_delivery(delivery_list_head, a);
    }
    fclose(p);
    return delivery_list_head;
}

int read_number_of_deliveries(char* f_address){
    int r = 0;
    FILE* p = fopen(f_address,"r");
    while(1){
        char delivery_id[30], name[30], id[11], u_a[30], r_a[30], order_id[10];
        int OTP, quantity;
        float amount, commission;
        if(fscanf( p ,"%s %s %s %s %s %d %s %f %f",delivery_id, name, id, u_a, r_a, &OTP, order_id, &amount, &commission) == EOF) break;
        int n;
        fscanf(p,"%d",&n);
        while(n--){
            char food_name[30]; 
            fscanf(p ,"%s %d", food_name, &quantity);
        }
        r++;
    }
    fclose(p);
    return r;
}

void print_delivery(delivery_details c,FILE * p){
    fprintf(p,"Delivery ID:%s\nRestaurant Address:%s\nOTP(0 if not assigned):%d\nOrder ID:%s\nPrice:%0.2f\n", c.delivery_id, c.r_a, c.OTP, c.order_id, c.amount + c.commission);
    fprintf(p,"%d\n",c.n);
    struct food_details_list* foods = c.foods;
    printf("Order Details:\nITEM | Quantity\n");
    while(foods!=NULL){
        fprintf(p,"%s %d\n",(foods->details).name, (foods->details).quantity);
        foods = foods->next;
    }
    printf("\n\n");
}


void main_past(char * name){
    struct deliveries* to_print;


    int choice = 1;
    while(1){
        system("clear");
        printf("Which deliveries do you want to see?\n1)Orders not accepted by delivery partner yet\n2)Orders accepted by delivery partner\n3)Delivered orders\n(0 to Go back)\n");
        scanf("%d", &choice);
        system("clear");
        if(choice==0) break;
        while(choice>3){
            printf("Invalid choice please try again:");
            scanf("%d", &choice);
        }
        if(choice == 1){
            to_print = read_details_from_file(cust_order);
            printf("Orders not accepted by delivery partner yet:\n");
        }   
        else if(choice == 2){
            to_print = read_details_from_file(accept_file); 
            printf("Orders accepted by delivery partner:\n");
        }
        else if(choice == 3){
            to_print = read_details_from_file(delivered_file);
            printf("Orders Delivered:\n");
        }
        
        while(to_print!=NULL){
            if(strcmp(to_print->details.name,name) == 0){
                print_delivery(to_print->details,stdout);
            }
            to_print = to_print->next;
        }

        char dump;
        printf("Enter any character to go back");
        scanf("%c",&dump);
        scanf("%c",&dump);
    }
}
