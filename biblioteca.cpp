#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <locale.h>

//menu principal
void menuPrincipal();

//STRUCTS

struct Usuarios {      
    long long int cpf;
    char nome[30];
};

struct Itens {      
    int condigo[6];
    char tipo[1];
    char titulo[30];
    char autor[30]
    char editora[15];
    int  ano;
};

//usuario
void menuUsuarios();
void CadastarUsuarios(Usuarios usuario[],int& cont);
void ExclusaoUsuarios();
void ListarUsuarios(Usuarios usuario[],int cont);

//Intens
void menuItens();
void CadastarItens();
void EmprestimoDevolucao();

//Validação
bool ValidarString(char string[],int menor, int maior);
bool ValidaCpf(long long int cpf);



int main(){
	setlocale(LC_ALL, "Portuguese");
    menuPrincipal();
    
}



//Menu principal------------------------------------------------------------------------------
void menuPrincipal(){
	int input;
	
    do {
        printf("\n");
        printf ("Menu Principal \n");
        printf("1 - Cadastro de usuários \n");
        printf("2 - Cadastro de Itens da biblioteca \n");
        printf("3 - Empréstimo/devolução \n");
        printf("4 - Fim \n");        
        fflush(stdin);
        scanf("%d", &input);
        system("cls");
        switch(input)
        {
        case 1:
            menuUsuarios();
            break;
        case 2:
        	menuItens();
            break;
        case 3:
        	EmprestimoDevolucao();
            break;        
        case 4:
            exit(EXIT_SUCCESS);
        default:
            printf ("\n Opção inválida!\n");
            fflush(stdin);
            menuPrincipal();
        }
    }
    while(input != 0);
    system("cls");
}


bool ValidarString(char string[],int menor, int maior){
	
if(strlen(string)>=menor && strlen(string)<=maior){
	
	return true;
	
}else{
	
	return false;
	
}

	
}


bool ValidaCpf(long long int cpf){
	
	if(cpf>9999999999 && cpf<100000000000){
		
		return true;
	}else{
		
		return false;
	}

	
}


bool ValidarNumero(int numero, int menor, int maior){
	
if(numero>=menor && numero<=maior){
	
	return true;
	
}else{
	
	return false;
	
}
	
}


void ImprimirEspaco(int n){
	
	for(int i=0;i<n;i++){
		
		printf(" ");
		
	}
	
}


void StringMaiuscula(char* string){
    while ((*string = (char) toupper(*string))) string++;
}







//Menu de usuários -------------------------------------------------------------------------

void menuUsuarios()
{
	int input=0,cont=0;
	
	Usuarios usuario[50];
	
    do
    {
        printf("\n");
        printf ("Menu de Cadastro de Usuários \n");
        printf("1 - Cadastrar novo usuário \n");
        printf("2 - Excluir usuário \n");
        printf("3 - Listar usuários (ordenado por CPF) \n");
        printf("4 - Listar usuários (ordenado por Nome) \n");  
		printf("5 - Voltar \n");        
        fflush(stdin);
        scanf("%d", &input);
        system("cls");
        switch(input)
        {
        case 1:
        	if(cont<50){
        		CadastarUsuarios(usuario,cont);
			}else{
				
				printf("Quantidade de Usuário esgotada!");
			}
            break;
        case 2:
        	ExclusaoUsuarios();
            break;
        case 3:
        	system("cls");
        	fflush(stdin);
        	ListarUsuarios(usuario,cont);
            break;   
	    case 4:
          ListarUsuarios(usuario,cont);
			break;      
        case 5:
            menuPrincipal();
            system("cls");
        default:
            printf ("\n Opcao invalida!\n");
            fflush(stdin);
            menuUsuarios();
        }
    }
    while(input != 0);
    system("cls");
}



//Cadastro de usuários ------------------------------------------------------------------------------------------

