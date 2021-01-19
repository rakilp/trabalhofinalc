#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <locale.h>
#include <time.h>

const int MAX_LEN = 30;
const int MAX_LEN_EDITORA = 15;
const int MIN_LEN_STRING = 4;

// STRUCTS
struct Usuario {      
    long long int cpf;
    char nome[MAX_LEN];
};

struct ItemBiblioteca {
    int codigo;
    char tipo_item[2];
    char titulo[MAX_LEN];
    char nome_autor[MAX_LEN];
    char nome_editora[MAX_LEN_EDITORA];
    int ano_publicacao;
};

struct Emprestimo {
	int codigo_emprestimo;
	long long int cpf_emprestimo;
    int dia_emprestimo;
    int mes_emprestimo;
    int ano_emprestimo;
    int dia_devolucao;
    int mes_devolucao;
    int ano_devolucao;
};

// MENU
void MenuUsuario(Usuario usuario[], Emprestimo emprestimo[],ItemBiblioteca itens[], int& cont_usuario, int cont_emprestimo, int cont_iten);
void MenuItem(ItemBiblioteca itens[], Emprestimo emprestimo[], int& cont_itens, int cont_emprestimo);
void MenuEmpestimo(Emprestimo emprestimo[], Usuario usuario[],ItemBiblioteca iten[], int& cont_emprestimo,int cont_usuario,int cont_iten);

// CADASTRAR
void CadastrarUsuario(Usuario usuario[], int& cont);
void  CadastrarItem(ItemBiblioteca itens[], int& cont);
void CadastrarEmprestimo(Emprestimo emprestimo[], Usuario usuario[], ItemBiblioteca iten[], int& cont_emprestimo, int cont_usuario, int cont_iten);

// LISTAR
void ListarUsuarios(Usuario usuario[], Emprestimo emprestimo[], ItemBiblioteca iten[], int cont_usuario, int cont_emprestimo,int cont_iten);
void ListaItensEmprestimo(Emprestimo emprestimo[], ItemBiblioteca iten[], int cont_emprestimo, int cont_iten, long long int cpf);
void ListaEmprestimo(Emprestimo emprestimo[],Usuario usuario[],ItemBiblioteca iten[], int cont_emprestimo,int cont_usuario , int cont_iten);

// EXCLUIR
void ExcluirCPF(Usuario* excluir, int& cont, long long int cpf);

// Maiuscula
void StringMaiuscula(char* string);


//VALIDAR
bool ValidaCpf(long long int cpf);
bool ValidarString(char string[], int menor, int maior);
bool ValidaNumero(int numero,int max , int min);

//BUSCA
bool BuscaCpf(Usuario usuario[],long long int cpf,int cont);
bool BuscaCpfEmprestimo(Emprestimo emprestimo[], long long int cpf, int cont);
bool BuscaCodigo (ItemBiblioteca itens[], int codigo, int cont);
bool BuscaCodigoEmprestimo(Emprestimo emprestimo[], int codigo, int cont);
//Recuperar
int  RecuperarNome(Usuario usuario[], long long int cpf,int cont);
int RecuperarTitulo(ItemBiblioteca iten[],int codigo,int cont);
int RecuperarData(Emprestimo emprestimo[],long long int cpf,int cont);





// -=-=-=-=-=-DATA-=-=-=-=-=-
void data_hora_atual(int &dia, int &mes, int &ano) {
 time_t t = time(NULL);
 struct tm lt = *localtime(&t);
 ano = lt.tm_year + 1900;
 mes = lt.tm_mon + 1;
 dia = lt.tm_mday;

}

