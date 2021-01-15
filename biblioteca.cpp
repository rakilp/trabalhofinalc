#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <locale.h>


//STRUCTS

 struct Usuario {      
    long long int cpf;
    char nome[30];
};


//usuario

void menuUsuario(Usuario usuario[], int& cont);
void CadastarUsuario(Usuario usuario[], int& cont);
void ListarUsuarios(Usuario usuario[],int cont);
void ExcluirCPF(Usuario* excluir,int& cont, long long int cpf);



//validação
bool ValidaCpf(long long int cpf){
	
	if(cpf>9999999999 && cpf<100000000000){
		
		return true;
	}else{
		
		return false;
	}

	
}


bool ValidarString(char string[],int menor, int maior){
	
if(strlen(string)>=menor && strlen(string)<=maior){
	
	return true;
	
}else{
	
	return false;
	
}

	
}

//espaços

void ImprimirEspaco(int n){
	
	for(int i=0;i<n;i++){
		
		printf(" ");
		
	}
	
}


//busca

bool BuscaCpf(Usuario usuario[],long long int cpf,int cont){
	bool result=false;
	
	
for(int i=0;i<=cont;i++){
	/*
	printf("%d \n",i);
	printf("%lli \n",usuario[i].cpf);
	printf("%lli \n",cpf);
	*/
	
	if(cpf==usuario[i].cpf){
		
		result = true;
		break;
	}
	
}

return result;
	
}


//ordenação

void OrdenaCPF(Usuario* ordena,int cont){
   int i, j;
   char copia[100];
   struct Usuario aux;
   
   for (j=cont-1; j>=0; j--){
        for (i=0; i<=j; i++){
            if (ordena[i].cpf > ordena[i+1].cpf){                            
                aux = ordena[i];
                ordena[i] = ordena[i+1];
                ordena[i+1] = aux;             
            }
        }
    }
}

void OrdenaNome(Usuario* ordena,int cont){
   int i, j;
   char copia[100];
   struct Usuario aux;
   
   printf("%d ordenado por nome \n",cont);
   
   for (j=cont-1; j>=0; j--){
        for (i=0; i<=j; i++){
            if (strcoll(ordena[i].nome,ordena[i+1].nome)> 0){                            
                aux = ordena[i];
                ordena[i] = ordena[i+1];
                ordena[i+1] = aux;             
            }
        }
    }
}




//excluir
void ExcluirCPF(Usuario* excluir,int& cont, long long int cpf){

printf("Exluir\n");

//cpf=10907926894;

 int i;

for (i=0; i <= cont; i++)
{
    if(excluir[i].cpf == cpf)
    {
        while(i <= cont-1)
        {
            excluir[i] = excluir[i+1];
            i++;
        }
        cont--;        
        break;
    }
    
}

}
	


//listar

void ListarUsuarios(Usuario usuario[],int cont){
	
	printf("--------------------------------------------------\n");
	printf("CPF         Nome\n");
	printf("--------------------------------------------------\n");

	for(int i=0;i<=cont;i++){
		printf("%lli",usuario[i].cpf);
		ImprimirEspaco(1);
		printf("%s",usuario[i].nome);
		
		printf("\n");	
	}
	fflush(stdin);
	getchar();
    system("cls");
}


  
//Menu de usuários -------------------------------------------------------------------------

void menuUsuario(Usuario usuario[], int& cont){
	int input=0;
	long long int cpf;
	 do{
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
        	
        	CadastarUsuario(usuario,cont);
        
            break;
        case 2:
        	printf("CPF: ");
        	scanf("%lli",&cpf);
        	
        	if(BuscaCpf(usuario,cpf,cont)){
        	   ExcluirCPF(usuario,cont,cpf);
        	   printf("Exclusao realizada com sucesso!");
        	   fflush(stdin);
        	   getchar();
        	   
			}else{
				printf("Erro na exclusao. Usuario nao cadastrado!");
				fflush(stdin);
				getchar();
			}
        	
        	
        
            break;
        case 3:
        	
        	OrdenaCPF(usuario,cont);
        	ListarUsuarios(usuario,cont);
        	
            break;   
	    case 4:
	    	
	    	OrdenaNome(usuario,cont);
	    	ListarUsuarios(usuario,cont);
         
			break;      
        case 5:
             system("cls");
             input=0;
        default:
            printf ("\n Opcao invalida!\n");
            fflush(stdin);
            
        }
    }
    while(input != 0);
    system("cls");
}



//Cadastro de usuários ------------------------------------------------------------------------------------------

void CadastarUsuario(Usuario usuario[], int& cont){
	
usuario[0].cpf=10907926894;
strcpy(usuario[0].nome,"ZAIAS BISPO DOS SANTOS");

usuario[1].cpf=54593229799;
strcpy(usuario[1].nome,"MARINA FERRUCCI BEGA");

usuario[2].cpf=11533741883;
strcpy(usuario[2].nome,"WALDIR CLAUDIO DE CASTRO JUNIOR");

usuario[3].cpf=37909198884;
strcpy(usuario[3].nome,"REGINA LOURENÇO DE BARROS");

usuario[4].cpf=27672903829;
strcpy(usuario[4].nome,"ALINE NUNES DE OLIVEIRA MACHAD");

cont=4;
	
	
	
	
/*
   int input=0;
    long long int cpf;
	char nome[30];
	
	
	
	
    	//cadastra cpf    	   
        printf("CPF: ");
         scanf("%lli", &cpf);  		     
         fflush(stdin);
         
         if(ValidaCpf(cpf)){
         	
         	
         if(BuscaCpf(usuario,cpf,cont)){
    	
       	printf("Erro no cadastro. CPF ja cadastrado!");
       	menuUsuario(usuario,cont);
    	
     	}else{
		
		cont++;
		usuario[cont].cpf=cpf;
		
	    }
   
		 }else{
		 	
		 	printf("Erro no cadastro!");
		 	menuUsuario(usuario,cont);
		 }
		 
		 
		 	
		//nome
	 
	 do{
	 	
	 	printf("Nome: ");
        gets(nome);
        fflush(stdin);
        
        if(ValidarString(nome,4,30)){
        	
        	strcpy(usuario[cont].nome,nome);
        	
        		printf("Cadastro realizado com sucesso!");	
        		getchar();
        		system("cls");
        	
		}else{
			
			printf("Erro");
			getchar();
			fflush(stdin);
		}
        
	 	
	 }while(ValidarString(nome,4,30)==false);
			
        
 
   */
}

   
   
   
   
//Main
      
 int main(){
	
	setlocale(LC_ALL, "Portuguese");
    
    int input;
    
    int contusuario=-1;
    
    Usuario usuario[5];
	
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
        
        
        switch(input){
        	
        case 1:
            
            menuUsuario(usuario,contusuario);
            
            break;
        case 2:
        	for(int i=0;i<=contusuario;i++){
        	
        	printf("%lli   %s \n",usuario[i].cpf,usuario[i].nome);
        	
		}
            break;
        case 3:
        	
            break;        
        case 4:
            exit(EXIT_SUCCESS);
        default:
            printf ("\n Opção inválida!\n");
            fflush(stdin);
            
        }
    }
    while(input != 0);
    system("cls");
    
}




