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
    for(int i  = 0;i<100;i++){
        fscanf(fptr,"%s",r[i].name);
        fscanf(fptr,"%s",r[i].address);
        fscanf(fptr,"%f",&r[i].dist);
        fscanf(fptr,"%s",r[i].contact);
        fscanf(fptr,"%d", &r[i].num_dishes);
        for(int j = 0;j < r[i].num_dishes;j++){
            fscanf(fptr,"%s %s %s %s",r[i].d[j].nameofdish, r[i].d[j].typeofdish,r[i].d[j].categoryofdish,r[i].d[j].priceofdish);
        }
    }
    fclose(fptr); 

    char input[100];
    printf("Enter 1 to add a restaurant \n");
    printf("Enter 2 to update the restaurant\n");
    printf("Enter 3 to remove the restaurant\n");
    printf("Enter exit to exit\n");
    scanf("%s",input);

    if (strcmp(input,"exit")==0){
        printf("EXIT\n");
    }
    else if (strcmp(input,"1")==0){
        fptr = fopen("new_file", "r");
        for(int i  = 0;i<100;i++){
            fscanf(fptr,"%s",r[i].name);
            fscanf(fptr,"%s",r[i].address);
            fscanf(fptr,"%f",&r[i].dist);
            fscanf(fptr,"%s",r[i].contact);
            fscanf(fptr,"%d", &r[i].num_dishes);
            for(int j = 0;j < 1;j++){
                fscanf(fptr,"%s %s %s %s",r[i].d[j].nameofdish, r[i].d[j].typeofdish,r[i].d[j].categoryofdish,r[i].d[j].priceofdish);
            }
        }
        fclose(fptr);
        for(int i=0;i<100;i++){
            if(strcmp(r[i].name,"") == 0){
                cadd = i; //counter for no.of restaurants
                break;
            }
        }
        counter=0;
        printf("Name of the restaurant");
        scanf("%s",r[cadd].name);
        printf("Address of the restaurant");
        scanf("%s",r[cadd].address);
        printf("Distance of the restaurant from IIITB(enter in km)");
        scanf("%f",&r[cadd].dist);
        printf("Contact of restaurant");
        scanf("%s",r[cadd].contact);
        //printf("Enter no.of dishes in the menu");
        //scanf("%d",&r[cadd].num_dishes);
        char inp[10];
        printf("Enter 1 to add dish to the menu\n");
        printf("Enter exit to exit\n");
        scanf("%s",inp);
        if (strcmp(inp,"exit")==0){
            printf("EXIT\n");
        }
        else if (strcmp(inp,"1")==0){
            fptr = fopen("new_file", "r");
            for(int i  = 0;i<100;i++){
                fscanf(fptr,"%s",r[i].name);
                fscanf(fptr,"%s",r[i].address);
                fscanf(fptr,"%f",&r[i].dist);
                fscanf(fptr,"%s",r[i].contact);
                fscanf(fptr,"%d", &r[i].num_dishes);
                for(int j = 0;j < r[i].num_dishes;j++){
                    fscanf(fptr,"%s %s %s %s",r[i].d[j].nameofdish, r[i].d[j].typeofdish,r[i].d[j].categoryofdish,r[i].d[j].priceofdish);
                }
            }
            fclose(fptr);
            printf("Name of the dish");
            scanf("%s",r[cadd].d[counter].nameofdish); 
            printf("Enter type of dish(veg/non-veg)");
            scanf("%s",r[cadd].d[counter].typeofdish);
            printf("Enter category of dish (beverage/fastfood/desserts/maincourse/breakfast....)");
            scanf("%s",r[cadd].d[counter].categoryofdish);
            printf("Enter price of dish");
            scanf("%s",r[cadd].d[counter].priceofdish);  
        }
    }
        for(int i=0;i<100;i++){
            if(strcmp(r[i].name,"") == 0){
                cadd = i; //counter for no.of restaurants
                break;
            }
        }
        for(int i=0;i<100;i++){
            if(strcmp(r[cadd-1].d[i].nameofdish,"") == 0){
                counter = i;
                break;
            }
        }
        fptr=fopen("new_file","w");
        for(int i=0;i<cadd;i++){
            fprintf(fptr,"%s\n%s\n%f\n%s\n%d\n",r[i].name,r[i].address,r[i].dist,r[i].contact,counter);
            for(int j=0;j<counter;j++){
                fprintf(fptr,"%s %s %s %s\n",r[i].d[j].nameofdish,r[i].d[j].typeofdish,r[i].d[j].categoryofdish,r[i].d[j].priceofdish);
            }
        }
        fclose(fptr);   
}