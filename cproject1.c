#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Dishes
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
    struct Dishes d[20];
};

int main(){
    int cadd=0; //counter for no.of restaurants
    int counter=0; //counter for no.of dishes 
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
    printf("%d\n",i);
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
        while(1){
            int choice;
            printf("Choose type:\n1)veg\n2)non-veg\n3)jain\n4)all\n5)Empty cart and go back to Restaurants\n");
            scanf("%d",&choice);
            if(choice == 5) break;
        }
        
    }
}
