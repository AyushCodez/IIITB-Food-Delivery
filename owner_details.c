#include<stdio.h>
#include<stdlib.h>
typedef struct{
    char name[30];//name of dish
    int quantity;//quantity of dish
} food_details;//food detials struct

struct food_details_list{
    food_details details;
    struct food_details_list* next;
};//linkedlist of individual food items

typedef struct{
    char name[30];
    char id[11];
    char u_a[30]; //user address
    char r_a[30]; //restaurant address
    int n;
    int OTP;
    char order_id[10];
    struct food_details_list* foods;

} delivery_details;//delivery details of one customer

struct deliveries{
    delivery_details details;
    struct deliveries* next;
};//linkedlist of all deliveries

struct food_details_list* add_food_item(struct food_details_list* food_list_head,food_details* new_item);
struct deliveries* add_new_delivery(struct deliveries* delivery_list_head,delivery_details* new_delivery);
struct deliveries* read_details_from_file(char* f_address);

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
        int OTP, quantity;
        if(fscanf( p ,"%s %s %s %s %d %s", a->name, a->id, a->u_a, a->r_a, &a->OTP, a->order_id) == EOF) break;
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
        printf("%s %s %s %s %d %s\n", a->name, a->id, a->u_a, a->r_a, a->OTP, a->order_id);
        delivery_list_head = add_new_delivery(delivery_list_head, a);
    }
    fclose(p);
    return delivery_list_head;
}

void print_delivery(struct deliveries* d,FILE* p){
    delivery_details c;
    c = (*d).details;
    fprintf(p,"%s %s %s %s %d %s\n", c.name, c.id, c.u_a, c.r_a, c.OTP, c.order_id);
    fprintf(p,"%d\n",c.n);
    struct food_details_list* foods = c.foods;
    while(foods!=NULL){
        fprintf(p,"%s %d\n",(foods->details).name, (foods->details).quantity, (foods->details).price);
        foods = foods->next;
    }
    fclose(p);
}

void main(){
    struct deliveries* d;
    d = read_details_from_file("accept_file.txt");
    print_delivery(d,stdout);
}

