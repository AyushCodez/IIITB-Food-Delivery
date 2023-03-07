#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "customer_order.c"
#include "customer_past.c"

#define cst_det "cust_det.txt" // MACRO for file cust_det.txt which contains customer details in format <username> <password> <name> <address> <phone> <money_in_wallet>
char current_cust[261];
char name[21]; char phone[11]; char username[11]; char password[11]; char address[201]; 
double money_in_acc=0.0; // THIS IS THE MONEY IN THE ACCOUNT OF THE LOGGED IN USER
//------------------>
char pre_msg_add_mny[50]="nil";
char pre_msg_prof[30]="nil";
char pre_msg_lgn[50]="nil"; // pre_msg_lgn --> message that has to be displeyed just after login hedaing
char pre_msg_sgnup[80]="nil"; // resp_sgnup --> message to be displayed just after signup heading
char pre_msg_updtprof[25]="nil";
//------------------>
typedef struct current_customer{
	char nm[21]; char ph[11]; char ad[201];
	char us[11]; char ps[11];
	double mny; // money
} cc;
int func(struct current_customer *cust){
	//...this function is to be
	//...defined by Ayush
	printf("received the object of cutsomer %s",cust->nm);
	return 0;
}
int update_wallet(float amt){ // returns 1 if wallet updated, else return 0 if wallet balance is insufficeint
	char updated_customer_data[261];
	char mny[50];
	char delimiter[]=" "; char new_line[]="\n";
	if(money_in_acc < amt) return 0;
	else{
		money_in_acc-=amt;
		strcpy(updated_customer_data,username);
		strcat(updated_customer_data,delimiter);strcat(updated_customer_data,password);
		strcat(updated_customer_data,delimiter);strcat(updated_customer_data,name);
		strcat(updated_customer_data,delimiter);strcat(updated_customer_data,address);
		strcat(updated_customer_data,delimiter);strcat(updated_customer_data,phone);
		sprintf(mny,"%lf",money_in_acc);
		strcat(updated_customer_data,delimiter);strcat(updated_customer_data,mny);
		strcat(updated_customer_data,delimiter);strcat(updated_customer_data,new_line);
		char linear_data[261];
		FILE * ptr_w=fopen("cust_det2.txt","w");
		FILE * ptr_r=fopen(cst_det,"r");
		while(fgets(linear_data,261,ptr_r)!=NULL){
			if(strcmp(linear_data,current_cust)!=0) fputs(linear_data,ptr_w);
			else fputs(updated_customer_data,ptr_w);
		}
		fclose(ptr_w);
		fclose(ptr_r);
		remove("cust_det.txt");
		rename("cust_det2.txt","cust_det.txt");
		strcpy(current_cust,updated_customer_data);
		return 1;
	}
}
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
		printf("\t\t\t\t\t\t\t\t\t\t\t:  : : :::%s",title);printf("::: : :  :\n");
		for(int i=0;i<210;i++) printf("_");
		printf("\n");
	}
