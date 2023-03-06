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
    char order_id[10];
    float amount;
    struct food_details_list* foods;

} delivery_details;//delivery details of one customer

struct deliveries{
    delivery_details details;
    struct deliveries* next;
};//linkedlist of all deliveries

void check_file_for_changes(char* p, int o);//We don't need this now
struct food_details_list* add_food_item(struct food_details_list* food_list_head,food_details* new_item);
struct deliveries* add_new_delivery(struct deliveries* delivery_list_head,delivery_details* new_delivery);
struct deliveries* read_details_from_file(char* f_address);
int read_number_of_deliveries(char* f_address);
void print_delivery(delivery_details* current_delivery,char* f_address);
void show_orders(int* f);
delivery_details* order_accept(struct deliveries* delivery_list_head, int n, int OTP, int order_id);
int generate_OTP(int a, int b);
char* itoa(int n);

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

struct deliveries* read_details_from_file(char* f_address){
    FILE* p = fopen(f_address,"r");
    struct deliveries* delivery_list_head = malloc(sizeof(struct deliveries)); 
    delivery_list_head = NULL;
    while(1){
        delivery_details* a = malloc(sizeof(delivery_details));
        if(fscanf( p ,"%s %s %s %s %f", a->name, a->id, a->u_a, a->r_a, &a->amount) == EOF) break;
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
        char name[30], id[11], u_a[30], r_a[30], order_id[10];
        int OTP, quantity;
        float amount;
        if(fscanf( p ,"%s %s %s %s %d %s %f", name, id, u_a, r_a, &OTP, order_id, &amount) == EOF) break;
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

void print_delivery(delivery_details* c,char* f_address){
    FILE* p = fopen(f_address,"a");
    fprintf(p,"%s %s %s %s %d %s %0.2f\n", c->name, c->id, c->u_a, c->r_a, c->OTP, c->order_id, c->amount);
    fprintf(p,"%d\n",c->n);
    struct food_details_list* foods = c->foods;
    while(foods!=NULL){
        fprintf(p,"%s %d\n",(foods->details).name, (foods->details).quantity);
        foods = foods->next;
    }
    fclose(p);
}

delivery_details* order_accept(struct deliveries* delivery_list_head, int n, int OTP, int order_id){
    delivery_details* accepted_delivery = malloc(sizeof(delivery_details));
    for(int i = 1; i < n; i++){
        delivery_list_head = delivery_list_head->next;
    }
    delivery_list_head->details.OTP = OTP;
    strcpy(delivery_list_head->details.order_id, itoa(order_id));
    accepted_delivery = &delivery_list_head->details;
    print_delivery(accepted_delivery,accept_file);
    return accepted_delivery;
}

int generate_OTP(int a, int b){
    srand(time(NULL));
    int OTP = a + (rand() % (b-a));
    return OTP;
}

char* itoa(int n){
    int len_str = 0;
    int str_size;
    int copy = n;
    while(n > 0)
    {
        n = n / 10;
        len_str ++;
    }

    char* str;

    if(len_str <= 4){
        str = (char*)malloc(4);
        for(int i = 0; i < (4 - len_str); i++)
        {
            str[i] = '0';
        }
        str_size = 5;
    }
    else{str = (char*)malloc(len_str); str_size = len_str + 1;}

    for(int i = 0; i < len_str; i++)
    {
        int reminder = copy % 10;
        str[str_size - i - 2] = (char)(reminder + (int)'0');
        copy = copy / 10;
    }
    str[str_size - 1] = '\0';
    return str;
}

void show_orders(int* f){
    char response[30];
    struct deliveries* a = read_details_from_file(cust_order);

    while(1){
        printf("\n\n\t\t\t\t\t\t\t\t  Do you want to\n\n\t\t\t\t\t\t\t\t  Check for new orders?(Press Yes)\n\t\t\t\t\t\t\t\t  Or exit the application?(Press exit)\n\n\t\t\t\t\t\t\t\t  Response:");
        scanf("%s",response);
        if(strcmp(response,"exit")==0||strcmp(response,"Exit")==0||strcmp(response,"EXIT")==0||strcmp(response,"no")==0||strcmp(response,"No")==0||strcmp(response,"NO")==0){
            *f = 0;
            system("clear");
            printf("\t\t\t\t\t\t\t\t  :  : : :::Deliveries Screen::: : :  :\n");
            for(int i=0;i<173;i++) printf("_");printf("\n");
            return;
        }
        else if(strcmp(response,"yes")==0||strcmp(response,"Yes")==0||strcmp(response,"YES")==0){
            a = read_details_from_file(cust_order);
            while(1){
                system("clear");
                printf("\t\t\t\t\t\t\t\t  :  : : :::Deliveries Screen::: : :  :\n");
                for(int i=0;i<173;i++) printf("_");printf("\n");
                while(a==NULL){
                    system("clear");
                    printf("\t\t\t\t\t\t\t\t  :  : : :::Deliveries Screen::: : :  :\n");
                    for(int i=0;i<173;i++) printf("_");printf("\n");
                    printf("\n\n\t\t\t\t\t\t\t\t  There are no deliveries available right now.\n\n\t\t\t\t\t\t\t\t  Do you want to\n\n\t\t\t\t\t\t\t\t  Check for new orders?(Press Yes to check again.)\n\t\t\t\t\t\t\t\t  Or exit the application?(Press exit)\n\n\t\t\t\t\t\t\t\t  Response:");
                    scanf("%s",response);
                    if(strcmp(response,"exit")==0||strcmp(response,"Exit")==0||strcmp(response,"EXIT")==0||strcmp(response,"no")==0||strcmp(response,"No")==0||strcmp(response,"NO")==0){
                        *f = 0;
                        system("clear");
                        printf("\t\t\t\t\t\t\t\t  :  : : :::Deliveries Screen::: : :  :\n");
                        for(int i=0;i<173;i++) printf("_");printf("\n");
                        return;
                    }
                    else if(strcmp(response,"yes")==0||strcmp(response,"Yes")==0||strcmp(response,"YES")==0){
                        a = read_details_from_file(cust_order);
                        system("clear");
                        printf("\t\t\t\t\t\t\t\t  :  : : :::Deliveries Screen::: : :  :\n");
                        for(int i=0;i<173;i++) printf("_");printf("\n");
                    }
                    else{//change needed?
                        system("clear");
                        printf("\t\t\t\t\t\t\t\t  :  : : :::Deliveries Screen::: : :  :\n");
                        for(int i=0;i<173;i++) printf("_");printf("\n");
                        printf("\n\t\t\t\t\t\t\t\t  Invalid Response, please try again.\n");
                        return;
                    }
                }
                printf("\n\n\t\t\t\t\t\t\t\t  Deliveries Available!\n\n");
                int i = 1;
                struct deliveries* copy = a;
                while(copy!=NULL){
                    printf("\t\t\t\t\t\t\t\t  Order Number %d.\n\t\t\t\t\t\t\t\t  Restaurant Address is %s\n\t\t\t\t\t\t\t\t  Delivery Address is %s\n\n", i, (copy->details).r_a,(copy->details).u_a);
                    i++;
                    copy = copy->next;
                }
                printf("\n\n\t\t\t\t\t\t\t\t  Which order do you want to accept?\n\t\t\t\t\t\t\t\t  Press order number to accept it or press 'exit' to go back:");
                scanf("%s",response);
                system("clear");
                printf("\t\t\t\t\t\t\t\t  :  : : :::Deliveries Screen::: : :  :\n");
                for(int i=0;i<173;i++) printf("_");printf("\n");
                if(strcmp(response,"exit")==0||strcmp(response,"Exit")==0||strcmp(response,"EXIT")==0||strcmp(response,"no")==0||strcmp(response,"No")==0||strcmp(response,"NO")==0){
                    *f = 0;
                    system("clear");
                    printf("\t\t\t\t\t\t\t\t  :  : : :::Deliveries Screen::: : :  :\n");
                    for(int i=0;i<173;i++) printf("_");printf("\n");
                    return;
                }
                else if(atoi(response)>0 && atoi(response)<=i){
                    int c = 0;
                    int num_delivered = read_number_of_deliveries(accept_file);
                    delivery_details* accepted_delivery = order_accept(a,atoi(response),generate_OTP(1000,10000),num_delivered+1);
                    do{
                        system("clear");
                        printf("\t\t\t\t\t\t\t\t  :  : : :::Deliveries Screen::: : :  :\n");
                        for(int i=0;i<173;i++) printf("_");printf("\n");
                        printf("\n\n\t\t\t\t\t\t\t\t  You have accepted an order.\n\n\t\t\t\t\t\t\t\t  Delivery is from %s to %s.\n\t\t\t\t\t\t\t\t  The order id is %s.\n\t\t\t\t\t\t\t\t  The contact number of the customer is %s.\n\n\n\t\t\t\t\t\t\t\t  You have to collect %0.2f rupees from %s.\n\n\n\t\t\t\t\t\t\t\t  If you have delivered the order, press Yes.\n\t\t\t\t\t\t\t\t  Response:", accepted_delivery->r_a, accepted_delivery->u_a, accepted_delivery->order_id, accepted_delivery->id, accepted_delivery->amount, accepted_delivery->name);
                        scanf("%s",response);
                    }while(strcmp(response,"yes")&&strcmp(response,"Yes")&&strcmp(response,"YES"));
                    printf("\n\n\t\t\t\t\t\t\t\t  You have delivered the order to %s at %s.\n\n\t\t\t\t\t\t\t\t  Ask %s for the OTP and enter it here to confirm your delivery:", accepted_delivery->name, accepted_delivery->u_a, accepted_delivery->name);
                    while(atoi(response) != accepted_delivery->OTP && c<5){
                        scanf("%s",response);
                        if(atoi(response) == accepted_delivery->OTP){
                            break;
                        }
                        c++;
                        if(c!=5)
                            printf("\n\n\t\t\t\t\t\t\t\t  You have entered the wrong OTP %d %s. Try again:", c, c==1?"time":"times");
                    };
                    system("clear");
                    printf("\t\t\t\t\t\t\t\t  :  : : :::Deliveries Screen::: : :  :\n");
                    for(int i=0;i<173;i++) printf("_");printf("\n");
                    if(c==5){
                        printf("\n\n\t\t\t\t\t\t\t\t  You have incorrectly entered OTP 5 times.Your delivery was not confirmed.\n\n");
                    }
                    else{
                        printf("\n\n\t\t\t\t\t\t\t\t  You delivery has been confirmed.\n\n\n\n");
                    }
                    break;
                }
                else{
                    system("clear");
                    printf("\t\t\t\t\t\t\t\t  :  : : :::Deliveries Screen::: : :  :\n");
                    for(int i=0;i<173;i++) printf("_");printf("\n");
                    printf("\n\t\t\t\t\t\t\t\t  Invalid Response, please try again.\n");
                    a = read_details_from_file(cust_order);
                    break;
                }
            }
        }
        else{
            system("clear");
            printf("\t\t\t\t\t\t\t\t  :  : : :::Deliveries Screen::: : :  :\n");
            for(int i=0;i<173;i++) printf("_");printf("\n");
            printf("\n\t\t\t\t\t\t\t\t  Invalid Response, please try again.\n");
            a = read_details_from_file(cust_order);
        }
    }
}

void main(){
    int f = 1;
    system("clear");
    printf("\t\t\t\t\t\t\t\t  :  : : :::Deliveries Screen::: : :  :\n");
    for(int i=0;i<173;i++) printf("_");printf("\n");
    do{
        show_orders(&f);
    }while(f);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t  Thank You!\n\n\n\n\n\n\n\n\n\n\n\n");
}
