#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <locale.h>

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

// MENU
void MenuUsuario(Usuario usuario[], int& cont);
void MenuIten(ItemBiblioteca itens[], int& cont);

// CADASTRAR
void CadastrarUsuario(Usuario usuario[], int& cont);
void  CadastrarItem(ItemBiblioteca itens[], int& cont);

// LISTAR
void ListarUsuarios(Usuario usuario[],int cont);

// EXCLUIR
void ExcluirCPF(Usuario* excluir, int& cont, long long int cpf);

// Maiuscula
void StringMaiuscula(char* string);


//VALIDAR
bool ValidaCpf(long long int cpf);
bool ValidarString(char string[], int menor, int maior);

//BUSCA
bool BuscaCpf(Usuario usuario[],long long int cpf,int cont);

// USUARIO
// -=-=-=-=-=-Cadastro-=-=-=-=-=-
void CadastrarUsuario(Usuario usuario[], int& cont) {
	    
    int input = 0;
    long long int cpf;
	char nome[30];

    // -=-=-=-=-=-CPF-=-=-=-=-=-   	   
    printf("CPF: ");
    scanf("%lli", &cpf);  		     
    fflush(stdin);
        
    if (ValidaCpf(cpf)) {
        if (BuscaCpf(usuario,cpf,cont)) {
            printf("Erro no cadastro. CPF ja cadastrado!");
            getchar();
            MenuUsuario(usuario,cont);
        } 
        else {
            cont++;
            usuario[cont].cpf = cpf;  
        }
    }
    else {
        printf("Erro no cadastro!");
        MenuUsuario(usuario,cont);
    }
    	
	// -=-=-=-=-=-NOME-=-=-=-=-=-
	do {
	 	printf("Nome: ");
        gets(nome);
        fflush(stdin);
        StringMaiuscula(nome);
        
        if(ValidarString(nome, MIN_LEN_STRING, MAX_LEN)) {
        	strcpy(usuario[cont].nome, nome);
            printf("Cadastro realizado com sucesso!");	
            getchar();
            system("cls");
        	
		} else {
			printf("Erro");
			getchar();
			fflush(stdin);
		}
	} while(!ValidarString(nome, MIN_LEN_STRING, MAX_LEN));
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
   
   printf("%d ordenado por nome \n",cont);
   
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
void ListarUsuarios(Usuario usuario[], int cont){
	
	printf("--------------------------------------------------\n");
	printf("CPF         Nome\n");
	printf("--------------------------------------------------\n");

	for(int i = 0; i <= cont; i++) {
		printf("%lli", usuario[i].cpf);
		ImprimirEspaco(1);
		printf("%s", usuario[i].nome);
		printf("\n");	
	}
	
    fflush(stdin);
	getchar();
    system("cls");
}

// ITENS

//-=-=-=-=-=-CADASTRAR-=-=-=-=-=-
void CadastrarItem(ItemBiblioteca itens[], int& cont) {

    itens[0].codigo = 012345;
    strcpy(itens[0].tipo_item,"L");
    strcpy(itens[0].titulo, "Menino Maluquinho");
    strcpy(itens[0].nome_autor, "Ziraldo");
    strcpy(itens[0].nome_editora, "Ed. Melhoramentos");
    itens[0].ano_publicacao = 1980;

    itens[1].codigo = 123456;
    strcpy(itens[1].tipo_item, "L");
    strcpy(itens[1].titulo, "Diario de um Banana");
    strcpy(itens[1].nome_autor, "Jeff Kinney");
    strcpy(itens[1].nome_editora, "New York Times");
    itens[1].ano_publicacao = 2007;

    itens[2].codigo = 234567;
    strcpy(itens[2].tipo_item, "R");
    strcpy(itens[2].titulo, "Mundo Estranho");
    strcpy(itens[2].nome_autor, "  ");
    strcpy(itens[2].nome_editora, "Abril");
    itens[2].ano_publicacao = 2013;

    itens[3].codigo = 345678;
    strcpy(itens[3].tipo_item, "R");
    strcpy(itens[3].titulo, "Epoca");
    strcpy(itens[3].nome_autor, "  ");
    strcpy(itens[3].nome_editora, "Globo");
    itens[3].ano_publicacao = 2021;
	
   cont=3;
}

//-=-=-=-=-=-VALIDACAO-=-=-=-=-=-
bool ValidaCodigo(int codigo) {
	
	if(codigo > 0 && codigo < 1000000)
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


//-=-=-=-=-=-LISTAR-=-=-=-=-=- /*APOS EMPRESTIMO*/
void ListaItens(ItemBiblioteca itens[], int cont) {

    printf("-------------------------------------------------------------------------------------------------\n");
	printf("CODIGO T TITULO                          AUTOR                          EDITORA            ANO\n");
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

//-=-=-=-=-=-MENU DE USUARIOS-=-=-=-=-=-
void MenuUsuario(Usuario usuario[], int& cont){
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
                CadastrarUsuario(usuario,cont);
                break;
            case 2:
                long long int cpf;
                printf("CPF: ");
        	    scanf("%lli", &cpf);
        	
                if(BuscaCpf(usuario, cpf, cont)){
                    ExcluirCPF(usuario, cont, cpf);
                    printf("Exclusao realizada com sucesso!");
                    fflush(stdin);
                    getchar();
                }
                else{
                    printf("Erro na exclusao. Usuario nao cadastrado!");
                    fflush(stdin);
                    getchar();
                }
                break;
            case 3:
                OrdenaCPF(usuario, cont);
                ListarUsuarios(usuario, cont);
                break;   
            case 4:
                OrdenaNome(usuario, cont);
                ListarUsuarios(usuario, cont);
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
void MenuItem(ItemBiblioteca itens[], int& cont) {
    
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
                CadastrarItem(itens, cont);
                break;
            case 2:
            	  int codigo;
                
                printf("Codigo: ");
        	    scanf("%d", &codigo);
        	
                if(BuscaCodigo(itens, codigo, cont)) {
                	
                    ExcluirCodigo(itens, codigo, cont);
                    printf("Exclusao realizada com sucesso!");
                    fflush(stdin);
                    getchar();
                }
                else{
                    printf("Erro na exclusao. Item nao cadastrado!");
                    fflush(stdin);
                    getchar();
                }
                break;
            case 3:
            	OrdenaCodigo(itens,cont);
                ListaItens(itens,cont);
                break;   
            case 4:
            	OrdenaTitulo(itens,cont);
                ListaItens(itens,cont);
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
   
//Main
      
 int main(){
	
	setlocale(LC_ALL, "Portuguese");
    
    int input;
    
    int cont_usuario = -1;
    int cont_itens = -1;
    
    Usuario usuario[10];    
    ItemBiblioteca itens[10];
	
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
                MenuUsuario(usuario,cont_usuario);
                break;
            case 2:
            	MenuItem(itens, cont_itens);                
                break;
            case 3:
                printf("Menu 3\n");
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