void CadastarUsuarios(Usuarios usuario[],int& cont){
	
		int input=0;
		long long int cpf;
		char nome[30];
	
    	//cadastra cpf
    	   
        printf("CPF: ");
         scanf("%lli", &cpf);       
         fflush(stdin);
      
      
        if(ValidaCpf(cpf)){
        
        	printf("\nErro no cadastro. Item ja cadastrado!\n");
        	input++;
		}else{
			
			printf("CPF  maior ou menor que 11 caracteres!");
			getchar();
		//	CadastarUsuarios(Usuarios usuario[],int cont);
			menuUsuarios();
			
		}
       
      
	
		// Cadastrar nome
	
		  do{
		printf("Nome: ");
        gets(nome);
        fflush(stdin);
         
         
         if(ValidarString(nome,4,30)){
           
        	//	printf("\n Nome  cadastrado\n");
        		input++;
           
		}else{
			
			printf("Nome maior que 30 caracters!");
			getchar();
			system("cls"); 
			
		}
	}while (ValidarString(nome,4,30)==false);
		
		
		
		if(input==2){
		strcpy(usuario[cont].nome, nome);	    
	    usuario[cont].cpf=cpf;
			
		cont++;		
		printf("\nCadastro realizado com sucesso!");	
		getchar();
		system("cls"); 
		}
        
       
}





//Exclusão de usuário --------------------------------------------------------------------------------------------

void ExclusaoUsuarios(){
	long long int cpf;
	int input;
	
	
		//pesquisar cpf
    	   
        printf("CPF: ");
         scanf("%lli", &cpf);       
         fflush(stdin);
      
      
        if(ValidaCpf(cpf)){
        	
        //	exclusão de usuário   
		     
        	input++;
        	
		}else{
			
			printf("CPF  maior ou menor que 11 caracteres!");
			getchar();
		//	CadastarUsuarios();
			
		}
		
		
		if(input!=0){
			
			printf("Cadastro realizado com sucesso!");
		}
	
}




//Listar usuário-------------------------------------------------------------------------------------------

void ListarUsuarios(Usuarios usuario[],int cont){
	
	printf("--------------------------------------------------\n");
	printf("CPF         Nome\n");
	printf("--------------------------------------------------\n");

	for(int i=0;i<cont;i++){
		printf("%lli",usuario[i].cpf);
		ImprimirEspaco(1);
		printf("%s",usuario[i].nome);
		
		printf("\n");	
	}
	getchar();
    system("cls");
}
        
        
 





//menu cadastro de itens ---------------------------------------------------------------------------------

void menuItens(){
	int input;
	
    do
    {
        printf("\n");
        printf ("Menu de Cadastro de Itens \n");
        printf("1 - Cadastrar novo item \n");
        printf("2 - Excluir item \n");
        printf("3 - Listar itens (ordenado por código) \n");
        printf("4 - Listar itens (ordenado por titulo) \n");  
		printf("5 - Voltar \n");        
        fflush(stdin);
        scanf("%d", &input);
        system("cls");
        switch(input)
        {
        case 1:
            CadastarItens();
            break;
        case 2:
        	printf("2 - Excluir item \n");
            break;
        case 3:
            printf("3 - Listar itens (ordenado por código) \n");
            break;   
	    case 4:
            printf("4 - Listar itens (ordenado por titulo) \n");
			break;      
        case 5:
            menuPrincipal();
            system("cls");
        default:
            printf ("\n Opcao invalida!\n");
            fflush(stdin);
            menuItens();
        }
    }
    while(input != 0);
    system("cls");
}


//Cadastro de Itens ------------------------------------------------------------------------------------------