// USUARIO
// -=-=-=-=-=-Cadastro-=-=-=-=-=-
void CadastrarUsuario(Usuario usuario[], int& cont) {

    long long int cpf;
	char nome[MAX_LEN];
	int input=0;

    // -=-=-=-=-=-CPF-=-=-=-=-=-   	   
    
    
    
    printf("CPF: ");
    scanf("%lli", &cpf);  		     
    fflush(stdin);
        
    if (ValidaCpf(cpf)) {
        if (BuscaCpf(usuario,cpf,cont)) {
            printf("Erro no cadastro. CPF ja cadastrado!");
            getchar();
             system("cls");
            input=1;
        } 
        else {
            cont++;
            usuario[cont].cpf = cpf;  
        }
    }else {
        printf("Erro no cadastro! \n");
        getchar();
        system("cls");
        
         input=1;
        
        	
    }
    
	if(input==0){

		
	// -=-=-=-=-=-NOME-=-=-=-=-=-
	do {
	 	printf("Nome: ");
        gets(nome);
        fflush(stdin);
        StringMaiuscula(nome);
        
        if(ValidarString(nome, MIN_LEN_STRING, MAX_LEN)) {
        	
        	strcpy(usuario[cont].nome, nome);
            printf("Cadastro realizado com sucesso!");	
            fflush(stdin);
            getchar();
            system("cls");
               
        	
		} else {
			printf("Erro no cadastro!");			
			getchar();
			fflush(stdin);
			system("cls");
			
			
		}
	} while(!ValidarString(nome, MIN_LEN_STRING,MAX_LEN));
	
	
		}
	
}

//-=-=-=-=-=-VALIDACAO-=-=-=-=-=-
bool ValidaCpf(long long int cpf) {
	
	if(cpf > 9999999999 && cpf < 100000000000)
		return true;
	else
		return false;
}

bool ValidarString(char string[], int menor, int maior){
	
    if(strlen(string) >= menor && strlen(string) <= maior)
        return true;
    else
        return false;
}


//-=-=-=-=-=-ESPACOS-=-=-=-=-=-
void ImprimirEspaco(int n){

	for(int i=0; i<=n; i++)
		printf(" ");
}
// -=-=-=-=-=-MAIUSCULO -=-=-=-=-=-
void StringMaiuscula(char* string){
	while ((*string = (char) toupper(*string))) string++;
}
// -=-=-=-=-=-BUSCA -=-=-=-=-=-
bool BuscaCpf(Usuario usuario[], long long int cpf, int cont){
	
    bool result = false;
	
    for(int i = 0; i <= cont; i++)
        if(cpf == usuario[i].cpf) {
            return true;
        }  

    return result;	
}


//-=-=-=-=-=-ORDENACAO-=-=-=-=-=-
void OrdenaCPF(Usuario* ordena,int cont) {
   struct Usuario aux;
   
   for (int j = cont-1; j >= 0; j--)
        for (int i = 0; i <= j; i++)
            if (ordena[i].cpf > ordena[i+1].cpf){                            
                aux = ordena[i];
                ordena[i] = ordena[i+1];
                ordena[i+1] = aux;             
            }
}

void OrdenaNome(Usuario* ordena,int cont){
   struct Usuario aux;
   
   for (int j = cont-1; j >= 0; j--)
        for (int i=0; i<=j; i++)
            if (strcoll(ordena[i].nome,ordena[i+1].nome)> 0){                            
                aux = ordena[i];
                ordena[i] = ordena[i+1];
                ordena[i+1] = aux;             
            }
}

// -=-=-=-=-=-EXCLUIR-=-=-=-=-=-
void ExcluirCPF(Usuario* excluir, int& cont, long long int cpf){

  

    for (int i = 0; i <= cont; i++)
        if(excluir[i].cpf == cpf) {
            while(i <= cont-1) {
                excluir[i] = excluir[i+1];
                i++;
            }
            cont--;        
            break;
        }
}

// -=-=-=-=-=-LISTAR-=-=-=-=-=- /*ADICIONAR EMPRESTIMO*/
void ListarUsuarios(Usuario usuario[], Emprestimo emprestimo[], ItemBiblioteca iten[], int cont_usuario, int cont_emprestimo,int cont_iten){
	
	printf("--------------------------------------------------\n");
	printf("CPF          Nome\n");
	printf("--------------------------------------------------\n");

	for(int i = 0; i <= cont_usuario; i++) {
		printf("%lli", usuario[i].cpf);
		ImprimirEspaco(1);
		printf("%s", usuario[i].nome);
		printf("\n");	
		
		ListaItensEmprestimo(emprestimo, iten, cont_emprestimo, cont_iten,usuario[i].cpf);
		
		
		
	}
	
    fflush(stdin);
	getchar();
    system("cls");
}

// ITENS

