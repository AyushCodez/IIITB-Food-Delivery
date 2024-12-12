#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "delivery.h"

void login(char* cust_order, char* accept_file, char* delivered_file);

//CONVERTS a given int to Char*
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

//Coverts String to Int
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

//Heading creater
void heading(char title[]){ // heading
		printf("\t\t\t\t\t\t\t\t  :  : : :::%s",title);printf("::: : :  :\n");
		for(int i=0;i<173;i++) printf("_");
		printf("\n");
}

//Checks if a user is already exists in the file
int check_if_already_exists(char* input){
    FILE* f_ptr = fopen("deliv.txt","r");
    //printf("Hi\n");
    char name[20];
    char phone_num[10];
    char pswd[10];
    int User_id;
    while(fscanf(f_ptr,"%s %s %s %d", name, phone_num, pswd, &User_id) != EOF){//printf("HI\n");
        if(strcmp(input, name) == 0)
        {
            return 1;
        }
    }
    fclose(f_ptr);
    return 0;
}

//Gives the password of a given user
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

//Retrives the last user id inorder to generate new ones
int current_user_id(){
    FILE* fptr = fopen("deliv.txt","r");
    char name[20];
    char phone_num[10];
    char pswd[10];
    int User_id;
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

//Creates a new Profile
void create_profile(char* cust_order, char* accept_file, char* delivered_file){
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
    printf("Please enter your Password (Please donot use ' '(spaces) and maximum length 10): ");
    scanf("%s", Pwd);
    strcat(Pwd,"\0");
    if(check_if_already_exists(Username)){
        printf("Already Exists!! press any key to continue\n");
        char dummy;
        scanf("%c", &dummy);
        scanf("%c", &dummy);
        login(cust_order, accept_file, delivered_file);
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
    login(cust_order, accept_file, delivered_file);
}

//Show the incorrect login error
void login_Wrong(char* cust_order, char* accept_file, char* delivered_file){
    char Username[20];
    char Pwd[10];
    char option[10];
        system("clear");
    heading("Welcome to delivery page");
    printf("Wrong Password:\n\nPress 'Login' to login\nPress 'Create' to create new account: ");
    scanf("%s", option);
    printf("\n");
    if(strcmp(option,"create")==0||strcmp(option,"Create")==0||strcmp(option,"CREATE")==0){
        create_profile(cust_order, accept_file, delivered_file);
        return ;
    }
    else if(strcmp(option,"login")==0||strcmp(option,"Login")==0||strcmp(option,"LOGIN")==0){
        printf("Please enter your Name (Please donot use ' '(spaces) and maximum length 20): ");
        scanf("%s", Username);
        printf("\n");
        printf("Please enter your Password (Please donot use ' '(spaces) and maximum length 10): ");
        scanf("%s", Pwd);
        printf("\n");
        if(check_if_already_exists(Username)){
            if(strcmp(retrieve_password(Username), Pwd) == 0){ 
                printf("Logged in\n");//Owais's Function
                delivery_main(Username,cust_order, accept_file, delivered_file,0);
                return ;
            }
            else{
                login_Wrong(cust_order, accept_file, delivered_file);
                return ;
            }
        }
        else{
            printf("You are Not Registered, invalid Username!!\nPress any Key to continue: ");
            char dummy;
            scanf("%c", &dummy);
            scanf("%c", &dummy);
            printf("%c", dummy);
            login(cust_order, accept_file,  delivered_file);
        }
    }
    else{
        printf("Invalid Input\n\n");
        login(cust_order, accept_file, delivered_file);
    }    
}

//Shows the ogin UI
void login(char* cust_order, char* accept_file, char* delivered_file){
    char Username[20];
    char Pwd[10];
    char option[10];
        system("clear");
    heading("Welcome to delivery page");
    printf("Press 'Login' to login\nPress 'Create' to create new account: ");
    scanf("%s", option);
    printf("\n");
    if(strcmp(option,"create")==0||strcmp(option,"Create")==0||strcmp(option,"CREATE")==0){
        create_profile(cust_order, accept_file, delivered_file);
        return ;
    }
    else if(strcmp(option,"login")==0||strcmp(option,"Login")==0||strcmp(option,"LOGIN")==0){
        printf("Please enter your Name (Please donot use ' '(spaces) and maximum length 20): ");
        scanf("%s", Username);
        printf("\n");
        printf("Please enter your Password (Please donot use ' '(spaces) and maximum length 10): ");
        scanf("%s", Pwd);
        printf("\n");
        if(check_if_already_exists(Username)){
            if(strcmp(retrieve_password(Username), Pwd) == 0){ 
                printf("Logged in\n");//Owais's Function
                delivery_main(Username,cust_order, accept_file, delivered_file,0);
                return ;
            }
            else{
                login_Wrong(cust_order, accept_file, delivered_file);
                return ;
            }
        }
        else{
            printf("You are Not Registered, invalid Username!!\nPress any Key to continue: ");
            char dummy;
            scanf("%c", &dummy);
            scanf("%c", &dummy);
            printf("%c", dummy);
            login(cust_order, accept_file, delivered_file);
        }
    }
    else{
        printf("Invalid Input\n\n");
        login(cust_order, accept_file, delivered_file);
    }    
}


int main(void){
    char* cust_order = "cust_order.txt";
    char* accept_file = "accept_file.txt";
    char* delivered_file = "delivered_file.txt";
    login(cust_order, accept_file, delivered_file);
    return 0;
}
