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

typedef struct current_customer{
	char nm[21]; char ph[11]; char ad[201];
	char us[11]; char ps[11];
	double mny; // money
} cc;

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

void main_order(cc cust){
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
        //system("clear")
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
        if(choice <=0) break;
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
                if(mycart.num_of_dishes == 0) printf("Nothing in Cart yet\n");
                else{
                    int choice1;
                    printf("%s\n",mycart.restaurant.name);
                    printf("DISH | QUANTITY\n");
                    for(int j = 0;j<mycart.num_of_dishes;j++){
                        printf("%s | %d\n",mycart.dishes[j].dish.nameofdish,mycart.dishes[j].quantity);
                    }
                    printf("Price: %.2f\n",mycart.price);
                    printf("Delivery charges: %.2f\n",mycart.restaurant.dist*30);
                    printf("Total Cost: %.2f\n",mycart.price + mycart.restaurant.dist*30);
                    printf("1)Checkout\n2)Go Back\n");
                    scanf("%d",&choice1);
                    if(choice1 == 1){
                        int left = cust.mny < mycart.price - mycart.restaurant.dist*30;
                        if(left<0){
                            printf("You don't have enough money for this transaction\nPress Enter to go back to profile");
                            scanf("");
                        }
                    }
                }
            }
            while(type_choice!=6){
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
                for(int i = 0; i< rest_chose.num_dishes;i++){
                    if(strcmp(rest_chose.d[i].typeofdish,type) == 0 || type_choice == 4){
                        if(strcmp(rest_chose.d[i].categoryofdish,cat) == 0 || cat_choice == 7){
                            printf("%d)",i+1);
                            print_dish(rest_chose.d[i]);
                        }
                    }
                }
                printf("Enter dish choice number to add to cart:");
                scanf("%d",&dish_choice);
                while(dish_choice<1 || dish_choice > rest_chose.num_dishes){
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

void main(){
    cc c1;
	strcpy(c1.nm,"Ayush");
	strcpy(c1.ph,"1234567890");
	strcpy(c1.ad,"B227");
	strcpy(c1.us,"Ayush");
	strcpy(c1.ps,"abc");
	c1.mny=1000;
    main_order(c1);
}
