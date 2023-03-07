#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define rest_file "restraunt.txt"

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

struct rest* extract(){
    FILE *fptr;
    fptr = fopen(rest_file, "r");
    struct rest* r; r = (struct rest*) malloc(100*sizeof(struct rest));
    int i = 0;
    while(fscanf(fptr,"%s %s %f %s %d",r[i].name, r[i].address, &r[i].dist, r[i].contact, &r[i].num_dishes)!=EOF){
        /*fscanf(fptr,"%s",r[i].address);
        fscanf(fptr,"%f",&r[i].dist);
        fscanf(fptr,"%s",r[i].contact);
        fscanf(fptr,"%d", &r[i].num_dishes);*/
        for(int j = 0;j < r[i].num_dishes;j++){
            fscanf(fptr,"%s %s %s %s",r[i].d[j].nameofdish, r[i].d[j].typeofdish,r[i].d[j].categoryofdish,r[i].d[j].priceofdish);
        }
        i++;
    }
    fclose(fptr);
    return r;
}

void add_dish(char* Rest_name){
    char name[30];
    char type[20];
    char category[20];
    char price[10];
    int option;
    printf("Please enter Name of the dish: ");
    scanf("%s", name);
    printf("Please enter '1' for Jain, '2' for Veg, '3' for Non-Veg : ");
    while(1){
        scanf("%d", &option);
        if(option == 1){strcpy(type, "Jain"); break;}
        else if(option == 2){strcpy(type, "Veg"); break;}
        else if(option == 3){strcpy(type, "Non-Veg"); break;}
        else{printf("Please enter a valid option\n Enter Value: ");}
    }
    printf("Please enter '1' for Breakfast, '2' for Maincourse, '3' for Beverages, '4' for Desserts, '5' for Starters and '6' for Fastfoods : ");
    while(1){
        scanf("%d", &option);
        if(option == 1){strcpy(type, "Breakfast"); break;}
        else if(option == 2){strcpy(category, "Maincourses"); break;}
        else if(option == 3){strcpy(category, "Beverages"); break;}
        else if(option == 4){strcpy(category, "Desserts"); break;}
        else if(option == 5){strcpy(category, "Starters"); break;}
        else if(option == 6){strcpy(category, "Fastfoods"); break;}
        else{printf("Please enter a valid option\n");}
    }
    printf("Please enter the price: ");
    scanf("%s", price);
    FILE *fptr;
    fptr = fopen(rest_file, "r");
    struct rest* r; r = (struct rest*) malloc(100*sizeof(struct rest));
    int i = 0;
    while(fscanf(fptr,"%s %s %f %s %d",r[i].name, r[i].address, &r[i].dist, r[i].contact, &r[i].num_dishes)!=EOF){
        for(int j = 0;j < r[i].num_dishes;j++){
            fscanf(fptr,"%s %s %s %s",r[i].d[j].nameofdish, r[i].d[j].typeofdish,r[i].d[j].categoryofdish,r[i].d[j].priceofdish);
        }
        i++;
    }
    fclose(fptr);
    for(int j = 0; j < i; j++){
            if(strcmp(Rest_name, r[j].name) == 0){
                if(r[j].num_dishes >= 20){printf("MAX DISHES REACHED\n"); return ;}
                else{
                    strcpy(r[j].d[r[j].num_dishes].nameofdish, name);
                    strcpy(r[j].d[r[j].num_dishes].typeofdish, type);
                    strcpy(r[j].d[r[j].num_dishes].categoryofdish, category);
                    strcpy(r[j].d[r[j].num_dishes].priceofdish, price);
                    printf("DISH ADDED!!\n");
                    r[j].num_dishes ++;
                }
                break;
            }
    }

    /*FILE *f_ptr = fopen(rest_file, "w");
    for(int j = 0; j < i; j++){
        fprintf(f_ptr,"%s\n%s\n%.2f\n%s\n%d",r[i].name, r[i].address, r[i].dist, r[i].contact, r[i].num_dishes);
        for(int k = 0; k < r[i].num_dishes; k++){
            fprintf(f_ptr, "%s %s %s %s", r[i].d[j].nameofdish, r[i].d[j].typeofdish,r[i].d[j].categoryofdish,r[i].d[j].priceofdish);
        }
    }
    fclose(f_ptr);*/

    fptr=fopen(rest_file,"w");
        for(int k=0;k<i;k++){
            fprintf(fptr,"%s\n%s\n%f\n%s\n%d\n",r[k].name,r[k].address,r[k].dist,r[k].contact,r[k].num_dishes);
            for(int j=0;j<r[k].num_dishes;j++){
                fprintf(fptr,"%s %s %s %s\n",r[k].d[j].nameofdish,r[k].d[j].typeofdish,r[k].d[j].categoryofdish,r[k].d[j].priceofdish);
            }
        }

}

