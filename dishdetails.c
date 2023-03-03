//This is the code after you login into your restaurant
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Dishes
{
    char nameofdish[30]; 
    char typeofdish[20]; //whether it is a softdrink / fastfood / beverage / bread / gravy ....
    char categoryofdish[20]; //whether it is veg/non-veg/jain
    char priceofdish[10];
};

int main(){
    FILE *fptr; 
    int cadd=0; //Acts as a counter to keep track of the length of the array
	fptr = fopen("dish_file", "r");
    struct Dishes d[100];
	for(int i=0;i<100;i++){
		fscanf(fptr,"%s%s%s%s",d[i].nameofdish,d[i].typeofdish,d[i].categoryofdish,d[i].priceofdish);
	}
    fclose(fptr);
    char input[10];
    printf("Enter 1 to add dish to the menu\n");
    printf("Enter 2 to update dish price in the menu\n");
    printf("Enter 3 to remove dish from the menu\n");
    printf("Enter exit to exit\n");
    scanf("%s",input);
    if (strcmp(input,"exit")==0){
        printf("EXIT\n");
    }
    else if (strcmp(input,"1")==0){ //add dish to the menu
        fptr = fopen("dish_file", "r");
        for(int i=0;i<100;i++){
            fscanf(fptr,"%s%s%s%s",d[i].nameofdish,d[i].typeofdish,d[i].categoryofdish,d[i].priceofdish);
        }
        for(int i=0;i<100;i++){
            if(strcmp(d[i].nameofdish,"") == 0){
                cadd = i;
                break;
            }
        }
        //printf("%d\n",cadd);
        fclose(fptr);
        printf("Name of the dish");
        scanf("%s",d[cadd].nameofdish);
        printf("Type of the dish");
        scanf("%s",d[cadd].typeofdish);
        printf("Category of the dish");
        scanf("%s",d[cadd].categoryofdish);
        printf("Price of the dish");
        scanf("%s",d[cadd].priceofdish);
    }
    else if(strcmp(input,"2")==0){ //update dish price in the menu
        fptr = fopen("dish_file", "r");
        for(int i=0;i<100;i++){
            fscanf(fptr,"%s%s%s%s",d[i].nameofdish,d[i].typeofdish,d[i].categoryofdish,d[i].priceofdish);
        }
        for(int i=0;i<100;i++){
            if(strcmp(d[i].nameofdish,"") == 0){
                cadd = i;
                break;
            }
        }
        fclose(fptr);
        char dishname[100];
        int flag=0;
        printf("Enter dish name\n");
        scanf("%s",dishname);
        for(int i=0;i<cadd;i++){
            if (strcmp(dishname,d[i].nameofdish)==0){
                printf("Enter the new price\n");
                scanf("%s",d[i].priceofdish);
                flag=1;
                break;
            }
        }
        if (flag==0){
            printf("dish name don't match\n");
            printf("These are the dishes available in your restaurant\n");
            for (int i = 0; i < cadd; i++){
                printf("%s\n",d[i].nameofdish);
            }
        }
    }
    else if(strcmp(input,"3")==0){ //remove dish from the menu
        fptr = fopen("dish_file", "r");
        for(int i=0;i<100;i++){
            fscanf(fptr,"%s%s%s%s",d[i].nameofdish,d[i].typeofdish,d[i].categoryofdish,d[i].priceofdish);
        }
        for(int i=0;i<100;i++){
            if(strcmp(d[i].nameofdish,"") == 0){
                cadd = i;
                break;
            }
        }
        fclose(fptr);
        char dishname[100];
        int flag=0;
        printf("Enter dish name\n");
        scanf("%s",dishname);
        for(int i=0;i<cadd;i++){
            if(strcmp(dishname,d[i].nameofdish)==0){
                for(int j=i;j<cadd-1;j++){
                    d[j]=d[j+1];
                }
                cadd=cadd-1;
                flag=1;
                break;
            }
        }
        if (flag==0){
            printf("dish name don't match\n");
            printf("These are the dishes available in your restaurant\n");
            for (int i = 0; i < cadd; i++){
                printf("%s\n",d[i].nameofdish);
            }
        }
    }
    for(int i=0;i<100;i++){
        if(strcmp(d[i].nameofdish,"") == 0){
            cadd = i;
            break;
        }
    }
    fptr=fopen("dish_file","w");
    for(int i=0;i<cadd;i++){
        fprintf(fptr,"%s %s %s %s\n",d[i].nameofdish,d[i].categoryofdish,d[i].typeofdish,d[i].priceofdish);
    }
    fclose(fptr);
}