//-=-=-=-=-=-CADASTRAR-=-=-=-=-=-
void CadastrarItem(ItemBiblioteca itens[], int& cont) {

   int codigo,ano;
   char tipo[2],titulo[MAX_LEN],autor[MAX_LEN],editora[MAX_LEN_EDITORA];
   int input=0;
   
   // -=-=-=-=-=-CODIGO-=-=-=-=-=-   	   
    printf("Codigo: ");
    scanf("%d", &codigo);  		     
    fflush(stdin);
     
    if (ValidaNumero(codigo,-1,100000)) {
        if (BuscaCodigo(itens,codigo,cont)) {
            printf("Erro no cadastro. Codigo já cadastrado!");
            getchar();
             system("cls");
             input=1;
            
        } 
        else {
            cont++;
            itens[cont].codigo = codigo;  
        }
    }
    else {
        printf("Erro no cadastro! \n");
        getchar();
        system("cls");      
        input=1;	
    }
    
    if(input==0){

     // -=-=-=-=-=-TIPO-=-=-=-=-=-
	
	do{	
	printf("Tipo: ");
	scanf("%s",tipo);
	fflush(stdin);	
	StringMaiuscula(tipo);
	
	
	if(stricmp(tipo,"R")==0 || stricmp(tipo,"L")==0){
		
		
	strcpy(itens[cont].tipo_item, tipo);	
	
	}else{
	
	printf("\nO Tipo não é  R para Resvistas ou  L para Livros!\n");
	getchar();
	system("cls"); 
	}	
	
		 
}while(stricmp (tipo,"R")!=0 && stricmp (tipo,"L")!=0);
		 
		 
		 
		 
		  // -=-=-=-=-=-TITULO-=-=-=-=-=-
		 
    
    do{
	
	printf("Titulo: ");
	gets(titulo);
	fflush(stdin);	
	StringMaiuscula(titulo);
	
	if(ValidarString(titulo,MIN_LEN_STRING,MAX_LEN)){
		
	strcpy(itens[cont].titulo, titulo);
		
	}else{
	
	printf("\nTitulo é menor que 4 ou maior que 30 caracteres!\n");	
	getchar();
	system("cls");	
	}	
	
		 
}while(ValidarString(titulo,MIN_LEN_STRING,MAX_LEN)==false);	
    
    
    
   
  
   



  
// -=-=-=-=-=-AUTOR-=-=-=-=-=-

if(stricmp(tipo,"L")==0){

do{
	
	printf("Autor: ");
	gets(autor);
	fflush(stdin);	
	StringMaiuscula(autor);
	
	if(ValidarString(autor,MIN_LEN_STRING,MAX_LEN)){
		
	strcpy(itens[cont].nome_autor, autor);
		
	}else{
	
	printf("\nAutor é menor que 4 ou maior que 30 caracteres!\n");	
	getchar();
	system("cls");	
	}	
	
		 
}while(ValidarString(autor,MIN_LEN_STRING,MAX_LEN)==false);		 
		 
}else{
	
	strcpy(itens[cont].nome_autor, " ");
	
}

// -=-=-=-=-=-EDITORA-=-=-=-=-=-

do{
	
	printf("Editora: ");
	gets(editora);
	fflush(stdin);	
	StringMaiuscula(editora);
	
	if(ValidarString(editora,MIN_LEN_STRING,MAX_LEN_EDITORA)){
		
	strcpy(itens[cont].nome_editora, editora);
		
	}else{
	
	printf("\nEditora é menor que 4 ou maior que 30 caracteres!\n");	
	getchar();
	system("cls");	
	}	
	
		 
}while(ValidarString(editora,MIN_LEN_STRING,MAX_LEN_EDITORA)==false);	

  
  
  // -=-=-=-=-=-ANO-=-=-=-=-=-
  
  
  
  do{
	
	printf("Ano: ");
	scanf("%d",&ano);
	fflush(stdin);	
		
	if(ValidaNumero(ano,999,10000)){
		
	itens[cont].ano_publicacao = ano;
		
	}else{
	
	printf("\nAno precisa ser possitivo de até 6 caracteres!\n");	
	getchar();
	system("cls");	
	}	
	
		 
}while(ValidaNumero(ano,999,10000)==false);	
  
  printf("Cadastro realizado com sucesso!");
  getchar();
  system("cls");
  
  
  
  	}
    
  
}

