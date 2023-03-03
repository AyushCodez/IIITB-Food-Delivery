#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define rest_det "rest_det.txt" // MACRO for file ctmr.txt which contains restaurant owner details in format <username> <password> <name> <address> <phone> <money_in_wallet>
char current_rest[261];
struct logged_in_rest{ // details of the current restaurat onwer----------
	char usernam[10]; char pass[10];
	char name[20]; char address[200];
	long ph; double money;
};//----------------
int check_ph_num(char ph[]){ // returns 1 if ph is valid 10 digit phone number else 0
	if(strlen(ph)!=10) return 0;
	for(int i=0;i<10;i++)
		if(ph[i]<48 || ph[i]>57) return 0;
	return 1;
}

int check_usrnm_pass(char line[100], char pu[21]){ // to check if <password username> is present in the line
		long len=strlen(pu);
		for(int i=0;i<len;i++)
			if(pu[i]!=line[i]) return 0;
		return 1;
	}
void heading(char title[20]){ // heading
		printf("\t\t\t\t\t\t\t\t\t\t\t:  : : :::%s",title);printf("::: : :  :\n)");
		for(int i=0;i<210;i++) printf("_");
		printf("\n");
	}
int profile(char line[]){
		system("clear");
		heading("<<< PROFILE >>>");
		char* name,* username;
		username=strtok(line,"%");
		strtok(NULL,"%");
		name=strtok(NULL,"%");
		printf("\t\t\t\t\t\t\t\t\t\t\t      >>> Welcome %s",name);printf(" <<<\n\n");
		printf("\t\t\t\t\t\t\t\t\t\t\t         Username: %s\n",username);
		printf("\t\t\t\t\t\t\t\t\t\t\t         Address: %s\n",strtok(NULL,"%"));
		printf("\t\t\t\t\t\t\t\t\t\t\t         Phone: %s\n",strtok(NULL,"%"));
		printf("\t\t\t\t\t\t\t\t\t\t\t         Wallet Balance: %s\n",strtok(NULL,"%"));
		return 0;
	}
char pre_msg_mainpage[40]="nil";
int username_pass(char * pre_msg); char pre_msg_lgn[50]="nil"; // pre_msg_lgn --> message that has to be displeyed just after login hedaing
int sign_up(); char pre_msg_sgnup[25]="nil"; // resp_sgnup --> message to be displayed just after signup heading
char pre_msg_updtprof[25]="nil";
int username_pass(char * pre_msg){
		char response[]="Account not found. Wrong username or password";
		char sgnup[]="s";
		char ext[]="e";
		//--------------
		char usrnm[21]; // max length of username restricted to 10, space has 1, and 10 for password
		char pass[10]; // max length of password restricted to 10
		char row[100]; // row that is read from the restaurant onwer details file
		//--------------
		char delimiter[] = "%";
		system("clear");
		heading("LOGIN");
		if(strcmp(pre_msg,"nil")!=0){
		printf("\t\t\t\t\t\t\t\t\t\t%s\n",pre_msg); // pre message
		for(int i=0;i<210;i++) printf("-");
		printf("\n");
		}
		printf("\t\t\t\t\t\t\t\t\t\ts: Dont have an account? Sign up now:\n");
		printf("\t\t\t\t\t\t\t\t\t\t\t Username:"); scanf("%s",usrnm);
		if(strcmp(usrnm,sgnup)==0){
			int show_sign_up=0; // if 0 then take to signup page
		       	while(show_sign_up==0)
				show_sign_up=sign_up();

			return 1;
		}
		if(strcmp(usrnm,ext)==0) exit(0);
		printf("\t\t\t\t\t\t\t\t\t\t\t Password:"); scanf("%s",pass);
		strcat(usrnm,delimiter);
		strcat(usrnm,pass);
		FILE * ptr=fopen(rest_det,"r");
		while(fgets(row,100,ptr)!=NULL)
			if(check_usrnm_pass(row,usrnm)==1){
				fclose(ptr);
				strcpy(current_rest,row);
				return 0;
				};
		
		fclose(ptr);
		strcpy(pre_msg_lgn,response);
		return 1;
	}	
int sign_up(){
		system("clear");
		heading("SIGN-UP");
		int reask_ph=1;
		char resp_sgnup[25]="Invalid Phone Number";
		char name[20];char ph[10];char us[261];char ps[10];char address[200];char money[]="0.0"; char new_line[]="\n";char delimiter[]="%";
		if(strcmp(pre_msg_sgnup,"nil")!=0){
			printf("\t\t\t\t\t\t\t\t\t\t\t   %s\n",pre_msg_sgnup);
			for(int i=0;i<210;i++) printf("-");
			printf("\n");
		}
		printf("\t\t\t\t\t\t\t\tName(20 characters max,no space allowed) :"); scanf("%s",name);
		printf("\t\t\t\t\t\t\t\tAddress(200 characters max,no space allowed) :"); scanf("%s",address);
		printf("\t\t\t\t\t\t\t\tPhone(10 digit valid number,no space allowed):"); scanf("%s",ph);
		if (check_ph_num(ph)==0){
			strcpy(pre_msg_sgnup,resp_sgnup);
			return 0;
		}
		printf("\t\t\t\t\t\t\t\tUsername(10 characters max,no space allowed) :"); scanf("%s",us);
		printf("\t\t\t\t\t\t\t\tPassword(10 charcters max,no space allowed) :");  scanf("%s",ps);
		strcat(us,delimiter);strcat(us,ps);
		strcat(us,delimiter);strcat(us,name);
		strcat(us,delimiter);strcat(us,address);
		strcat(us,delimiter);strcat(us,ph);
		strcat(us,delimiter);strcat(us,money);
		strcat(us,delimiter);strcat(us,new_line);
		FILE * ptr= fopen(rest_det,"a+");
		fputs(us,ptr);
		fclose(ptr);
		strcpy(pre_msg_lgn,"\t   Sign up successful!");
		return 1;
		}
