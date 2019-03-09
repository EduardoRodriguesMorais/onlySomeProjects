#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MENOR_IGUAL 3
#define MAIOR_IGUAL 2
#define IGUAL_IGUAL 1

/* Prototipos */

void apresentaVtrX(int **mtz, int qtdC);
void apresentaModelo(char **mtz, int qtdC, int qtdL);
char ** alocaMatrizChar(int qtdL, int qtdC);
void apresentaVlrVarRest(int **mtz, int qtdL, int qtdC);
void apresentaVlrMtzCoeficientes(int **mtz, int qtdL, int qtdC);
void apresentaMtzModelo(int **mtzCoeficientes, int *funcObjeva, int qtdL, int qtdC);
void leValidaOpcao(char *msn, char *msnErro, char *opcoesValidas, char *opcao);
FILE *abreArq (char *nomeArq, char *modoAbertura, char *msgErro);
void populaDados(int **mtz,int *funcObjeva,int *igualdadeModelo,int qtdL, int qtdC);
int **alocaMatriz (int qtdL, int qtdC);
int validaVariavel(char *str);
void verificaLinhasColunas(int *qtdL, int *qtdC);
void apresentaValoresMatriz(int **mtz, int qtdC, int qtdL);
int *alocaVetor(int qtd);
void apresentaValoresVetor(int *vet, int qtdP);
void apresentaVlrFuncObj(int *funcObjeva, int qtd);
void transformaModeloDual(int **mtzCoeficientes,int qtdL ,int qtdC , int *funcObjeva,int qtdFO, int *igualdadeModelo,int qtdIGM);

int main(int argc, char *argv[]) {
	char opcao, **modelo;
	int **mtz, *funcObjeva, *igualdadeModelo, qtdL=-1, qtdC=1;
	
	verificaLinhasColunas(&qtdL,&qtdC);
	modelo = alocaMatrizChar(qtdL, qtdC); 
	mtz = alocaMatriz(qtdL, qtdC);
	funcObjeva = alocaVetor(qtdC-1);
	igualdadeModelo = alocaVetor(qtdL);
	populaDados(mtz,funcObjeva, igualdadeModelo, qtdL, qtdC);
	
	do{
		leValidaOpcao("MENU:\n\n1 - Apresentar Modelo \n2 - Matrizes do modelo  \n3 - Modelo Dual   \n4 - Exit\n","Opcao invalida.","1234",&opcao);
		switch(opcao){
			case '1':
				apresentaModelo(modelo,qtdC,qtdL);
				break;
			case '2':
				apresentaMtzModelo(mtz, funcObjeva, qtdL, qtdC);
				break;		
			case '3':
				transformaModeloDual(mtz,qtdL ,qtdC , funcObjeva,qtdC-1, igualdadeModelo,qtdL);
				break;		
		}
		system("cls");
	}while(opcao!='4');
	
	
	return 0;
}

//Objetivo: Transformar modelo em dual
//Parâmetro: 
//Retorno:

void transformaModeloDual(int **mtzCoeficientes,int qtdL ,int qtdC , int *funcObjeva,int qtdFO, int *igualdadeModelo,int qtdIGM){
	int **mtzDual, x, y, auxL=0,auxC=0,auxFO=0;
	
	mtzDual = alocaMatriz(qtdL,qtdC);

	for(x=0 ; x<qtdL ; x++){
		auxL=0;
		for(y=0 ; y<qtdC ; y++){
			if(y == qtdC-1){
				mtzDual[x][y] = funcObjeva[auxFO];
				auxFO++;
			}else{
				mtzDual[x][y] = mtzCoeficientes[auxL][auxC];
			}
			auxL++;
		}
		auxC++;
	}
	system("cls");	
	apresentaValoresMatriz(mtzDual,auxL,auxC);
	getch();
}

//Objetivo: Apresentar matrizes que compóem o modelo
//Parametros: Matriz com valores do modelo, vetor com variaveis de
//Retorno: Vetor com devida quantidade de posições
void apresentaMtzModelo(int **mtzCoeficientes, int *funcObjeva, int qtdL, int qtdC){
	system("cls");
	printf("Matrizes que compoem o modelo: \n");
	apresentaVtrX(mtzCoeficientes, qtdC); //MTZ X
	apresentaVlrMtzCoeficientes(mtzCoeficientes, qtdL, qtdC); //<MTZ A
	apresentaVlrVarRest(mtzCoeficientes, qtdL, qtdC); //MTZ B
	apresentaVlrFuncObj(funcObjeva, qtdC);		// MTZ C
	getch();
}