//-=-=-=-=-=-VALIDACAO-=-=-=-=-=-
bool ValidaNumero(int numero,int max , int min) {
	
	if(numero > 0 && numero < 1000000)
		return true;
	else
		return false;
}

//-=-=-=-=-=-EXCLUIR-=-=-=-=-=-
void ExcluirCodigo(ItemBiblioteca itens[], int codigo, int& cont) {

    for (int i = 0; i <= cont; i++)
        if(itens[i].codigo == codigo) {
            while(i <= cont-1) {
                itens[i] = itens[i+1];
                i++;
            }
            cont--;        
            break;
        }
}

//-=-=-=-=-=-BUSCAR-=-=-=-=-=-
bool BuscaCodigo (ItemBiblioteca itens[], int codigo, int cont) {
	
    
	
    for(int i = 0; i <= cont; i++){
	
        if(codigo == itens[i].codigo) {
            return true;
        }  
}
    return false;	
}

//-=-=-=-=-=-ORDENACAO-=-=-=-=-=-
void OrdenaCodigo(ItemBiblioteca* ordena,int cont) {
   struct ItemBiblioteca aux;
   
   for (int j = cont-1; j >= 0; j--)
        for (int i = 0; i <= j; i++)
            if (ordena[i].codigo > ordena[i+1].codigo){                            
                aux = ordena[i];
                ordena[i] = ordena[i+1];
                ordena[i+1] = aux;             
            }
}

void OrdenaTitulo(ItemBiblioteca* ordena,int cont){
   struct ItemBiblioteca aux;
   
   for (int j = cont-1; j >= 0; j--)
        for (int i=0; i<=j; i++)
            if (strcoll(ordena[i].titulo,ordena[i+1].titulo)> 0){                            
                aux = ordena[i];
                ordena[i] = ordena[i+1];
                ordena[i+1] = aux;             
            }
}

//-=-=-=-=-=-LISTAR-=-=-=-=-=-
void ListaItens(ItemBiblioteca itens[], int cont) {

    printf("-------------------------------------------------------------------------------------------------\n");
	printf("CODIGO T TITULO                          AUTOR                            EDITORA            ANO\n");
	printf("-------------------------------------------------------------------------------------------------\n");

	for(int i = 0; i <= cont; i++) {
		printf("%06d", itens[i].codigo);
		
		ImprimirEspaco(0);
		
        printf("%s", itens[i].tipo_item);
        
        ImprimirEspaco(0);
        
		printf("%s",itens[i].titulo);
		
	    ImprimirEspaco(31-strlen(itens[i].titulo));
        
        printf("%s",itens[i].nome_autor);
        
         ImprimirEspaco(31-strlen(itens[i].nome_autor));
         
          printf(" %s ", itens[i].nome_editora);
          
        ImprimirEspaco(16- strlen(itens[i].nome_editora));
        
        printf(" %d  \n", itens[i].ano_publicacao);
         
         
         
	}
	
    fflush(stdin);
	getchar();
    system("cls");
}