void remove_dish(char* Rest_name){
    char name[30];
    printf("Please enter the name of the Dish you wish to remove: ");
    scanf("%s", name);
    FILE *fptr;
    fptr = fopen(rest_file, "r");
    struct rest* r; r = (struct rest*) malloc(100*sizeof(struct rest));
    int i = 0;
    while(fscanf(fptr,"%s %s %f %s %d",r[i].name, r[i].address, &r[i].dist, r[i].contact, &r[i].num_dishes)!=EOF){
        /*fscanf(fptr,"%s",r[i].address);
        fscanf(fptr,"%f",&r[i].dist);
        fscanf(fptr,"%s",r[i].contact);
        fscanf(fptr,"%d", &r[i].num_dishes);*/
        for(int j = 0;j < r[i].num_dishes;j++){
            fscanf(fptr,"%s %s %s %s",r[i].d[j].nameofdish, r[i].d[j].typeofdish,r[i].d[j].categoryofdish,r[i].d[j].priceofdish);
        }
        i++;
    }
    fclose(fptr);
    int found = 0;
    for(int j = 0; j < i; j++){
            if(strcmp(Rest_name, r[j].name) == 0){
                int k = 0;
                for(; k < r[j].num_dishes; k++){
                    if(strcmp(r[j].d[k].nameofdish, name) == 0){
                        for(int l = k; l < r[j].num_dishes - 1 ; k++)
                        {
                            strcpy(r[j].d[l].nameofdish, r[j].d[l + 1].nameofdish);
                            strcpy(r[j].d[l].typeofdish, r[j].d[l + 1].typeofdish);
                            strcpy(r[j].d[l].categoryofdish, r[j].d[l + 1].categoryofdish);
                            strcpy(r[j].d[l].priceofdish, r[j].d[l + 1].priceofdish);
                        }
                        r[j].num_dishes --;
                        found = 1;
                        printf("ITEM DELETED\n");
                        break;
                    }
                }
                if(found == 0){printf("Dish not present!!\n");}
                break;
            }
    }

    /*FILE *f_ptr = fopen(rest_file, "w");
    for(int j = 0; j < i; j++){
        fprintf(f_ptr,"%s\n%s\n%f\n%s\n%d",r[i].name, r[i].address, r[i].dist, r[i].contact, r[i].num_dishes);
        for(int k = 0; k < r[i].num_dishes; k++){
            fprintf(f_ptr, "%s %s %s %s", r[i].d[j].nameofdish, r[i].d[j].typeofdish,r[i].d[j].categoryofdish,r[i].d[j].priceofdish);
        }
    }*/

    fptr=fopen(rest_file,"w");
        for(int k=0;k<i;k++){
            fprintf(fptr,"%s\n%s\n%f\n%s\n%d\n",r[k].name,r[k].address,r[k].dist,r[k].contact,r[k].num_dishes);
            for(int j=0;j<r[k].num_dishes;j++){
                fprintf(fptr,"%s %s %s %s\n",r[k].d[j].nameofdish,r[k].d[j].typeofdish,r[k].d[j].categoryofdish,r[k].d[j].priceofdish);
            }
        }

}

int main(void){
    char restraunt[20];
    scanf("%s",restraunt);
    remove_dish(restraunt);
    return 0;
}