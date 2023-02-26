#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cust_order "cust_order.txt"
#define flagfile "flag_file.txt"
#define accept_file "accept_file.txt"

typedef struct{
    char name[30];//name of dish
    int quantity;//quantity of dish
} food_details;//food detials struct

struct food_details_list{
    food_details details;
    struct food_details_list* next;
};//linkedlist of individual food items

typedef struct{
    char name[20];
    char id[14];
    char u_a[30]; //user address
    char r_a[30]; //restaurant address
    int n;
    struct food_details_list* foods;

} delivery_details;//delivery details of one customer

struct deliveries{
    delivery_details details;
    struct deliveries* next;
};//linkedlist of all deliveries

void orderdecline();
void show_orders(struct deliveries* a);
void check_file_for_changes(int* o);
struct deliveries* read_details_from_file(FILE * p);
struct food_details_list* add_food_item(struct food_details_list* food_list_head,food_details* new_item);
struct deliveries* add_new_delivery(struct deliveries* delivery_list_head,delivery_details* new_delivery);
delivery_details* order_accept(struct deliveries* delivery_list_head, int n);
void print_delivery(delivery_details* current_delivery,FILE* p);

struct deliveries* read_details_from_file(FILE * p){//Works perfectly

    struct deliveries* delivery_list_head = malloc(sizeof(struct deliveries)); 
    delivery_list_head = NULL;
    while(1){
        delivery_details* a = malloc(sizeof(delivery_details));
        if(fscanf( p ,"%s %s %s %s", a->name, a->id, a->u_a, a->r_a) == EOF) break;
        int n;//number of food items
        fscanf(p,"%d",&n);
        a->n = n;
        struct food_details_list* food_list_head = malloc(sizeof(struct food_details_list));
        food_list_head = NULL;
        while(n--){
            food_details* new_item = malloc(sizeof(food_details)); 
            fscanf(p ,"%s %d", new_item->name, &new_item->quantity);
            //use your otp thing to add an otp at end of phone number to make it into a delivery id(Kausthubh)
            food_list_head = add_food_item(food_list_head, new_item);
            a->foods = food_list_head;
        }
        delivery_list_head = add_new_delivery(delivery_list_head, a);
    }
    return delivery_list_head;
}


struct food_details_list* add_food_item(struct food_details_list* food_list_head,food_details* new_item){//Works perfectly
    struct food_details_list * new_list_item = malloc(sizeof(struct food_details_list));
    new_list_item -> details = *(new_item);
    new_list_item -> next = food_list_head;
    return new_list_item;
}

struct deliveries* add_new_delivery(struct deliveries* delivery_list_head,delivery_details* new_delivery){//Works perfectly
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

delivery_details* order_accept(struct deliveries* delivery_list_head, int n){//Works perfectly
    delivery_details* accepted_delivery = malloc(sizeof(delivery_details));
    for(int i = 1; i < n; i++){
        delivery_list_head = delivery_list_head->next;
    }
    accepted_delivery = &delivery_list_head->details;
    FILE* p = fopen(accept_file,"a");
    print_delivery(accepted_delivery,p);
    fclose(p);
    return accepted_delivery;
}

void print_delivery(delivery_details* c,FILE* p){//Needs debugging
    fprintf(p,"%s %s %s %s\n",c->name, c->id ,c->u_a ,c->r_a);
    fprintf(p,"%d\n",c->n);
    struct food_details_list* foods = c->foods;
    while(foods!=NULL){
        fprintf(p,"%s %d\n",(foods->details).name, (foods->details).quantity);
        foods = foods->next;
    }
}

void show_orders(struct deliveries* a){//Needs debugging
    char r[3];
    while(1){
        //system("clear");
        printf("\t\t\t\tDeliveries Available!\n\n");
        int i = 1;
        struct deliveries* copy = a;
        while(copy!=NULL){
            printf("\t\t\t\tOrder Number %d.\n\t\t\t\tRestaurant Address is %s\n\t\t\t\tDelivery Address is %s\n\n", i, (copy->details).r_a,(copy->details).u_a);
            i++;
            copy = copy->next;
        }
        printf("What order number do you want to accept?.Press number to accept or 'exit' to go back:");
        scanf("%s",r);
        if(strcmp(r,"exit")==0||strcmp(r,"Exit")==0||strcmp(r,"EXIT")==0) break;
        else if(atoi(r)>0 && atoi(r)<=i){
            delivery_details* accepted_delivery = order_accept(a,atoi(r));
            system("clear");
            printf("\t\t\t\tYou have accepted an order.\n\n\t\t\t\tDelivery is from %s to %s\n", accepted_delivery->r_a, accepted_delivery->u_a);
            break;
        }
        else{
            system("clear");
            printf("\t\t\t\tInvalid Response, please try again\n");
        }
    }
}

void check_file_for_changes(int* o){//Works perfectly
    int newval;
    do{
        FILE* p = fopen(flagfile,"r");
        fscanf(p,"%d",&newval);
        fclose(p);
        if(newval != *o){
            return;
        }
    }while(1);
}

void main(){//Works perfectly
    FILE* flag_file = fopen(flagfile,"r");
    int oldval;
    fscanf(flag_file,"%d",&oldval);
    fclose(flag_file);
    int* o = &oldval;
    char r[4];
    do{
        system("clear");
        while(1){
            printf("\n\n\t\t\t\tDo you want to\n\n\t\t\t\tCheck for new orders?(Press Yes)\n\n\t\t\t\tOr exit the application?(Press exit)\n\n\t\t\t\tResponse:");
            scanf("%s",r);
            if(strcmp(r,"exit")==0||strcmp(r,"Exit")==0||strcmp(r,"EXIT")==0){
                break;
            }
            else if(strcmp(r,"yes")==0||strcmp(r,"Yes")==0||strcmp(r,"YES")==0){
                check_file_for_changes(o);
                FILE* order_file = fopen(cust_order,"r");
                struct deliveries* a = read_details_from_file(order_file);
                fclose(order_file);
                show_orders(a);
            }
            else{
                system("clear");
                printf("\t\t\t\tInvalid Response, please try again\n");
            }
        }
        break;
    }while(1);
    system("clear");
    printf("\t\t\t\tThank You!\n");
}