// Emprestimo
// -=-=-=-=-=-Cadastro-=-=-=-=-=- 
void CadastrarEmprestimo(Emprestimo emprestimo[], Usuario usuario[], ItemBiblioteca iten[], int& cont_emprestimo, int cont_usuario, int cont_iten) {

	int codigo,dia,mes,ano;
	long long int cpf;
	int input=0;
	
	// -=-=-=-=-=-CPF-=-=-=-=-=-   	   
    printf("CPF: ");
    scanf("%lli", &cpf);  		     
    fflush(stdin);
    
    printf("Codigo: ");
    scanf("%d", &codigo);  		     
    fflush(stdin);
    
    // -=-=-=-=-=-CADASTRAR CPF-=-=-=-=-=-
        
    if (ValidaCpf(cpf)) {
        if (BuscaCpf(usuario,cpf,cont_usuario)) {
        	if(BuscaCpfEmprestimo(emprestimo,cpf,cont_emprestimo)){
        		
            printf("Erro no emprestimo. Usuario ja tem emprestimo!");
            getchar();
           system("cls");
          
           
            
         }else{
         	
         	// -=-=-=-=-=-CADASTRAR CODIGO-=-=-=-=-=-
         	
         	
         	if(ValidaNumero(codigo,0,10000)){
         		if(BuscaCodigo(iten,codigo,cont_iten)){
         			if(BuscaCodigoEmprestimo(emprestimo,codigo,cont_emprestimo)){
         				
         				printf("Erro no emprestimo. Item já tem emprestimo!");
                        getchar();
                        system("cls");
                         
         				
					 }else{
					 	
					 	cont_emprestimo++;
					 	
         	            emprestimo[cont_emprestimo].cpf_emprestimo = cpf;
         	            emprestimo[cont_emprestimo].codigo_emprestimo = codigo;
         	         
         	          data_hora_atual(dia,mes,ano);
         	          
         	         emprestimo[cont_emprestimo].dia_emprestimo = dia;
         	         emprestimo[cont_emprestimo].mes_emprestimo = mes;
         	         emprestimo[cont_emprestimo].ano_emprestimo = ano;
         	         
         	         emprestimo[cont_emprestimo].dia_devolucao = dia + 7;
         	         
         	         if(dia>31){
         	         	
         	         	 emprestimo[cont_emprestimo].dia_devolucao = 31 - dia;
         	         	emprestimo[cont_emprestimo].mes_devolucao = mes + 1;
					  }else{
					  	
					  	emprestimo[cont_emprestimo].mes_devolucao = mes;
					  	
					  }
					  
         	         emprestimo[cont_emprestimo].ano_devolucao = ano;
         	         
         	         printf("\n\nEmprestimo concedido! \n");
         	         printf("Nome : %s \n",usuario[RecuperarNome(usuario,cpf,cont_usuario)].nome);
         	         printf("Titulo : %s \n",iten[RecuperarTitulo(iten,codigo,cont_iten)].titulo);
         	         printf("Data de emprestimo: %02d/%02d/%d \n",dia,mes,ano);
         	         printf("Data de devolução: %02d/%02d/%d \n",emprestimo[cont_emprestimo].dia_devolucao,emprestimo[cont_emprestimo].mes_devolucao,emprestimo[cont_emprestimo].ano_devolucao);
					 getchar();
					 
					system("cls");	
					 	
					 }
         			
				 }else{
				 	
				 	printf("Erro no emprestimo. Codigo não cadastrado!");
					getchar();
					system("cls");
					
				 	
				 }
         		
			 }else{
			 	
			 	printf("Erro no emprestimo. Codigo incorreto!");
				getchar();
				system("cls");
				
			
			 	
			 	
			 }
         	
		 }	
         
    }else{
    	
    	printf("Erro no emprestimo. Usuario não cadastrado!");
        getchar();
        system("cls");
    
	}    	
}else{
	
	printf("Erro no emprestimo. CPF incorreto!");
	getchar();
    system("cls");
		
}
        
	
	
}
//-=-=-=-=-=-EXCLUIR-=-=-=-=-=-
void Devolucao(Emprestimo emprestimo[], long long int cpf, int& cont) {

    for (int i = 0; i <= cont; i++)
        if(emprestimo[i].cpf_emprestimo == cpf) {
            while(i <= cont-1) {
                emprestimo[i] = emprestimo[i+1];
                i++;
            }
            cont--;        
            break;
        }
}

// -=-=-=-=-=-BUSCA -=-=-=-=-=-
bool BuscaCpfEmprestimo(Emprestimo emprestimo[], long long int cpf, int cont){
	
    bool result = false;
	
    for(int i = 0; i <= cont; i++)
        if(cpf == emprestimo[i].cpf_emprestimo) {
            return true;
        }  

    return result;	
}

bool BuscaCodigoEmprestimo(Emprestimo emprestimo[], int codigo, int cont){
	
    bool result = false;
	
    for(int i = 0; i <= cont; i++)
        if(codigo == emprestimo[i].codigo_emprestimo) {
            return true;
        }  

    return result;	
}

