//Written by Sarvesh Kumar

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "restaurant_func.c"


void login();


char* int_to_char_converter(int n){
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
        //Takes the reminder and addis it to the last element of the list
        int reminder = copy % 10;
        str[str_size - i - 2] = (char)(reminder + (int)'0');
        copy = copy / 10;
    }
    str[str_size - 1] = '\0';
    return str;
}

int char_to_int(char* num_str){
    int n;
    int power = strlen(num_str) - 1;
    for(int i = 0; i < strlen(num_str); i++)
    {
        n = ((int)(*(num_str + i)) - (int)'0')*pow(10, power);
        power--;
    }
    return (int)n;
}

void heading(char title[]){ // heading
		printf("\t\t\t\t\t\t\t\t  :  : : :::%s",title);printf("::: : :  :\n");
		for(int i=0;i<173;i++) printf("_");
		printf("\n");
}

int check_if_aldready_exists(char* input){
    FILE* f_ptr = fopen("restiv.txt","r");
    FILE* f_ptr1 = fopen("lativ.txt","r");
    //printf("Hi\n");
    char name[20];
    char phone_num[11];
    char pswd[20];
    int User_id;
    char address[50];
    float dist; //enter in Km
    int num_dishes=0;
    while(fscanf(f_ptr, "%s %s %f %s %s %d %d", name, address,&dist,phone_num, pswd, &User_id,&num_dishes) != EOF){//printf("HI\n");
        if(strcmp(input, name) == 0)
        {
            //printf("HELLO\n");
            return 1;
        }
    }
    fclose(f_ptr);
    while(fscanf(f_ptr1, "%s %s %f %s %d", name, address,&dist,phone_num,&num_dishes) != EOF){//printf("HI\n");
        if(strcmp(input, name) == 0)
        {
            //printf("HELLO\n");
            return 1;
        }
    }
    fclose(f_ptr1);
    return 0;
}

char* retrieve_password(char* input){
    FILE* f_ptr = fopen("restiv.txt","r");
    FILE* f_ptr1 = fopen("lativ.txt","r");
    char* name; name = (char*)malloc(20);
    char phone_num[10];
    char* pswd = (char*)malloc(10);
    int User_id;
    char* address=(char*)malloc(50);
    float dist;
    int num_dishes=0;
    while(fscanf(f_ptr, "%s %s %f %s %s %d %d", name, address,&dist,phone_num, pswd, &User_id,&num_dishes) != EOF){
        if(strcmp(input, name) == 0)
        {
            fclose(f_ptr);
            return pswd;
        }
    }
    fclose(f_ptr);
    while(fscanf(f_ptr1, "%s %s %f %s %d", name, address,&dist,phone_num,&num_dishes) != EOF){
        if(strcmp(input, name) == 0)
        {
            fclose(f_ptr1);
            return pswd;
        }
    }
    fclose(f_ptr1);
    return NULL;
}

int current_user_id(){
    FILE* fptr = fopen("restiv.txt","r");
    FILE* fptr1 = fopen("lativ.txt","r");
    char name[20];
    char phone_num[10];
    char pswd[10];
    int User_id;
    char address[50];
    float dist;
    int num_dishes=0;
    //previous_values;
    char prev_name[20];
    char prev_phone_num[10];
    char prev_pswd[10];
    int prev_id;
    char prev_address[50];
    float prev_dist;
    int prev_num_dishes=0;
    while(fscanf(fptr, "%s %s %f %s %s %d %d", name, address,&dist,phone_num, pswd, &User_id,&num_dishes) != EOF){
        strcpy(name,prev_name);strcpy(phone_num,prev_phone_num);strcpy(pswd, prev_pswd); prev_id = User_id;strcpy(address,prev_address);prev_dist=dist;prev_num_dishes=num_dishes;
    }
    fclose(fptr);
    while(fscanf(fptr1, "%s %s %f %s %d", name, address,&dist,phone_num,&num_dishes) != EOF){
        strcpy(name,prev_name);strcpy(phone_num,prev_phone_num);strcpy(pswd, prev_pswd); prev_id = User_id;strcpy(address,prev_address);prev_dist=dist;prev_num_dishes=num_dishes;
    }
    fclose(fptr1);
    return prev_id;
}

