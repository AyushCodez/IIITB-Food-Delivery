#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct dishes
{
    char nameofdish[30]; 
    char typeofdish[20]; //whether it is veg/non-veg/jain
    char categoryofdish[20]; //whether it is beverage/fastfood...
    char priceofdish[10];
};

struct rest{
    char name[20];
    char address[50];
    float dist; //enter in Km
    char contact[10];
    int num_dishes;
    struct dishes d[20];
};

typedef struct current_customer1{
	char nm[21]; char ph[11]; char ad[201];
	char us[11]; char ps[11];
	double mny; // money
} cc_new;

void print_dish(struct dishes d){
    printf("%s %s %s %s\n",d.nameofdish,d.typeofdish,d.categoryofdish,d.priceofdish);
}

struct order_dish{
        struct dishes dish;
        int quantity;  
};

struct cart{
    struct rest restaurant;
    struct order_dish dishes[30];
    int num_of_dishes;
    int price;
};

float main_order(cc_new cust){
    FILE *fptr;
    fptr = fopen("new_file", "r");
    struct rest r[100];
    int i = 0;
    while(fscanf(fptr,"%s",r[i].name)!=EOF){
        fscanf(fptr,"%s",r[i].address);
        fscanf(fptr,"%f",&r[i].dist);
        fscanf(fptr,"%s",r[i].contact);
        fscanf(fptr,"%d", &r[i].num_dishes);
        for(int j = 0;j < r[i].num_dishes;j++){
            fscanf(fptr,"%s %s %s %s",r[i].d[j].nameofdish, r[i].d[j].typeofdish,r[i].d[j].categoryofdish,r[i].d[j].priceofdish);
        }
        i++;
    }
    fclose(fptr); 
    while(1){
        system("clear");
        int choice;
        struct rest rest_chose;
        printf("Choose restaurant(0 to exit):\n");
        for(int j = 0;j<i;j++){
            printf("%d) %s\n",j+1,r[j].name);
        }
        scanf("%d",&choice);
        while(choice > i){
            if(choice <=0) break;
            printf("Invalid choice, please enter again:");
            scanf("%d",&choice);
        }
        if(choice <=0) return 0;
        rest_chose = r[choice-1];
        struct cart mycart;
        struct order_dish d[30];
        for(int i = 0;i<mycart.num_of_dishes;i++){
            mycart.dishes[i] = d[i];
        }
        mycart.restaurant = rest_chose;
        mycart.num_of_dishes = 0;
        mycart.price = 0;
        while(1){
            system("clear");
            int type_choice = -1;
            char type[10];
            printf("Choose type:\n1)Veg\n2)Non-Veg\n3)Jain\n4)See all\n5)Empty cart and go back to Restaurants\n6)View Cart\n");
            scanf("%d",&type_choice);
            while(type_choice<1 || type_choice>6){
                printf("Invalid choice, please enter again:");
                scanf("%d",&type_choice);
            }
            if(type_choice == 5) break;
            else if(type_choice == 1) strcpy(type,"Veg");
            else if(type_choice == 2) strcpy(type,"Non-Veg");
            else if(type_choice == 3) strcpy(type,"Jin");
            if(type_choice == 6){
                system("clear");
                if(mycart.num_of_dishes == 0) printf("Nothing in Cart yet\n");
                else{
                    int choice1;
                    printf("%s\n",mycart.restaurant.name);
                    printf("DISH | QUANTITY\n");
                    for(int j = 0;j<mycart.num_of_dishes;j++){
                        printf("%s | %d\n",mycart.dishes[j].dish.nameofdish,mycart.dishes[j].quantity);
                    }
                    float deliv_cost = 50 + mycart.restaurant.dist*4;
                    printf("Price: %.2f\n",(float)mycart.price);
                    printf("Delivery charges: %.2f\n",deliv_cost);
                    printf("Total Cost: %.2f\n",mycart.price + deliv_cost);
                    printf("1)Checkout\n2)Go Back\n");
                    scanf("%d",&choice1);
                    if(choice1 == 1){
                        float left = cust.mny - mycart.price - mycart.restaurant.dist*30;
                        if(left<0){
                            int dump;
                            printf("You don't have enough money for this transaction\nGo back to:\n1)Profile\n2)Menu\n");
                            scanf("%d",&dump);
                            if(dump == 1) return 0;
                        }
                        else{
                            FILE * ptr = fopen("num_of_delivs.txt","r");
                            int del_id;
                            char del_ids[5];
                            fscanf(ptr,"%d",&del_id);
                            fclose(ptr);
                            ptr = fopen("num_of_delivs.txt","w");
                            fprintf(ptr,"%d",del_id+1);
                            fclose(ptr);
                            ptr = fopen("num_of_delivs.txt","r");
                            fscanf(ptr,"%s",del_ids);
                            fclose(ptr);
                            while(strlen(del_ids)<4){
                                char temp[5] = "0";
                                strcat(temp,del_ids);
                                strcpy(del_ids,temp);
                            }
                            printf("%s %ld\n",del_ids,strlen(del_ids));
                            ptr = fopen("cust_order.txt","a");
                            fprintf(ptr,"not_assigned %s %s %s %s 0 %s %.2f %.2f\n", cust.nm, cust.ph, cust.ad, mycart.restaurant.address, del_ids, (float)mycart.price, deliv_cost);
                            fprintf(ptr,"%d\n",mycart.num_of_dishes);
                            for(int j = 0;j< mycart.num_of_dishes;j++){
                                fprintf(ptr,"%s %d\n",mycart.dishes[j].dish.nameofdish,mycart.dishes[j].quantity);
                            }
                            fclose(ptr);
                            printf("Order Placed. You have %.2f left in your account\n",left);
                            printf("Enter any number to go back to profile ");
                            scanf("%d",&choice1);
                            return mycart.price + deliv_cost;
                        }
                    }
                }
            }
            while(type_choice!=6){
                system("clear");
                int cat_choice;
                char cat[12];

                printf("%s\nChoose Category:\n1)Breakfast\n2)Maincourse\n3)Beverage\n4)Desserts\n5)Starters\n6)Fastfood\n7)See all\n8)Go back to types\n",rest_chose.name);
                scanf("%d",&cat_choice);
                while(cat_choice<1 || cat_choice>8){
                    printf("Invalid choice, please enter again:");
                    scanf("%d",&cat_choice);
                }
                if(cat_choice == 8) break;
                else if(cat_choice == 1) strcpy(cat,"Breakfast");
                else if(cat_choice == 2) strcpy(cat,"Maincourse");
                else if(cat_choice == 3) strcpy(cat,"Beverage");
                else if(cat_choice == 4) strcpy(cat,"Desserts");
                else if(cat_choice == 5) strcpy(cat,"Starters");
                else if(cat_choice == 6) strcpy(cat,"Fastfood");

                int dish_choice;
                int quantity;
                system("clear");
                for(int i = 0; i< rest_chose.num_dishes;i++){
                    if(strcmp(rest_chose.d[i].typeofdish,type) == 0 || type_choice == 4){
                        if(strcmp(rest_chose.d[i].categoryofdish,cat) == 0 || cat_choice == 7){
                            printf("%d)",i+1);
                            print_dish(rest_chose.d[i]);
                        }
                    }
                }
                printf("Enter dish choice number to add to cart(0 to go back):");
                scanf("%d",&dish_choice);
                if(dish_choice<1) break;
                while(dish_choice > rest_chose.num_dishes){
                    printf("Invalid Number please try again:");
                    scanf("%d",&dish_choice);
                }
                printf("Quantity:");
                scanf("%d",&quantity);
                while(quantity<1){
                    printf("Invalid quantity please try again:");
                    scanf("%d",&quantity);
                }
                int temp = 0;
                struct order_dish ord;
                

                for(int i = 0; i< rest_chose.num_dishes;i++){
                    if(strcmp(rest_chose.d[i].typeofdish,type) == 0 || type_choice == 4){
                        if(strcmp(rest_chose.d[i].categoryofdish,cat) == 0 || cat_choice == 7){
                            if(temp+1 == dish_choice){
                                ord.dish = rest_chose.d[i];
                                ord.quantity = quantity;
                                mycart.dishes[mycart.num_of_dishes] = ord;
                                mycart.num_of_dishes++;
                                mycart.price = mycart.price + quantity*atoi(rest_chose.d[i].priceofdish);
                            }
                            temp++;

                        }
                    }
                }
            }
        }
    }
}

