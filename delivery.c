#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cust_order "/home/owais/Desktop/cust_order.txt"
#define flagfile "/home/owais/Desktop/flag_file.txt"
#define accept_file "/home/owais/Desktop/accept_file.txt"

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
void check_file_for_changes(char* p,int* o);
struct deliveries* read_details_from_file(FILE * p);
struct food_details_list* add_food_item(struct food_details_list* food_list_head,food_details* new_item);
struct deliveries* add_new_delivery(struct deliveries* delivery_list_head,delivery_details* new_delivery);
struct deliveries* orderaccept(struct deliveries* delivery_list_head, int i);
void print_delivery(struct deliveries* current_delivery,FILE* p);

struct deliveries* read_details_from_file(FILE * p){

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


struct food_details_list* add_food_item(struct food_details_list* food_list_head,food_details* new_item){
    struct food_details_list * new_list_item = malloc(sizeof(struct food_details_list));
    new_list_item -> details = *(new_item);
    new_list_item -> next = food_list_head;
    return new_list_item;
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
        printf("%s\n",new_delivery->name);
        delivery_list_head = delivery_list_head->next;
    }
    delivery_list_head->next = new_delivery_list;
    return head_copy;
}

struct deliveries* orderaccept(struct deliveries* delivery_list_head, int n){
    if(n == 1){
        return delivery_list_head -> next;
    }
    struct deliveries * current_delivery = delivery_list_head;
    struct deliveries * previous_delivery = delivery_list_head;
    for(int i = 1; i < n; i++){
        previous_delivery = current_delivery;
        current_delivery = current_delivery -> next;
    }
    previous_delivery -> next = current_delivery -> next;
    FILE* p = fopen(accept_file,"a");
    print_delivery(current_delivery,p);
    free(current_delivery);
    return delivery_list_head;
}

void print_delivery(struct deliveries* c,FILE* p){
    fprintf(p,"%s %s %s %s",(c->details).name, (c->details).id ,(c->details).u_a ,(c->details).r_a);
    fprintf(p,"%d",(c->details).n);
    struct food_details_list* foods = (c->details).foods;
    while(foods->next!=NULL){
        fprintf(p,"%s %d",(foods->details).name, (foods->details).quantity);
    }
}

void show_orders(struct deliveries* a){//Need to make changes(Owais)
    char r[3];
    while(1){
        system("clear");
        printf("\t\t\t\tDeliveries Available!\n\n");
        int i = 1;
        while(a!=NULL){
            printf("\t\t\t\tOrder Number is %d. Restaurant Address is %s\n\t\t\t\tDelivery Address is %s\n\n", i, (a->details).r_a,(a->details).u_a);
            i++;
            a = a->next;
        }
        printf("What order number do you want to accept?.Press number to accept or 'exit' to go back:");
        scanf("%s",r);
        if(strcmp(r,"exit")==0||strcmp(r,"Exit")==0||strcmp(r,"EXIT")==0) break;
        else if(atoi(r)>0 && atoi(r)<=i){
            a = orderaccept(a,atoi(r));
            break;
        }
        else{
            system("clear");
            printf("\t\t\t\tInvalid Response, please try again\n");
        }
    }
}

void check_file_for_changes(char * flag_file_str,int* o){
    int newval;
    do{
        FILE* p = fopen(flag_file_str,"r");
        fscanf(p,"%d",&newval);
        fclose(p);
        if(newval != *o){
            return;
        }
    }while(1);
}

void main(){
    FILE* order_file = fopen(cust_order,"r");
    FILE* flag_file = fopen(flagfile,"r");
    int oldval;
    fscanf(flag_file,"%d",&oldval);
    fclose(flag_file);
    int* o = &oldval;
    char r[4];
    do{
        system("clear");
        while(1){
            printf("\t\t\t\tDo you want to\n\n\t\t\t\tCheck for new orders?(Press Yes)\n\n\t\t\t\tOr exit the application?(Press exit)\n\n\t\t\t\tResponse:");
            scanf("%s",r);
            if(strcmp(r,"exit")==0||strcmp(r,"Exit")==0||strcmp(r,"EXIT")==0) break;
            else if(strcmp(r,"yes")==0||strcmp(r,"Yes")==0||strcmp(r,"YES")==0){
                check_file_for_changes(flagfile,o);
                struct deliveries* a = read_details_from_file(order_file);
                show_orders(a);
            }
            else{
                system("clear");
                printf("\t\t\t\tInvalid Response, please try again\n");
            }
        }
        break;
    }while(1);
}