int add_money(){
	double money;
	char updated_customer_data[261];
	char mny[50];
	char delimiter[]=" "; char new_line[]="\n";
	system("clear");
	heading("ADD MONEY");
	if(strcmp(pre_msg_add_mny,"nil")!=0){
		printf("\t\t\t\t\t\t\t\t\t\t%s\n",pre_msg_add_mny);
		printf("\n");
	}
	printf("\t\t\t\t\t\t\t\t\t\t Amt to be added (no spaces) : "); scanf("%s",mny);
	money=atof(mny);
	if(money==0){
		strcpy(pre_msg_add_mny,"\tInvalid or 0 Amount entered.");
		return 0;
	}
	money_in_acc+=money;
	strcpy(updated_customer_data,username);
	strcat(updated_customer_data,delimiter);strcat(updated_customer_data,password);
	strcat(updated_customer_data,delimiter);strcat(updated_customer_data,name);
	strcat(updated_customer_data,delimiter);strcat(updated_customer_data,address);
	strcat(updated_customer_data,delimiter);strcat(updated_customer_data,phone);
	sprintf(mny,"%lf",money_in_acc);
	strcat(updated_customer_data,delimiter);strcat(updated_customer_data,mny);
	strcat(updated_customer_data,delimiter);strcat(updated_customer_data,new_line);
	char linear_data[261];
	FILE * ptr_w=fopen("cust_det2.txt","w");
	FILE * ptr_r=fopen(cst_det,"r");
	while(fgets(linear_data,261,ptr_r)!=NULL){
		if(strcmp(linear_data,current_cust)!=0) fputs(linear_data,ptr_w);
		else fputs(updated_customer_data,ptr_w);
	}
	fclose(ptr_w);
	fclose(ptr_r);
	remove("cust_det.txt");
	rename("cust_det2.txt","cust_det.txt");
	strcpy(current_cust,updated_customer_data);
	return 1;
}
int profile(char ln[]){
		system("clear");
		heading("<<< PROFILE >>>");
		if(strcmp(pre_msg_prof,"nil")!=0){
			printf("\t\t\t\t\t\t\t\t\t\t\t%s",pre_msg_prof);printf("\n");
			for(int i=0;i<210;i++) printf("-");
			printf("\n");
		}
		char line[261];
		strcpy(line,ln);
		sscanf(line,"%s",username);
		sscanf(line,"%*s %s",password);
		sscanf(line,"%*s %*s %s",name);
		sscanf(line,"%*s %*s %*s %s",address);
		sscanf(line,"%*s %*s %*s %*s %s",phone);
		sscanf(line,"%*s %*s %*s %*s %*s %lf",&money_in_acc);
		printf("\t\t\t\t\t\t\t\t\t\t\t      >>> Welcome %s",name);printf(" <<<\n\n");
		printf("\t\t\t\t\t\t\t\t\t\t\t         Username: %s\n",username);
		printf("\t\t\t\t\t\t\t\t\t\t\t         Address: %s\n",address);
		printf("\t\t\t\t\t\t\t\t\t\t\t         Phone: %s\n",phone);
		printf("\t\t\t\t\t\t\t\t\t\t\t         Wallet Balance: %lf\n",money_in_acc);
		return 0;
	}
int username_pass(char * pre_msg);
int sign_up(); 
int username_pass(char * pre_msg){
		char us[11]; char ps[11]; // the username and password as read from the file
		char sgnup[]="s";
		char ext[]="e";
		//--------------
		char usrnm[21]; // max length of username restricted to 10, space has 1, and 10 for password
		char pass[10]; // max length of password restricted to 10
		char row[100]; // row that is read from the customer details file
		//--------------
		char delimiter[] = " ";
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
		FILE * ptr=fopen(cst_det,"r");
		while(fgets(row,100,ptr)!=NULL){
			sscanf(row,"%s %s",us,ps);
			strcat(us,delimiter);
			strcat(us,ps);
			if(check_usrnm_pass(usrnm,us)==1){
				fclose(ptr);
				strcpy(current_cust,row);
				return 0;
				};
		}
		fclose(ptr);
		strcpy(pre_msg_lgn,"Account not found. Wrong username or password");
		return 1;
	}	
int sign_up(){
		system("clear");
		heading("SIGN-UP");
		char row[261]; char u[11],p[11];
		char us_ps[22];
		char name[21];char ph[11];char us[261];char ps[11];char address[201];char money[]="0.0";
	    char new_line[]="\n";char delimiter[]=" ";
		if(strcmp(pre_msg_sgnup,"nil")!=0){
			printf("\t\t\t\t\t\t\t\t\t\t\t   %s\n",pre_msg_sgnup);
			for(int i=0;i<210;i++) printf("-");
			printf("\n");
		}
		printf("\t\t\t\t\t\t\t\tName(20 characters max,no space allowed) :"); scanf("%s",name);
		printf("\t\t\t\t\t\t\t\tAddress(200 characters max,no space allowed) :"); scanf("%s",address);
		printf("\t\t\t\t\t\t\t\tPhone(10 digit valid number,no space allowed):"); scanf("%s",ph);
		if (check_ph_num(ph)==0){
			strcpy(pre_msg_sgnup,"Invalid Phone Number");
			return 0;
		}
		printf("\t\t\t\t\t\t\t\tUsername(10 characters max,no space allowed) :"); scanf("%s",us);
		printf("\t\t\t\t\t\t\t\tPassword(10 charcters max,no space allowed) :");  scanf("%s",ps);
		strcat(us,delimiter);strcat(us,ps);
		strcpy(us_ps,us);
		strcat(us,delimiter);strcat(us,name); 
		strcat(us,delimiter);strcat(us,address);
		strcat(us,delimiter);strcat(us,ph);
		strcat(us,delimiter);strcat(us,money);
		strcat(us,delimiter);strcat(us,new_line);
		strcat(us,delimiter);
		FILE * ptr=fopen(cst_det,"r");
		while(fgets(row,100,ptr)!=NULL){
			sscanf(row,"%s %s",u,p);
			strcat(u,delimiter);
			strcat(u,p);
			if(check_usrnm_pass(us_ps,u)==1){
				fclose(ptr);
				strcpy(pre_msg_sgnup,"      Sorry,\n\t\t\t\t\t\t\t\t\t\tSame username/password has been already used");
				return 0;
				};
		}
		fclose(ptr);
		ptr= fopen(cst_det,"a+");
		fputs(us,ptr);
		fclose(ptr);
		strcpy(pre_msg_lgn,"\t   Sign up successful!");
		return 1;
		}