void CadastarItens(){
	
	int codigo,input=0,ano;
	char tipo[1],titulo[30],autor[30],editora[15];
	
	//cadastra codigo
    	   
        printf("Código: ");
         scanf("%d", &codigo);       
         fflush(stdin);	
         
         if(ValidarNumero(codigo,1,999999)){
         	
         	//implementar cadastro
         	
         	printf("Código: %d \n", codigo);
         	printf("Erro no cadastro. Item ja cadastrado!\n");
         	input++;
         	
		 }else{
		 	
		 	printf("Código precisa ser possitivo de até 6 caracteres!");
		 	getchar();
		 	CadastarItens();
		 }
		 
		 
		 
	// cadastrar tipo	 
	
	do{	
	printf("Tipo: ");
	scanf("%s",tipo);
	fflush(stdin);	
	StringMaiuscula(tipo);
	
	
	if(stricmp(tipo,"R")==0 || stricmp(tipo,"L")==0){
		
		
	//implementar cadastro	
	input++;
		
	}else{
	
	printf("\nO Tipo não é  R para Resvistas ou  L para Livros!\n");
	getchar();
	system("cls"); 
	}	
	
		 
}while(stricmp (tipo,"R")!=0 && stricmp (tipo,"L")!=0);
		 
		 
		 
	



//cadastrar titulo

do{
	
	printf("Titulo: ");
	scanf("%s",titulo);
	fflush(stdin);	
	StringMaiuscula(tipo);
	
	if(ValidarString(titulo,4,30)){
		
		input++;
		
	}else{
	
	printf("\nTitulo é menor que 4 ou maior que 30 caracteres!\n");	
	getchar();
	system("cls");	
	}	
	
		 
}while(ValidarString(titulo,4,30)==false);
		 
		 
		 
//cadastrar Autor

if(stricmp(tipo,"L")==0){

do{
	
	printf("Autor: ");
	scanf("%s",autor);
	fflush(stdin);	
	StringMaiuscula(autor);
	
	if(ValidarString(autor,4,30)){
		
		input++;
		
	}else{
	
	printf("\nTitulo é menor que 4 ou maior que 30 caracteres!\n");	
	getchar();
	system("cls");	
	}	
	
		 
}while(ValidarString(autor,4,30)==false);		 
		 
}


//cadastrar Editora

do{
	
	printf("Editora: ");
	scanf("%s",editora);
	fflush(stdin);	
	StringMaiuscula(editora);
	
	if(ValidarString(editora,4,30)){
		
		input++;
		
	}else{
	
	printf("\nEditora é menor que 4 ou maior que 30 caracteres!\n");	
	getchar();
	system("cls");	
	}	
	
		 
}while(ValidarString(editora,4,15)==false);	



//cadastrar Ano

do{
	
	printf("Ano: ");
	scanf("%d",&ano);
	fflush(stdin);	
		
	if(ValidarNumero(ano,1,9999)){
		
	input++;	
		
	}else{
	
	printf("\nAno precisa ser possitivo de até 6 caracteres!\n");	
	getchar();
	system("cls");	
	}	
	
		 
}while(ValidarNumero(ano,1,9999)==false);		 
		 


		 
		 
		 
		 
		 if(input>4 && input<7){
		 	
		 	printf("Cadastro realizado com sucesso!");
		 	getchar();
	        system("cls");
		 }
         
	
}





//Exclusão de Itens --------------------------------------------------------------------------------------------

void ExclusaoItens(){
	
       
}




//Listar Itens-------------------------------------------------------------------------------------------

void ListarItens(int tipo){
		
}
        
        
 



//menu de devolucao/emprestimo -------------------------------------------------------------------------

void EmprestimoDevolucao(){
	
	int input;
	
    do
    {
        printf("\n");
        printf ("Menu Empréstimo/Devolução \n");
        printf("1 - Emprestar item \n");
        printf("2 - Devolver item \n");
        printf("3 - Listar empréstimos \n");        
		printf("4 - Voltar \n");        
        fflush(stdin);
        scanf("%d", &input);
        system("cls");
        switch(input)
        {
        case 1:
            printf ("\n Menu 1 \n");
            break;
        case 2:
        	printf ("\n Menu 2 \n");
            break;
        case 3:
        	printf ("\n Menu 3\n");
            break;   
	   
        case 4:
            menuPrincipal();
            system("cls");
        default:
            printf ("\n Opção inválida!\n");
            fflush(stdin);
        }
    }
    while(input != 0);
    system("cls");    

}





