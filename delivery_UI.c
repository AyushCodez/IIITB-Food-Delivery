#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "delivery.h"

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
		printf("\t\t\t\t\t\t\t\t\t\t\t:  : : :::%s",title);printf("::: : :  :\n");
		for(int i=0;i<210;i++) printf("_");
		printf("\n");
}

int check_if_aldready_exists(char* input){
    FILE* f_ptr = fopen("deliv.txt","r");
    //printf("Hi\n");
    char name[20];
    char phone_num[10];
    char pswd[10];
    int User_id;
    while(fscanf(f_ptr,"%s %s %s %d", name, phone_num, pswd, &User_id) != EOF){//printf("HI\n");
        if(strcmp(input, name) == 0)
        {
            //printf("HELLO\n");
            return 1;
        }
    }
    fclose(f_ptr);
    return 0;
}

char* retrieve_password(char* input){
    FILE* f_ptr = fopen("deliv.txt","r");
    char* name; name = (char*)malloc(20);
    char phone_num[10];
    char* pswd = (char*)malloc(10);
    int User_id;
    while(fscanf(f_ptr, "%s %s %s %d", name, phone_num, pswd, &User_id) != EOF){
        if(strcmp(input, name) == 0)
        {
            fclose(f_ptr);
            return pswd;
        }
    }
    fclose(f_ptr);
    return NULL;
}

int current_user_id(){
    FILE* fptr = fopen("deliv.txt","r");
    char name[20];
    char phone_num[10];
    char pswd[10];
    int User_id;
    //previous_values;
    char prev_name[20];
    char prev_phone_num[10];
    char prev_pswd[10];
    int prev_id;

    while(fscanf(fptr, "%s %s %s %d", name, phone_num, pswd, &User_id) != EOF){
        strcpy(name,prev_name);strcpy(phone_num,prev_phone_num);strcpy(pswd, prev_pswd); prev_id = User_id;
    }
    fclose(fptr);
    return prev_id;
}

void create_profile(){
    char Username[20];
    char Phone_number[11];
    char Pwd[10];
    system("clear");
    heading("CREATE_PROFILE");
    printf("Please enter your Name (Please donot use ' '(spaces) and maximum length 20): ");
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
    printf("%s\n", Phone_number);
    printf("Please enter your Password (Please donot use ' '(spaces) and maximum length 10): ");
    scanf("%s", Pwd);
    strcat(Pwd,"\0");
    printf("%s\n", Phone_number);
    if(check_if_aldready_exists(Username)){
        printf("Aldready Exists!! press any key to continue\n");
        char dummy;
        scanf("%c", &dummy);
        scanf("%c", &dummy);
        login();
        return ;
    }

    int U_id = current_user_id() + 1;

    FILE* f_ptr = fopen("deliv.txt","a");
    fprintf(f_ptr, "%s %s %s %d\n", Username, Phone_number, Pwd, U_id);
    fclose(f_ptr);
    printf("Thank You for Joining our Team!!\npress any key to continue: ");
    char dummy;
    scanf("%c", &dummy);
    scanf("%c", &dummy);
    login();
}

void login_Wrong(){
    char Username[20];
    char Pwd[10];
    char option;
        system("clear");
    heading("Welcome to delivery page");
    printf("Wrong Password - Press 'l' to login OR Press 'c' to create new account: ");
    scanf("%c", &option);
    if(option == 'c'){
        create_profile();
        return ;
    }
    else if(option == 'l'){
        printf("Please enter your Name (Please donot use ' '(spaces) and maximum length 20): ");
        scanf("%s", Username);
        printf("\n");
        printf("Please enter your Password (Please donot use ' '(spaces) and maximum length 10): ");
        scanf("%s", Pwd);
        printf("\n");
        if(check_if_aldready_exists(Username)){
            if(strcmp(retrieve_password(Username), Pwd) == 0){ 
                printf("Logged in\n");//Owais's Function

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
        printf("Invalid Input");
        login();
    }    
}

void login(){
    char Username[20];
    char Pwd[10];
    char option;
        system("clear");
    heading("Welcome to delivery page");
    printf("Press 'l' to login OR Press 'c' to create new account: ");
    scanf("%c", &option);
    if(option == 'c'){
        create_profile();
        return ;
    }
    else if(option == 'l'){
        printf("Please enter your Name (Please donot use ' '(spaces) and maximum length 20): ");
        scanf("%s", Username);
        printf("\n");
        printf("Please enter your Password (Please donot use ' '(spaces) and maximum length 10): ");
        scanf("%s", Pwd);
        printf("\n");
        if(check_if_aldready_exists(Username)){
            if(strcmp(retrieve_password(Username), Pwd) == 0){ 
                printf("Logged in\n");//Owais's Function
                delivery_main(Username);
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
        printf("Invalid Input");
        login();
    }    
}


int main(void){
    login();
    return 0;
}