void create_profile(){
    char Username[20];
    char Phone_number[11];
    char Pwd[10];
    char Address[50];
    float Dist;
    int num_dishes=0;
    system("clear");
    heading("CREATE_PROFILE");
    printf("Please enter your Restaurant Name (Please donot use ' '(spaces) and maximum length 20): ");
    scanf("%s", Username);
    strcat(Username,"\0");

    printf("Please enter your Phone Number: ");
    scanf("%s", Phone_number);
    strcat(Phone_number,"\0");

    while(strlen(Phone_number) != 10){
        printf("Please enter a valid phone number: ");
        scanf("%s", Phone_number);
        strcat(Phone_number,"\0");
    }
    printf("Please enter your Password (Please do not use ' '(spaces) and maximum length 10): ");
    scanf("%s", Pwd);
    strcat(Pwd,"\0");
    printf("Please enter your address: ");
    scanf("%s",Address);
    strcat(Address,"\0");
    printf("Please enter your distance from IITB: ");
    scanf("%f",&Dist);
    if(check_if_aldready_exists(Username)){
        printf("Already Exists!! press any key to continue\n");
        char dummy;
        scanf("%c", &dummy);
        scanf("%c", &dummy);
        login();
        return ;
    }

    int U_id = current_user_id() + 1;

    FILE* f_ptr = fopen("restiv.txt","a");
    FILE* f_ptr1 = fopen("lativ.txt","a");
    fprintf(f_ptr, "%s\n%s\n%f\n%s\n%s\n%d\n%d\n", Username, Address, Dist,Phone_number,Pwd,U_id,num_dishes);
    fprintf(f_ptr1, "%s\n%s\n%f\n%s\n%d\n", Username, Address, Dist,Phone_number,num_dishes);
    fclose(f_ptr);
    fclose(f_ptr1);
    printf("Thank You for Joining our Team!!\npress any key to continue: ");
    char dummy;
    scanf("%c", &dummy);
    scanf("%c", &dummy);
    login();
}

void login_Wrong(){
    char Username[20];
    char Pwd[10];
    char option[10];
        system("clear");
    heading("Welcome to Restauarnt Owner page");
    printf("Wrong Password:\n\nPress 'Login' to login\nPress 'Create' to create new account: ");
    scanf("%s", option);
    printf("\n");
    if(strcmp(option,"create")==0||strcmp(option,"Create")==0||strcmp(option,"CREATE")==0){
        create_profile();
        return ;
    }
    else if(strcmp(option,"login")==0||strcmp(option,"Login")==0||strcmp(option,"LOGIN")==0){
        printf("Please enter your Restaurant Name (Please donot use ' '(spaces) and maximum length 20): ");
        scanf("%s", Username);
        printf("\n");
        printf("Please enter your Password (Please donot use ' '(spaces) and maximum length 10): ");
        scanf("%s", Pwd);
        printf("\n");
        if(check_if_aldready_exists(Username)){
            if(strcmp(retrieve_password(Username), Pwd) == 0){ 
                printf("Logged in\n");
                return ;
            }
            else{
                login_Wrong();
                return ;
            }
        }
        else{
            printf("You are Not Registered, invalid Username!!\nPress any Key to continue: ");
            char dummy;
            scanf("%c", &dummy);
            scanf("%c", &dummy);
            printf("%c", dummy);
            login();
        }
    }
    else{
        printf("Invalid Input\n\n");
        login();
    }    
}

void login(){
    char Username[20];
    char Pwd[10];
    char option[10];
        system("clear");
    heading("Welcome to Restaurant Owner page");
    printf("Press 'Login' to login\nPress 'Create' to create new account: ");
    scanf("%s", option);
    printf("\n");
    if(strcmp(option,"create")==0||strcmp(option,"Create")==0||strcmp(option,"CREATE")==0){
        create_profile();
        return ;
    }
    else if(strcmp(option,"login")==0||strcmp(option,"Login")==0||strcmp(option,"LOGIN")==0){
        printf("Please enter your Restauarnt Name (Please do not use ' '(spaces) and maximum length 20): ");
        scanf("%s", Username);
        printf("\n");
        printf("Please enter your Password (Please do not use ' '(spaces) and maximum length 10): ");
        scanf("%s", Pwd);
        printf("\n");
        if(check_if_aldready_exists(Username)){
            if(strcmp(retrieve_password(Username), Pwd) == 0){ 
                printf("Logged in\n");
                system("clear");
                int input;
                char resname[50];
                strcpy(resname,Username);
                while(1){
                    printf("Enter:\n1)Add Dish\n2)Update restaurant\n3)Remove Dish\n4)Exit");
                    scanf("%d",&input);
                    while(input<1 || input>4){
                        printf("Invalid input, Please enter again: ");
                        scanf("%d",&input);
                    }
                    if (input == 1){
                        add_dish(resname);
                    }
                    else if(input == 2){
                        update_restaurant(resname);
                    }
                    else if(input == 3){
                        remove_dish(resname);
                    }
                    else if(input == 4){
                        return;
                    }
                }
            }
            else{
                login_Wrong();
                return ;
            }
        }
        else{
            printf("You are Not Registered, invalid Username!!\nPress any Key to continue: ");
            char dummy;
            scanf("%c", &dummy);
            scanf("%c", &dummy);
            login();
        }
    }
    else{
        printf("Invalid Input\n\n");
        login();
    }    
}

int main(void){
    login();
    return 0;
}