struct linear_data{
	char data[261];
	struct linear_data * next;
};
int update_profile(){
	system("clear");
	char updated_restowner_data[261];
	heading("UPDATE PROFILE");
	char name[20];char ph[10];char us[261];char ps[10];char address[200];char money[]="0.0"; char new_line[]="\n";char delimiter[]="%";
		if(strcmp(pre_msg_updtprof,"nil")!=0){
			printf("\t\t\t\t\t\t\t\t\t\t\t   %s\n",pre_msg_updtprof);
			for(int i=0;i<210;i++) printf("-");
			printf("\n");
		}
		printf("\t\t\t\t\t\t\t\tName(20 characters max,no space allowed) :"); scanf("%s",name);
		printf("\t\t\t\t\t\t\t\tAddress(200 characters max,no space allowed) :"); scanf("%s",address);
		printf("\t\t\t\t\t\t\t\tPhone(10 digit valid number,no space allowed):"); scanf("%s",ph);
		if (check_ph_num(ph)==0){
			strcpy(pre_msg_updtprof,"Invalid Phone Number");
			return 0;
		}
		printf("\t\t\t\t\t\t\t\tUsername(10 characters max,no space allowed) :"); scanf("%s",us);
		printf("\t\t\t\t\t\t\t\tPassword(10 charcters max,no space allowed) :");  scanf("%s",ps);
		strcat(us,delimiter);strcat(us,ps);
		strcat(us,delimiter);strcat(us,name);
		strcat(us,delimiter);strcat(us,address);
		strcat(us,delimiter);strcat(us,ph);
		strcat(us,delimiter);strcat(us,new_line);
		strcat(updated_restowner_data,us);
	struct linear_data * rest_data= (struct linear_data*)malloc(sizeof(struct linear_data));
	struct linear_data * temp= (struct linear_data*)malloc(sizeof(struct linear_data));
	FILE * ptr_r=fopen(rest_det,"r");
	fgets(rest_data->data,261,ptr_r);
	temp=rest_data;
	while(1){
		struct linear_data *tempx=(struct linear_data*)malloc(sizeof(struct linear_data));
		fgets(tempx->data,261,ptr_r);
		tempx->next=NULL;
		if(tempx->data==NULL) break;
		temp->next=tempx;
		temp=temp->next;
	}
	fclose(ptr_r);
	return 1;

}
void login_restowner()
{
	system("clear");
	int opt; // option 1
	char opt2[3]; //option 2
	int repeat;
	printf("\t\t\t\t\t\t\t\t\t\t\t :  : : :::LOGIN::: : :  :\n");
	for(int i=0;i<210;i++) printf("_");
	printf("\n");
	if(strcmp(pre_msg_mainpage,"nil")!=0){
		printf("\t\t\t\t\t\t\t\t\t\t\t%s \n",pre_msg_mainpage);
		for(int i=0;i<210;i++) printf("-");
		printf("\n");
	}
	printf("\t\t\t\t\t\t\t\t\t\t\t How do you want to login?\n");
	printf("\t\t\t\t\t\t\t\t\t\t 1. Via Username and Password\n");
	printf("\t\t\t\t\t\t\t\t\t\t 2. Via Phone number\n");
	printf("\t\t\t\t\t\t\t\t\t\t Enter number next to desired option...");
	scanf("%d",&opt);
    if(opt==1){
		repeat=1; // 1--> YES 0--> NO
		while(repeat==1){
			repeat=username_pass(pre_msg_lgn);
		}
		profile(current_rest);
		printf("\n\t\t\t\t\t\t\t\t\t\t\t < : Logout:");
	        printf("\n\t\t\t\t\t\t\t\t\t\t\t u : Update Profile:");
		printf("\n\t\t\t\t\t\t\t\t\t\t\t a : Add money to your wallet:");
		printf("\n\t\t\t\t\t\t\t\t\t\t\t o : Start Ordering:");
		scanf("%s",opt2);
		if(strcmp(opt2,"<")==0){
			strcpy(pre_msg_mainpage,"     You were logged out"); 
			strcpy(pre_msg_sgnup,"nil"); strcpy(pre_msg_lgn,"nil");
			login_restowner();
		}
		else if(~strcmp(opt2,"u")){
			int repeat=0;
			while(repeat==0) repeat=update_profile();
		}
		else if(strcmp(opt2,"a")){}
		else if(strcmp(opt2,"o")){}
		else exit(0);
	}
}
void main(){
	char login_as[1];
	system("clear");
	login_restowner();
}