// -=-=-=-=-=-LISTAR-=-=-=-=-=- 
void ListaItensEmprestimo(Emprestimo emprestimo[], ItemBiblioteca iten[], int cont_emprestimo, int cont_iten, long long int cpf) {

	for(int i = 0; i <= cont_emprestimo; i++) {
		
		if(emprestimo[i].cpf_emprestimo == cpf){
		  
		  ImprimirEspaco(12);
		  printf("Emprestimo:");
		  ImprimirEspaco(0);
		  printf("%02d/%02d/%d",emprestimo[i].dia_emprestimo,emprestimo[i].mes_emprestimo,emprestimo[i].ano_emprestimo);
		  ImprimirEspaco(0);
		  printf("a");
		  ImprimirEspaco(0);
		  printf("%02d/%02d/%d",emprestimo[i].dia_devolucao,emprestimo[i].mes_devolucao,emprestimo[i].ano_devolucao);
		  printf("\n");
		  ImprimirEspaco(12);
		  printf("Tipo: ");
		   if( stricmp (iten[RecuperarTitulo(iten,emprestimo[i].codigo_emprestimo,cont_iten)].tipo_item,"R")==0){
		   	
		   	printf("Revista");	
		    printf("\n");
		   	
		   }else{
		   	
		   	printf("Livro");	
		    printf("\n");
		   	
		   }
		  
		  
		  ImprimirEspaco(12);
		  printf("Titulo: ");
		  printf("%s",iten[RecuperarTitulo(iten,emprestimo[i].codigo_emprestimo,cont_iten)].titulo);
		  ImprimirEspaco(0);
	      printf("\n");
       
     }
	}
}

void ListaEmprestimo(Emprestimo emprestimo[], Usuario usuario[],ItemBiblioteca iten[], int cont_emprestimo,int cont_usuario , int cont_iten){


  printf("-----------------------------------------------------------------------------------------------------\n");
  printf("CPF         Nome                            Codigo Titulo                          Emprestimo Devolução\n");
  printf("-----------------------------------------------------------------------------------------------------\n");

	for(int i = 0; i <= cont_emprestimo; i++) {

		  printf("%lli",emprestimo[i].cpf_emprestimo);
		  ImprimirEspaco(0);
		  		  
		  printf("%s",usuario[RecuperarNome(usuario,emprestimo[i].cpf_emprestimo,cont_usuario)].nome);		  
		  ImprimirEspaco(31-strlen(usuario[RecuperarNome(usuario,emprestimo[i].cpf_emprestimo,cont_usuario)].nome));
		  
		  printf("%06d",emprestimo[i].codigo_emprestimo);
		  ImprimirEspaco(0);
		  
		  printf("%s",iten[RecuperarTitulo(iten,emprestimo[i].codigo_emprestimo,cont_iten)].titulo);		  
		  ImprimirEspaco(31-strlen(iten[RecuperarTitulo(iten,emprestimo[i].codigo_emprestimo,cont_iten)].titulo));
		  
		  printf("%02d",emprestimo[i].dia_emprestimo);
		  printf("/");
		  printf("%02d",emprestimo[i].mes_emprestimo);
		  printf("/");
		  printf("%02d",emprestimo[i].ano_emprestimo);
		  ImprimirEspaco(0);
		  printf("%02d",emprestimo[i].dia_devolucao);
		  printf("/");
		  printf("%02d",emprestimo[i].mes_devolucao);
		  printf("/");
		  printf("%02d",emprestimo[i].ano_devolucao);
		  printf("\n");
	
	
}

fflush(stdin);
	getchar();
    system("cls");
}
// -=-=-=-=-=-Calcular multa -=-=-=-=-=-
int CalcularMulta (Emprestimo emprestimo[], long long int cpf,int cont_emprestimo,int dia,int mes,int ano){
 
 int result,i,devolucao,dataAtual;

	i=RecuperarData(emprestimo,cpf,cont_emprestimo);
	
	devolucao = emprestimo[i].dia_devolucao + (emprestimo[i].mes_devolucao*31 )+ (emprestimo[i].ano_devolucao*365);
	
	dataAtual=dia+(mes*31)+(ano*365);
	
		if(dataAtual>=devolucao){
			
			result =  dataAtual - devolucao;
		
			
		}else{
			
			result =  0;
			
		}
		
		return result;
		
}


int RecuperarNome(Usuario usuario[], long long int cpf,int cont){
	int result=0;
	
	for(int i=0;i<=cont;i++){
		
		if(usuario[i].cpf == cpf){
			
	      result =  i;
	      
		}
	}
	
	return result ;
}

int RecuperarTitulo(ItemBiblioteca iten[],int codigo,int cont){
	
	for(int i=0;i<=cont;i++){
		
		if(iten[i].codigo == codigo){
			
	      return i;
	      
		}
	}
	
	
}

