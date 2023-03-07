#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Dishes{
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
    int a=0;
    int flag=0;
    int*ptr=&flag;
    int*ptr1=&a;
    int cadd=0; //counter for no.of restaurants
    FILE *fptr;
    fptr = fopen("new_file", "r");
    struct rest r[100];
    for(int i  = 0;i<100;i++){
        fscanf(fptr,"%s",r[i].name);
        fscanf(fptr,"%s",r[i].address);
        fscanf(fptr,"%f",&r[i].dist);
        fscanf(fptr,"%s",r[i].contact);
        fscanf(fptr,"%d",&r[i].num_dishes);
        for(int j = 0;j < r[i].num_dishes;j++){
            fscanf(fptr,"%s %s %s %s",r[i].d[j].nameofdish, r[i].d[j].typeofdish,r[i].d[j].categoryofdish,r[i].d[j].priceofdish);
        }
    }
    fclose(fptr); 

    char input[100];
    printf("Enter 1 to add a restaurant \n");
    printf("Enter 2 to update the restaurant (except food details)\n");
    printf("Enter 3 to remove the restaurant\n");
    printf("Enter 4 to update the restaurant (only food details)\n");
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
            for(int j = 0;j < r[i].num_dishes;j++){
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
        r[cadd].num_dishes=0;
        printf("Name of the restaurant");
        scanf("%s",r[cadd].name);
        int flag=0;
        for(int i=0;i<cadd;i++){
            if (strcmp(r[cadd].name,r[i].name)==0){
                printf("Restaurant already exists\n");
                strcpy(r[cadd].name," ");
                flag=1;
            }
        }
        if (flag==0){
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
            scanf("%s",r[cadd].d[r[cadd].num_dishes].nameofdish); 
            printf("Enter following numbers for type of dish 1.Jain 2.Veg 3.Non-Veg");
            char in[10];
            scanf("%s",in);
            if (strcmp(in,"1")==0){
                strcpy(r[cadd].d[r[cadd].num_dishes].typeofdish,"Jain");
            }
            else if (strcmp(in,"2")==0){
                strcpy(r[cadd].d[r[cadd].num_dishes].typeofdish,"Veg");
            }
            else if (strcmp(in,"3")==0){
                strcpy(r[cadd].d[r[cadd].num_dishes].typeofdish,"Non-Veg");
            }
            else{
                printf("Invalid Input");
            }
            printf("Enter following numbers for category of dish 1.Breakfast 2.Maincourse 3.Beverage 4.Desserts 5.Starters 6.Fastfood");
            char jn[10];
            scanf("%s",jn);
            if (strcmp(in,"1")==0){
                strcpy(r[cadd].d[r[cadd].num_dishes].categoryofdish,"Breakfast");
            }
            else if (strcmp(in,"2")==0){
                strcpy(r[cadd].d[r[cadd].num_dishes].categoryofdish,"Maincourse");
            }
            else if (strcmp(in,"3")==0){
                strcpy(r[cadd].d[r[cadd].num_dishes].categoryofdish,"Beverage");
            }
            else if (strcmp(in,"4")==0){
                strcpy(r[cadd].d[r[cadd].num_dishes].categoryofdish,"Desserts");
            }
            else if (strcmp(in,"5")==0){
                strcpy(r[cadd].d[r[cadd].num_dishes].categoryofdish,"Starters");
            }
            else if (strcmp(in,"6")==0){
                strcpy(r[cadd].d[r[cadd].num_dishes].categoryofdish,"Fastfood");
            }
            else{
                printf("Invalid Input");
            }
            printf("Enter price of dish");
            scanf("%s",r[cadd].d[r[cadd].num_dishes].priceofdish);  
        }
        else{
            printf("Invalid Input\n");
        }
        }
        else if(flag==1){
            printf("These are the restaurants available \n");
            for (int i = 0; i < cadd; i++){
                printf("%s\n",r[i].name);
            }            
        }

    }
    else if (strcmp(input,"2")==0){ //to update restauarnt (except food details)
        fptr = fopen("new_file", "r");
        for(int i  = 0;i<100;i++){
            fscanf(fptr,"%s",r[i].name);
            fscanf(fptr,"%s",r[i].address);
            fscanf(fptr,"%f",&r[i].dist);
            fscanf(fptr,"%s",r[i].contact);
            fscanf(fptr,"%d", &r[i].num_dishes);
            for(int j = 0;j <r[i].num_dishes;j++){
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
        char restname[100];
        int flag=0;
        printf("Enter restaurant name\n");
        scanf("%s",restname);
        for(int i=0;i<cadd;i++){
            if (strcmp(restname,r[i].name)==0){
                printf("Enter new address\n");
                scanf("%s",r[i].address);
                printf("Enter new distance\n");
                scanf("%f",&r[i].dist);
                printf("Enter new contact\n");
                scanf("%s",r[i].contact);
                printf("Enter no.of dishes in the menu\n");
                scanf("%d",&r[i].num_dishes);
                flag=1;
                break;
            }
        }
        if (flag==0){
            printf("rest name don't match\n");
            printf("These are the restaurants available \n");
            for (int i = 0; i < cadd; i++){
                printf("%s\n",r[i].name);
            }
        }
    }
    else if (strcmp(input,"3")==0){ //to delete a restaurant
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
        char restname[100];
        printf("Enter restaurant name\n");
        scanf("%s",restname);
        for(int i=0;i<cadd;i++){
            if(strcmp(restname,r[i].name)==0){
                for(int j=i;j<cadd-1;j++){
                    r[j]=r[j+1];
                }
                cadd=cadd-1;
                *ptr=1;
                break;
            }
        }
        if (*ptr==0){
            printf("rest name don't match\n");
            printf("These are the restaurants available \n");
            for (int i = 0; i < cadd; i++){
                printf("%s\n",r[i].name);
            }
        }
    }
    else if (strcmp(input,"4")==0){ //to update restauarnt (only  food details)
        fptr = fopen("new_file", "r");
        for(int i  = 0;i<100;i++){
            fscanf(fptr,"%s",r[i].name);
            fscanf(fptr,"%s",r[i].address);
            fscanf(fptr,"%f",&r[i].dist);
            fscanf(fptr,"%s",r[i].contact);
            fscanf(fptr,"%d", &r[i].num_dishes);
            for(int j = 0;j <r[i].num_dishes;j++){
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
        char restname[100];
        int flag=0;
        printf("Enter restaurant name\n");
        scanf("%s",restname);
        for(int i=0;i<cadd;i++){
            if (strcmp(restname,r[i].name)==0){
                flag=1;
                char ln[10];
                printf("Enter 1 to add dish to the menu\n");
                printf("Enter 2 to update dish price in the menu\n");
                printf("Enter 3 to remove dish from the menu\n");
                printf("Enter exit to exit\n");
                scanf("%s",ln);
                if (strcmp(ln,"1")){
                    char dn[50];
                    printf("Enter dish name");
                    scanf("%s",dn);
                    strcpy(r[i].d[r[i].num_dishes].nameofdish,dn);
                    r[i].num_dishes+=1;
                }
                else if(strcmp(ln,"2")){
                    char dish[50];
                    printf("Enter dish name");
                    scanf("%s",dish);
                    int b=0;
                    for(int j=0;j<r[i].num_dishes;j++){
                        if (strcmp(dish,r[i].d[j].nameofdish)==0){
                            printf("Enter the new price\n");
                            scanf("%s",r[i].d[j].priceofdish);
                            b=1;
                            break;
                        }
                    }
                    if (b==0){
                        printf("dish name don't match\n");
                        printf("These are the dishes available in your restaurant\n");
                        for(int j=0;j<r[i].num_dishes;j++){
                            printf("%s\n",r[i].d[j].nameofdish);
                        }
                    }
                }
                else if(strcmp(ln,"3")){
                    char dis[50];
                    printf("Enter dish name");
                    scanf("%s",dis);
                    int a=0;
                    for(int j=0;j<r[i].num_dishes;j++){
                        if(strcmp(dis,r[i].d[j].nameofdish)==0){
                            for(int k=j;k<r[i].num_dishes-1;k++){
                                r[i].d[k]=r[i].d[k+1];
                            }
                            *ptr1=1;
                            r[i].num_dishes-=1;
                            break;
                        }
                    }
                    if(*ptr1==0){
                        printf("dish name don't match\n");
                        printf("These are the dishes available in your restaurant\n");
                        for(int j=0;j<r[i].num_dishes;j++){
                            printf("%s\n",r[i].d[j].nameofdish);
                        }
                    }
                }
            }
        } 
        if (flag==0){
            printf("rest name don't match\n");
            printf("These are the restaurants available \n");
            for (int i = 0; i < cadd; i++){
                printf("%s\n",r[i].name);
            }
        }
    }
    else{
        printf("Wrong Input\n");
    }
        for(int i=0;i<100;i++){
            if(strcmp(r[i].name,"") == 0){
                cadd = i; //counter for no.of restaurants
                break;
            }
        }
        if(strcmp(input,"3")==0 && *ptr==1) {
            cadd=cadd-1;
        }
        for(int i=0;i<100;i++){
            if(strcmp(r[cadd-1].d[i].nameofdish,"") == 0){
                r[cadd].num_dishes = i;
                break;
            }
        }
        fptr=fopen("new_file","w");
        for(int i=0;i<cadd;i++){
            fprintf(fptr,"%s\n%s\n%f\n%s\n%d\n",r[i].name,r[i].address,r[i].dist,r[i].contact,r[cadd].num_dishes);
            for(int j=0;j<r[cadd].num_dishes;j++){
                fprintf(fptr,"%s %s %s %s\n",r[i].d[j].nameofdish,r[i].d[j].typeofdish,r[i].d[j].categoryofdish,r[i].d[j].priceofdish);
            }
        }
        fclose(fptr);   
}