//Objetivo: Apresentar valores da função objetiva
//Parametros: Ponteiro do vetor e a quantidade de valores
void apresentaVtrX(int **mtz, int qtdC){
	int x,y = qtdC-1;
	printf("\nX: [ ");
	for (x = 0; x < qtdC-1; x++){
		if(x != qtdC-2){
			printf("X%d, ",x+1);
		}else{
			printf("X%d ",x+1);
		}
	}
	printf("] \n");
}

//Objetivo: Apresentar valores da função objetiva
//Parametros: Ponteiro do vetor e a quantidade de valores
void apresentaVlrMtzCoeficientes(int **mtz, int qtdL, int qtdC){
	int x,y;
	printf("\nA: [ ");
	for (x = 0; x < qtdL; x++){
		for (y = 0; y < qtdC-1; y++){
			if(y != qtdC-2){
				printf("%d, ",mtz[x][y]);
			}else if(x != qtdL-1){
				printf("%d | ",mtz[x][y]);
			}else{
				printf("%d ",mtz[x][y]);
			}		
		}
	}
	printf("] \n");
}

//Objetivo: Apresentar valores da função objetiva
//Parametros: Ponteiro do vetor e a quantidade de valores
void apresentaVlrVarRest(int **mtz, int qtdL, int qtdC){
	int x,y = qtdC-1;
	printf("\nB: [ ");
	for (x = 0; x < qtdL; x++){
		if(x != qtdL-1){
			printf("%d, ",mtz[x][y]);
		}else{
			printf("%d ",mtz[x][y]);
		}	
	}
	printf("] \n");
}


//Objetivo: Apresentar valores da função objetiva
//Parametros: Ponteiro do vetor e a quantidade de valores
void apresentaVlrFuncObj(int *funcObjeva, int qtd){
	int x;
	printf("\nC: [ ");
	for (x = 0; x < qtd-1; x++){
		if(x != qtd-2){
			printf("%d, ",funcObjeva[x]);	
		}else{
			printf("%d ",funcObjeva[x]);
		}
	}
	printf("] \n");
}

//Objetivo: Alocação dinámica para vetor
//Parametros: Quantidade de posições que o vetor deve possuir
//Retorno: Vetor com devida quantidade de posições
int *alocaVetor(int qtd){
	int *vetor = (int *) malloc (qtd * sizeof(int *));
	return vetor;
}