int update_profile(){
	system("clear");
	char updated_customer_data[261];
	heading("UPDATE PROFILE");
	char name[21]; char ph[11]; char us[261]; char ps[11]; char address[201]; char mny[50];
	sprintf(mny,"%lf",money_in_acc);
    char new_line[]="\n";char delimiter[]=" ";
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
		strcat(us,delimiter);strcat(us,mny);
		strcat(us,delimiter);strcat(us,new_line);
		strcpy(updated_customer_data,us);
	char linear_data[261];
	FILE * ptr_w=fopen("cust_det2.txt","w");
	FILE * ptr_r=fopen(cst_det,"r");
	while(fgets(linear_data,261,ptr_r)!=NULL){
		if(strcmp(linear_data,current_cust)!=0) fputs(linear_data,ptr_w);
		else fputs(updated_customer_data,ptr_w);
	}
	fclose(ptr_w);
	fclose(ptr_r);
	remove("cust_det.txt");
	rename("cust_det2.txt","cust_det.txt");
	strcpy(pre_msg_lgn,"Profile updated! Login to view:");
	return 1;
	}
void login_customer()
{
	int repeat=1; // 1--> YES 0--> NO
	while(repeat==1){
		repeat=username_pass(pre_msg_lgn);
	}
	pro:
		profile(current_cust);
	printf("\n\t\t\t\t\t\t\t\t\t\t\t < : Logout:");
	printf("\n\t\t\t\t\t\t\t\t\t\t\t u : Update Profile:");
	printf("\n\t\t\t\t\t\t\t\t\t\t\t a : Add money to your wallet:");
	printf("\n\t\t\t\t\t\t\t\t\t\t\t o : Start Ordering:");
	printf("\n\t\t\t\t\t\t\t\t\t\t\t p : See Past Orders:");
	printf("\n\t\t\t\t\t\t\t\t\t\t\t Enter anything else to exit");
	char opt[]="nil"; // option that the user chooses after seeing the profile
	scanf("%s",opt);
		if(strcmp(opt,"<")==0){
			strcpy(pre_msg_lgn,"          You were logged out :"); 
			strcpy(pre_msg_sgnup,"nil");	
			strcpy(pre_msg_add_mny,"nil");
			strcpy(pre_msg_updtprof,"nil");
			strcpy(pre_msg_prof,"nil");
			login_customer();
		}
		else if(strcmp(opt,"u")==0){
			int repeat=0;
			while(repeat==0) 
				repeat=update_profile();
			strcpy(pre_msg_lgn,"\t  Profile was updated.");
			strcpy(pre_msg_sgnup,"nil");
			strcpy(pre_msg_add_mny,"nil");
			strcpy(pre_msg_prof,"nil");
			strcpy(pre_msg_updtprof,"nil");
			login_customer();
		}
		else if(strcmp(opt,"a")==0){
			int repeat=0;
			while(repeat==0)
				repeat=add_money();
			strcpy(pre_msg_prof,"\tMoney added to Wallet");
			strcpy(pre_msg_lgn,"nil");
			strcpy(pre_msg_sgnup,"nil");
			strcpy(pre_msg_add_mny,"nil");
			strcpy(pre_msg_updtprof,"nil");
			goto pro;
		}
		else if(strcmp(opt,"o")==0){
		       cc_new c1;
		       strcpy(c1.nm,name);
			   strcpy(c1.ph,phone);
			   strcpy(c1.ad,address);
			   strcpy(c1.us,username);
			   strcpy(c1.ps,password);
			   c1.mny=money_in_acc; // if true then control will return to main  function were  one can resume following process
			   float price = main_order(c1);
			   update_wallet(price);
			   goto pro;
		}
		else if(strcmp(opt,"p")==0){
		       main_past(name);
			   goto pro;
		}
		else exit(0);
}
void main(){
	system("clear");
	login_customer();
}
