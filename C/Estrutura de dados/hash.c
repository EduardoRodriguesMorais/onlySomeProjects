// Sintese
//   objetivo "Hash - Distribua os 22 nomes em 44 posi??es com no m?ximo 11 colis?es 
//   data "03/11/2016"
//   autor "Edson F. da Fonseca & Turma de EDA 2016/2"

#include <stdio.h>

typedef struct tDado {
  char matricula[11];
  char nome[50];
};

typedef struct tHash {
  struct {
  	int colisao; // -1=vazio; 0..N=qtd de colisoes
  	struct tDado dado;
  } tabelaDispersao[44];	
  int posicaoLivre;
  struct tDado tabelaColisao[21];
};

// Prototipos

void inicializar(struct tHash *esp) {
  int i;
  (*esp).posicaoLivre = 0;
  for (i=0;i<44;i++)
    (*esp).tabelaDispersao[i].colisao = -1;
}

int hash(char nome[]) {
  int i, valor=0;
  
  for (i=0;i<strlen(nome);i++) {
  	switch (nome[i]) {
  	  case 'A': valor += 2; break;
  	  case 'E': valor += 3; break;
  	  case 'I': valor += 7; break;
  	  case 'O': valor += 5; break;
  	  case 'U': valor += 11; break;
  	  default: valor += 1; break;
	}
  }
	
  return valor % 44;	
}

void incluir(struct tHash *esp, struct tDado dado) {
  int posicao = hash(dado.nome);
  
  if ((*esp).tabelaDispersao[posicao].colisao++ == -1) // livre
    (*esp).tabelaDispersao[posicao].dado = dado;
  else
    (*esp).tabelaColisao[(*esp).posicaoLivre++] = dado;
}

int main(void) {
  int i, pN, pM;
  char str[60];
  struct tDado dado;
  struct tHash espalhamento;
  FILE *arq = fopen("alunos.txt","r");
  
  if (arq == NULL) {
    printf("Erro de abertura do arquivo alunos.txt");
    return 1;
  }
  
  inicializar(&espalhamento);
  
  while (fgets(str, 60, arq)) {
  	pN = pM = 0;
	for (i=0;i<strlen(str);i++) {
  	  if (i < 10)
  	    dado.matricula[pM++] = str[i];
  	  else
  	    dado.nome[pN++] = str[i];
	}
    dado.matricula[10] = '\0';
    dado.nome[pN-1] = '\0';
    //printf("--> %s - %s\n", dado.matricula, dado.nome);
    incluir(&espalhamento, dado);
  }
  fclose(arq);
	
  printf("Colisoes: %d\n", espalhamento.posicaoLivre);
  printf("Dispersao:\n");
  for (i=0;i<44;i++)  {
    printf("[%d] - Colisao: %d\n", i, espalhamento.tabelaDispersao[i].colisao);
  }
    
  printf("Colisao:\n");
  for (i=0;i<espalhamento.posicaoLivre;i++){
    printf("[%d] - Nome: %s\n", i, espalhamento.tabelaColisao[i].nome);
  }
  
  return 0;
}