//Objetivo: Alocação dinámica para matriz 
//Parametros: Quantidade de linhas e Colunas que a matriz deve possuir
//Retorno: Matriz com a devida quantidade de linhas de colunas
char ** alocaMatrizChar(int qtdL, int qtdC){
	int i,j;
	char **mtz = (char**)malloc(qtdL * sizeof(char*)); 
	
	for (i = 0; i < qtdL; i++){ //Percorre as linhas do Vetor de Ponteiros
		mtz[i] = (char*) malloc(qtdC * sizeof(char)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		for (j = 0; j < qtdC; j++){ //Percorre o Vetor de Inteiros atual.
			mtz[i][j] = 0; //Inicializa com 0.
		}
	}
	
	return mtz; 
}

//Objetivo: Alocação dinámica para matriz 
//Parametros: Quantidade de linhas e Colunas que a matriz deve possuir
//Retorno: Matriz com a devida quantidade de linhas de colunas
int ** alocaMatriz (int qtdL, int qtdC){
	int i,j;
	int **mtz = (int**)malloc(qtdL * sizeof(int*)); 
	
	for (i = 0; i < qtdL; i++){ //Percorre as linhas do Vetor de Ponteiros
		mtz[i] = (int*) malloc(qtdC * sizeof(int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
		for (j = 0; j < qtdC; j++){ //Percorre o Vetor de Inteiros atual.
			mtz[i][j] = 0; //Inicializa com 0.
		}
	}
	
	return mtz; 
}

//Objetivo: Verificar a quantidade de linhas de colunas da matriz
//Parametros: Um ponteiro pra quantidade de linhas de Colunas
//Retorno: Valores aos ponteiros
void verificaLinhasColunas(int *qtdL, int *qtdC){
	char ch;
	FILE *arq = abreArq("modelo.txt","r","Erro ao abrir arquivo");
	while( (ch=fgetc(arq)) != EOF ){
		if(ch == 'x' && *qtdL == 0 ){
			*qtdC+=1;
		}else if(ch == '\n'){
			*qtdL+=1;
		}
	}
	fclose(arq);
}

//Objetivo: Le valores de uma variavel de acordo com o Modelo Simplex
//Parametros: Uma string
//Retorno: Valor em inteiro que essa string representa para o modelo
int validaVariavel(char *str){
	int i =0, aux = 0;
	char vet[10];
	for(i=0; i < strlen(str); i++){
		if(isdigit(str[i])){
			aux = 1;
			vet[i] = (int) str[i];
		}else{
			break;
		}
	}
	if(aux == 1){
		return atoi(vet);	
	}else{
		return -1;
	}
}

//Objetivo: Popular dados 
//Parametros: Matriz de vakires para modelo, vetor de função objetiva, vetor de igualdades do modelo, quantidade de linhas e colunas da matriz
void populaDados(int **mtz,int *funcObjeva,int *igualdadeModelo,int qtdL, int qtdC){
    int contL=0,aux, auxVet = 0, auxL=0, auxC=0, sa = 0, flag=0;
	char str[50] ;
	FILE *arq = abreArq("modelo.txt","r","Erro ao abrir arquivo");
	while( (fscanf(arq,"%s\n", &str))!=EOF){
		if(!strcmp(str,"sa")){
			sa = 1;
		}
		aux = validaVariavel(str);
		if( aux != -1 ){
			if(sa == 1){
				if(auxL < qtdL){
					if(auxC < qtdC){		
						mtz[auxL][auxC] = aux;
						auxC++;
					}else{
						auxC=0;
						auxL++;	
						if(auxL == qtdL){
							break;
						}
						mtz[auxL][auxC] = aux;
						auxC++;
					}
				}	
			}else{
				funcObjeva[auxVet] = aux;
				auxVet++;
			}
		}else{
			if(	auxL != qtdL-1 ) {
				flag = verificaOperador(str); 
				if(flag != 0){
					igualdadeModelo[contL] = flag;
					contL++;
					flag = 0;	
				}
				
			}
		}
	}
	fclose(arq);
}

//Objetivo: Verificar qual Operador matemático a string representa 
//Parâmetro: String 
//Retorno: Inteiro correspondente: MENOR_IGUAL 3, MAIOR_IGUAL 2, IGUAL_IGUAL 1, retorna 0 se não for um operador

int verificaOperador(char *str){
	if(!strcmp(str,"<=")){
		return MENOR_IGUAL;
	}else if(!strcmp(str,">=")){
		return MAIOR_IGUAL;
	}else if(!strcmp(str,"==")){
		return IGUAL_IGUAL;
	}else{
		return 0;
	}
}

//Objetivo: Apresentar valode de um vetor
//Parametros: Vetor, quantidade de posições
void apresentaValoresVetor(int *vet, int qtdP){
	int x; 
	
	for (x = 0; x < qtdP; x++){
		printf("|  %d  ",vet[x]);
	}
}

//Objetivo: Apresentar modelo
//Parametros: Matriz, quantidade de linhas e colunas
void apresentaModelo(char **mtz, int qtdC, int qtdL){
	int x=0; 
	char str[50];
	FILE *arq = abreArq("modelo.txt","r","Erro ao abrir arquivo");
	system("cls");
	printf("Modelo: \n\n");
	while ((fgets(str, sizeof(str), arq))!=NULL){
		printf("%s",str);
	}
	fclose(arq);
	getch();
}


//Objetivo: Apresentar valode de uma Matriz
//Parametros: Matriz, quantidade de linhas e colunas
void apresentaValoresMatriz(int **mtz, int qtdC, int qtdL){
	int x, y; 

	for (x = 0; x < qtdL; x++){
		for (y = 0; y < qtdC; y++){
			printf("|  %d  ",mtz[x][y]);
		}
		printf("\n");
	}
}

//Objetivo: abrir um arquivo
//Parametros: referencia ao nome do arquivo , ao modo de abertura e a mensagem de erro
//Retorno: endereco da stream arquivo ou null 
FILE *abreArq (char *nomeArq, char *modoAbertura, char *msgErro){
	FILE *arq;
	
	arq=fopen(nomeArq,modoAbertura);
	if(arq==NULL){
		printf(msgErro);
	}
	
	return arq;
}

// Objetivo: Ler uma opcao 
// Parâmetros: endereco de memoria  da string  mensagem, mensagem de erro e das opcoes validas e endereço da opcao
// Retorna: opcao valida
void leValidaOpcao(char *msn, char *msnErro, char *opcoesValidas, char *opcao) {
        
	do {
		printf(msn);
		fflush(stdin);
		*opcao = toupper(getch());
		if(strchr(opcoesValidas, *opcao) == NULL) {
			printf("%s\n", msnErro);
			getch();
			system("cls");
		}
	} while(strchr(opcoesValidas, *opcao) == NULL);

}