int RecuperarData(Emprestimo emprestimo[],long long int cpf,int cont){
	
		for(int i=0;i<=cont;i++){
			
		if(emprestimo[i].cpf_emprestimo == cpf)	{
			
			return i;
		}
		
		}
}

//-=-=-=-=-=-MENU DE USUARIOS-=-=-=-=-=-
void MenuUsuario(Usuario usuario[], Emprestimo emprestimo[],ItemBiblioteca itens[], int& cont_usuario, int cont_emprestimo, int cont_iten){
	int input = 0;
	 
    do {
        printf("\n");
        printf ("Menu de Cadastro de Usuarios\n");
        printf("1 - Cadastrar novo usuario\n");
        printf("2 - Excluir usuario\n");
        printf("3 - Listar usuarios (ordenado por CPF)\n");
        printf("4 - Listar usuarios (ordenado por Nome)\n");  
		printf("5 - Voltar \n");        
        
        fflush(stdin);
        scanf("%d", &input);
        system("cls");
        
        switch(input) {
            case 1:
                CadastrarUsuario(usuario,cont_usuario);
                break;
            case 2:
                long long int cpf;
                printf("CPF: ");
        	    scanf("%lli", &cpf);
        	
                if(BuscaCpf(usuario, cpf, cont_usuario)){
                	
                	if(!BuscaCpfEmprestimo(emprestimo,cpf,cont_emprestimo)){
					
                    ExcluirCPF(usuario, cont_usuario, cpf);
                    printf("Exclusao realizada com sucesso!");
                    fflush(stdin);
                    getchar();
                 }else{
                 	printf("Erro na exclusao. Usuario possui um emprestimo!");
                    fflush(stdin);
                    getchar();
				 }
                }
                else{
                    printf("Erro na exclusao. Usuario nao cadastrado!");
                    fflush(stdin);
                    getchar();
                }
                system("cls");
                break;
            case 3:
                OrdenaCPF(usuario, cont_usuario);
                ListarUsuarios(usuario, emprestimo, itens, cont_usuario,cont_emprestimo,cont_iten);
                break;   
            case 4:
                OrdenaNome(usuario, cont_usuario);
                ListarUsuarios(usuario, emprestimo,itens, cont_usuario,cont_emprestimo,cont_iten);
                break;      
            case 5:
                system("cls");
                input = 0;
                break;
            default:
                printf ("\n Opcao invalida!\n");
                fflush(stdin);
        }
    } while(input != 0);

    system("cls");
}

//-=-=-=-=-=-MENU DE ITENS-=-=-=-=-=-
void MenuItem(ItemBiblioteca itens[], Emprestimo emprestimo[], int& cont_itens, int cont_emprestimo) {
    
    int input = 0;

    do {
    	
    	//printf("%d", cont);
    	
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
        
        switch(input) {
            case 1:
                CadastrarItem(itens, cont_itens);
                break;
            case 2:
            	  int codigo;
                
                printf("Codigo: ");
        	    scanf("%d", &codigo);
        	    fflush(stdin);
                    getchar();
        	
                if(BuscaCodigo(itens, codigo, cont_itens)) {
                		if(BuscaCodigoEmprestimo(emprestimo,codigo,cont_emprestimo)){
                    ExcluirCodigo(itens, codigo, cont_itens);
                    printf("Exclusao realizada com sucesso!");
                    fflush(stdin);
                    getchar();
                }else{
                	printf("Erro na exclusao. Item esta emprestado!");
                    fflush(stdin);
                    getchar();
				}
                }
                else{
                    printf("Erro na exclusao. Item nao cadastrado!");
                    fflush(stdin);
                    getchar();
                }
                break;
            case 3:
            	OrdenaCodigo(itens,cont_itens);
                ListaItens(itens,cont_itens);
                break;   
            case 4:
            	OrdenaTitulo(itens,cont_itens);
                ListaItens(itens,cont_itens);
                break;      
            case 5:
                system("cls");
                input = 0;
                break;
            default:
                printf ("\n Opcao invalida!\n");
                fflush(stdin);
        }
    }
    while(input != 0);
    system("cls");
}

