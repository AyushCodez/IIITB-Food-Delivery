#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define cust_order "cust_order.txt"
#define accept_file "accept_file.txt"
#define Order_delivered_file "Order_delivered_file.txt"

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
    int order_id;
    struct food_details_list* foods;

} delivery_details;//delivery details of one customer

struct deliveries{
    delivery_details details;
    struct deliveries* next;
};//linkedlist of all deliveries

void check_file_for_changes(char* p, int o);//We don't need this now
struct food_details_list* add_food_item(struct food_details_list* food_list_head,food_details* new_item);
struct deliveries* add_new_delivery(struct deliveries* delivery_list_head,delivery_details* new_delivery);
struct deliveries* read_details_from_file(char* fname);
void print_delivery(delivery_details* current_delivery,FILE* p);
void show_orders(int* f);
delivery_details* order_accept(struct deliveries* delivery_list_head, int n, int OTP, int order_id);
int generate_OTP(int n);

void check_file_for_changes(char* p, int o){//We don't need this now
    int checkval;
    do{
        FILE* file_to_check = fopen(p,"r");
        fscanf(file_to_check, "%d", &checkval);
        fclose(file_to_check);
        if(checkval == o){
            return;
        }
    }while(1);
}

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

struct deliveries* read_details_from_file(char* fname){
    FILE* p = fopen(fname,"r");
    struct deliveries* delivery_list_head = malloc(sizeof(struct deliveries)); 
    delivery_list_head = NULL;
    while(1){
        delivery_details* a = malloc(sizeof(delivery_details));
        if(fscanf( p ,"%s %s %s %s", a->name, a->id, a->u_a, a->r_a) == EOF) break;
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

void print_delivery(delivery_details* c,FILE* p){
    fprintf(p,"%s %s %s %s %d %d\n", c->name, c->id, c->u_a, c->r_a, c->OTP, c->order_id);
    fprintf(p,"%d\n",c->n);
    struct food_details_list* foods = c->foods;
    while(foods!=NULL){
        fprintf(p,"%s %d\n",(foods->details).name, (foods->details).quantity);
        foods = foods->next;
    }
}

delivery_details* order_accept(struct deliveries* delivery_list_head, int n, int OTP, int order_id){
    delivery_details* accepted_delivery = malloc(sizeof(delivery_details));
    for(int i = 1; i < n; i++){
        delivery_list_head = delivery_list_head->next;
    }
    delivery_list_head->details.OTP = OTP;
    delivery_list_head->details.order_id = order_id;
    accepted_delivery = &delivery_list_head->details;
    FILE* p = fopen(accept_file,"a");
    print_delivery(accepted_delivery,p);
    fclose(p);
    return accepted_delivery;
}

int generate_OTP(int a){
    srand(time(NULL));
    int OTP = 1000 + (rand() % a);
    return OTP;
}

void show_orders(int* f){
    char response[30];
    struct deliveries* a = read_details_from_file(cust_order);

    while(*f){
        printf("\n\n\t\t\t\t\tDo you want to\n\n\t\t\t\t\tCheck for new orders?(Press Yes)\n\n\t\t\t\t\tOr exit the application?(Press exit)\n\n\t\t\t\t\tResponse:");
        scanf("%s",response);
        if(strcmp(response,"exit")==0||strcmp(response,"Exit")==0||strcmp(response,"EXIT")==0||strcmp(response,"no")==0||strcmp(response,"No")==0||strcmp(response,"NO")==0){
            *f = 0;
            system("clear");
            return;
        }
        else if(strcmp(response,"yes")==0||strcmp(response,"Yes")==0||strcmp(response,"YES")==0){
            a = read_details_from_file(cust_order);
            while(1){
                system("clear");
                while(a==NULL){
                    system("clear");
                    printf("\n\n\t\t\t\t\tThere are no deliveries available right now.\n\n\t\t\t\t\tDo you want to\n\n\t\t\t\t\tCheck for new orders?(Press Yes to check again.)\n\n\t\t\t\t\tOr exit the application?(Press exit)\n\n\t\t\t\t\tResponse:");
                    scanf("%s",response);
                    if(strcmp(response,"exit")==0||strcmp(response,"Exit")==0||strcmp(response,"EXIT")==0||strcmp(response,"no")==0||strcmp(response,"No")==0||strcmp(response,"NO")==0){
                        *f = 0;
                        system("clear");
                        return;
                    }
                    else if(strcmp(response,"yes")==0||strcmp(response,"Yes")==0||strcmp(response,"YES")==0){
                        a = read_details_from_file(cust_order);
                        system("clear");
                    }
                    else{
                        system("clear");
                        return;
                    }
                }
                printf("\t\t\t\t\tDeliveries Available!\n\n");
                int i = 1;
                struct deliveries* copy = a;
                while(copy!=NULL){
                    printf("\t\t\t\t\tOrder Number %d.\n\t\t\t\t\tRestaurant Address is %s\n\t\t\t\t\tDelivery Address is %s\n\n", i, (copy->details).r_a,(copy->details).u_a);
                    i++;
                    copy = copy->next;
                }
                printf("\n\n\t\t\t\t\tWhat order number do you want to accept?\n\n\t\t\t\t\tPress number to accept or 'exit' to go back:");
                scanf("%s",response);
                system("clear");
                if(strcmp(response,"exit")==0||strcmp(response,"Exit")==0||strcmp(response,"EXIT")==0){
                    *f = 0;
                    system("clear");
                    return;
                }
                else if(atoi(response)>0 && atoi(response)<=i){
                    int c = 0;
                    delivery_details* accepted_delivery = order_accept(a,atoi(response),generate_OTP(9000),generate_OTP(99000));
                    do{
                        printf("\t\t\t\t\tYou have accepted an order.\n\n\t\t\t\t\tDelivery is from %s to %s.\n\t\t\t\t\tThe order id is %d.\n\t\t\t\t\tThe contact number of the customer is %s.\n\n\n\t\t\t\t\tIf you have delivered the order, press Yes.\n\t\t\t\t\tResponse:", accepted_delivery->r_a, accepted_delivery->u_a, accepted_delivery->order_id, accepted_delivery->id);
                        scanf("%s",response);
                    }while(strcmp(response,"yes")&&strcmp(response,"Yes")&&strcmp(response,"YES"));
                    printf("\n\n\t\t\t\t\tYou have delivered the order to %s at %s.\n\n\t\t\t\t\tAsk %s for the OTP and enter it here to confirm your delivery:", accepted_delivery->name, accepted_delivery->u_a, accepted_delivery->name);
                   do{
                        c++; scanf("%s",response);
                        if(atoi(response) == accepted_delivery->OTP){
                            break;
                        }
                        printf("\n\n\t\t\t\t\tYou have entered the wrong OTP. Try again:");
                    }while(atoi(response) != accepted_delivery->OTP && c<5);
                    system("clear");
                    if(c==5){
                        printf("You have incorrectly entered OTP 5 times.Your delivery was not confirmed.");
                    }
                    else printf("\n\n\t\t\t\t\tYou delivery has been confirmed.\n\n\n\n");
                    break;
                }
                else{
                    break;
                }
            }
        }
        system("clear");
        printf("\t\t\t\t\tInvalid Response, please try again.\n");
        a = read_details_from_file(cust_order);
    }
}

void main(){
    int f = 1;
    system("clear");
    do{
        show_orders(&f);
    }while(f);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tThank You!\n\n\n\n\n\n\n\n\n\n\n\n");
}
