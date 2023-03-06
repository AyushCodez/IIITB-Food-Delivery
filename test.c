#include<stdio.h>
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
    int dist;
    char contact[10];
    int rating;
    int num_dishes;
    struct Dishes d[20];
};

int main(){
    
    FILE *infile = fopen("hotel.txt","r");
    FILE *fptr; 
    fptr = fopen("dish_file", "r");
    struct Dishes d[100];
	for(int i=0;i<100;i++){
		fscanf(fptr,"%s%s%s%s",d[i].nameofdish,d[i].typeofdish,d[i].categoryofdish,d[i].priceofdish);
	}
    fclose(fptr);
    struct rest all[10];
    for(int i  = 0;i<2;i++){
        fscanf(infile,"%s",all[i].name);
        fscanf(infile,"%s",all[i].address);
        fscanf(infile,"%d",&all[i].dist);
        fscanf(infile,"%s",all[i].contact);
        fscanf(infile,"%d",&all[i].rating);
        fscanf(infile,"%d", &all[i].num_dishes);
        for(int j = 0;j < all[i].num_dishes;j++){
            fscanf(infile,"%s %s %s %s",all[i].d[j].nameofdish, all[i].d[j].typeofdish,all[i].d[j].categoryofdish,all[i].d[j].priceofdish);
        }
    }
    fclose(infile);    
    for(int i = 0;i<2;i++){
        printf("%s\n",all[i].name);
        for(int j = 0;j<all[i].num_dishes;j++){
            printf("%s %s %s %s\n",all[i].d[j].nameofdish,all[i].d[j].priceofdish,all[i].d[j].priceofdish,all[i].d[j].priceofdish);
        }
    }
}






