//-=-=-=-=-=-MENU DE EMPRESTIMO-=-=-=-=-=-
void MenuEmpestimo(Emprestimo emprestimo[], Usuario usuario[],ItemBiblioteca iten[], int& cont_emprestimo,int cont_usuario,int cont_iten) {
    
    
    int input = 0;

    do {
    	
        printf("\n");
        printf ("Menu de Empréstimo\n");
        printf("1 - Emprestar item\n");
        printf("2 - Devolver item\n");
        printf("3 - Listar empréstimos\n");        
        printf("4 - Voltar \n");        
        fflush(stdin);
        scanf("%d", &input);
        system("cls");
        
        switch(input) {
            case 1:
                CadastrarEmprestimo(emprestimo, usuario, iten, cont_emprestimo, cont_usuario, cont_iten);
                break;
            case 2:
            	int dia,mes,ano;
            	int prazo;
            	float taxa;
            	long long int cpf;
            	
            	taxa=1.50;
            	 
            	  printf("CPF: ");
        	    scanf("%lli", &cpf);
        	    
        	    if(BuscaCpf(usuario, cpf, cont_usuario)){
        	      if(BuscaCpfEmprestimo(emprestimo,cpf,cont_emprestimo)){
        	      	
        	   
        	    
        	    printf("Dia: ");
        	    scanf("%d", &dia);
        	    
        	    printf("Mês: ");
        	    scanf("%d", &mes);
        	    
        	    printf("Ano: ");
        	    scanf("%d", &ano);
        	    
        	      	prazo = CalcularMulta(emprestimo,cpf,cont_emprestimo,dia,mes,ano);
        	      	
        	      	if(prazo==0){
        	      		Devolucao(emprestimo,cpf,cont_emprestimo);
        	      		printf("\nDevolucao realizada com sucesso no prazo!");
        	      		fflush(stdin);
        	      		getchar();        	      		
        	      		system("cls");
        	      		
					  }else{
					  	Devolucao(emprestimo,cpf,cont_emprestimo);
					  	
					  	printf("Nome : %s \n",usuario[RecuperarNome(usuario,cpf,cont_usuario)].nome);
         	            printf("Titulo : %s \n",iten[RecuperarTitulo(iten,emprestimo[cont_emprestimo].codigo_emprestimo,cont_iten)].titulo);
					  	printf("Data de devolução: %02d/%02d/%d \n",emprestimo[cont_emprestimo].dia_devolucao,emprestimo[cont_emprestimo].mes_devolucao,emprestimo[cont_emprestimo].ano_devolucao);
					  	
					  	printf("\n\nDevolucao realizada com atraso de %d dia(s).\n",prazo);
					  	printf("Multa de R$ %.2f \n", prazo*taxa);
					  	fflush(stdin);
					  		getchar();        	      		
        	      		system("cls");
					  }
        	      	
        	      	
				  }else{
				  	printf("Usuario nao tem emprestimo!");
				  	fflush(stdin);
        	      		getchar();        	      		
        	      		system("cls");
				  }	
				}else{
					printf("Usuario não cadastrado!");
				     	fflush(stdin);
        	      		getchar();        	      		
        	      		system("cls");
				}
				
            	  break;                
            case 3:
            	ListaEmprestimo(emprestimo,usuario,iten,cont_emprestimo,cont_usuario,cont_iten);           
                break;                 
            case 4:
                system("cls");
                input = 0;
                break;
            default:
                printf ("\n Opcao invalida!\n");
                fflush(stdin);
        }
    }
    while(input != 0);
    system("cls");
}


   
   
//Main
      
 int main(){
	
	setlocale(LC_ALL, "Portuguese");
    
    int input;
    
    int cont_usuario = -1;
    int cont_itens = -1;
    int cont_emprestimo= -1;
    
    Usuario usuario[10];    
    ItemBiblioteca itens[10];
    Emprestimo emprestimo[10];
	

	
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
                MenuUsuario(usuario,emprestimo,itens, cont_usuario,cont_emprestimo,cont_itens);
                break;
            case 2:
            	MenuItem(itens,emprestimo, cont_itens,cont_emprestimo);                
                break;
            case 3:
                MenuEmpestimo(emprestimo,usuario,itens,cont_emprestimo,cont_usuario,cont_itens);
                break;        
            case 4:
                exit(EXIT_SUCCESS);
            default:
                printf ("\nOpção inválida!\n");
                fflush(stdin);
                
        }
    } while(input != 0);
    system("cls");
}
