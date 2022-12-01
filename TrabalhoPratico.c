#include <stdio.h>
#include <time.h>
#include <locale.h> 
#include <string.h>

struct login {
	char fName[50];
	char lName[50];
	char email[50];
	char dataNascimento[50];
	int numeroTelemovel[9];
	char username[50];
	char password[50];
} login;

void interface();
int loginRegister();
void loginConta();
void registerConta();

int main(){
	setlocale(LC_ALL, "Portuguese"); //Mudar lingua para portugues devido aos acentos
	interface(); //Desenhar Logo
	int op = loginRegister(); //User quer dar login ou register
	if(op){
		if(op==1)
			loginConta();
		else
			registerConta();
	}else{
		return -1;
	}
	
	//system("CLS"); // server para limpar a tela
	
	time_t horario; //time_t � um tipo de varial para horario
	struct tm * timeinfo; //broken-down calendar time type: year, month, day, hour, minute, second
	time(&horario); //Da return ao horario do sistema na variavel horario
	timeinfo = localtime(&horario); //O valor do horario � dividido na estrutura tm e expresso no fuso horario local
	printf("%02d:%02d:%02d", timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec); //horas,minutos e segundos
	
	return 0;
}

void interface(){
	//Desenhar Logo
	puts("");
    puts("�������������    �������������    ����      ���    ������������     �������������    �������������");
    puts("     ���              ���         �����     ���    ���       ���    ���              ���       ���");
    puts("     ���              ���         ������    ���    ���       ���    ���              ���       ���");
    puts("     ���              ���         ��� ���   ���    ���       ���    ���              ���       ���");
    puts("     ���              ���         ���  ���  ���    ���       ���    �������������    �������������");
    puts("     ���              ���         ���   ��� ���    ���       ���    ���              ���    ���   ");
    puts("     ���              ���         ���    ������    ���       ���    ���              ���     ���  ");
    puts("     ���              ���         ���     �����    ���       ���    ���              ���      ��� ");
    puts("     ���         �������������    ���      ����    ������������     �������������    ���       ���");
    puts("");
}

int loginRegister(){
	int op;
	puts("1) Acessar Conta \t 2) Criar Conta");
	printf("Op��o: ");
	scanf("%d",&op);
	if(op==1||op==2){
		return op;
	}else{
		printf("Op��o invalida");
		return 0;
	}
}

void loginConta(){
	char username[200];
	FILE *log;
	log = fopen("bd1.ini","r");
	struct login l;
	printf("Username: ");scanf("%s",username);
	
	//Colocar a pass invisivel
	int i = 0;
	char ch;
	char pwd[200];
	printf("Password: ");
	while((ch = _getch()) != 13){
		pwd[i] = ch;
		i++;
		printf("*");
	}
	puts("");
	while(fread(&l,sizeof(l),1,log)){
		if(strcmp(username,l.username)==0&&strcmp(pwd,l.password)==0)
			printf("Succesful Login\n");
		else
			printf("Username/Password Incorreto!");
	}
	fclose(log);
}

void registerConta(){
	FILE *log;
	log = fopen("bd1.ini","w");
	//struct login l;
	printf("First Name: ");scanf("%s",login.fName);
	printf("Last Name: ");scanf("%s",login.lName);
	printf("Email: ");scanf("%s",login.email);
	printf("Data de Nascimento (DD/MM/AAAA): ");scanf("%s",login.dataNascimento);
	printf("Numero Telemovel: ");scanf("%s",login.numeroTelemovel);
	printf("Username: ");scanf("%s",login.username);
	//Colocar a pass invisivel
	int i = 0;
	char ch;
	char pwd[200];
	printf("Password: ");
	while((ch = _getch()) != 13){
		pwd[i] = ch;
		i++;
		printf("*");
	}
	strcpy(login.password, pwd);
	puts("");
	
	fwrite(&login,sizeof(login),1,log);
	fclose(log);
	printf("Registado com sucesso!\nAgora deve logar com a sua conta nova.");
	printf("\nPress any key to continue......");
	getch();
	system("CLS");
	loginConta();
}
