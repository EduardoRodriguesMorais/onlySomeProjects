#include <stdio.h>
#include <stdlib.h>
#define tam_bucket 100
#define num_bucket 10


typedef struct {
	int topo;
	int balde[tam_bucket];
}bucket;

typedef struct data {
	int chave;
}data;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void heapSort(int A[], int tam);
void radixSort(int A[], int tam);
void coutingSort(struct data A[], int tam, int max);
void bucketSort(int A[], int tam);
void quickSort(int A[], int ini, int fim);
void merge(int vetor[], int comeco, int meio, int fim);
void mergeSort(int A[], int ini, int fim);
void shellSort(int *vet, int size);
void insertionSort(int A[], int tam); 
void selectionSort(int vet[], int n);
void bubbleSort(int vet[], int n);

int main(int argc, char *argv[]) {
	

	
	return 0;
}

void bubbleSort(int vet[], int n){
	int i, j,x;
	for (i=0; i<n; i++) {
		for (j=1; j<n; j++) {
			if (vet[j-1] > vet[j]) {
				x = vet[j-1];
				vet[j-1] = vet[j];
				vet[j] = x;
			}
		}
	}
	
}

void selectionSort(int vet[], int n){
	int i, j,x,k;
	for (i=0; i<n; i++) {
		k = i;
		x = vet[i];
		for (j=1; j<n; j++) {
			if (vet[j] < x) {
				k = j;
				x = vet[k];
			}
		}
		vet[k] = vet[i];
		vet[i] = x;
	}
}

void insertionSort(int A[], int tam) {
	int i, j, aux;
	for (j=1; j<tam; j++) {
		aux = A[j];
		i = j-1;
		while ((i >= 0) && (A[i] > aux)){
			A[i+1] = A[i--];
		}
		A[i+1] = aux;
	}
}
/*
	EXERCICIO  1:
	Shell Sort utilisa um método de inserção direta. O algoritmo difere do método de inserção direta pelo fato de no lugar de considerar o array a ser ordenado como um único segmento,
	ele considera vários segmentos sendo aplicado o método de inserção direta em cada um deles. Basicamente o algoritmo passa várias vezes pela lista dividindo o grupo maior em menores. 	
*/

void shellSort(int *vet, int size) {
    int i , j , value;
    int gap = 1;
    while(gap < size) {
        gap = 3*gap+1;
    }
    while ( gap > 1) {
        gap /= 3;
        for(i = gap; i < size; i++) {
            value = vet[i];
            j = i;
            while (j >= gap && value < vet[j - gap]) {
                vet[j] = vet [j - gap];
                j = j - gap;
            }
            vet [j] = value;
        }
    }
}

void mergeSort(int A[], int ini, int fim) {
	int meio;
	if (ini < fim) {
		meio = (ini+fim)/2;
		mergeSort(A, ini, meio);
		mergeSort(A, meio+1, fim);
		merge(A, ini, meio, fim);
	}
}

void merge(int vetor[], int comeco, int meio, int fim) {
    int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    int *vetAux;
    vetAux = (int*)malloc(tam * sizeof(int));

    while(com1 <= meio && com2 <= fim){
        if(vetor[com1] < vetor[com2]) {
            vetAux[comAux] = vetor[com1];
            com1++;
        } else {
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio){  //Caso ainda haja elementos na primeira metade
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {   //Caso ainda haja elementos na segunda metade
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++){    //Move os elementos de volta para o vetor original
        vetor[comAux] = vetAux[comAux-comeco];
    }
    
    free(vetAux);
}

void quickSort(int A[], int ini, int fim){
	int i=ini, f=fim, pivo=A[ini], aux;
	do{
		while(A[i] < pivo) i++;
		while(A[f] > pivo) f--;
		if (i <= f){
			aux=A[i];
			A[i++] = A[f];
			A[f--] = aux;
		}
	} while (i <= f);
	if (ini < f){
		quickSort(A, ini, f);	
	}
	if (i < fim){
		quickSort(A, i, fim);
	}
}

void bucketSort(int A[], int tam) {
	bucket b[num_bucket];
	int i,j,k,v[num_bucket];
	for(i=0; i<num_bucket; i++)
		b[i].topo=0;
	for(i=0; i<tam; i++) {
		j = (num_bucket)-1;
		while (1) {
			if (j<0)
				break;
			if (v[i] >= j*10) {
				b[j].balde[b[j].topo] = v[i];
				(b[j].topo)++;
				break;
			}
			j--;
		}
	}
	for (i=0; i<num_bucket; i++)
		if(b[i].topo)
			bubbleSort(b[i].balde,b[i].topo);
		i=0;
		for(j=0; j<num_bucket; j++) {
			for(k=0; k<b[j].topo; k++) {
				v[i] = b[j].balde[k];
				i++;
		}
	}
}

void coutingSort(struct data A[], int tam, int max) {
	int aux[max+1], i;
	struct data B[tam-1];
	for(i=0; i<max+1; i++){
		aux[i] = 0;	
	}
	for(i=0; i<tam; i++){
		aux[A[i].chave]++;
	}
	for(i=1; i<max+1; i++){
		aux[i] += aux[i-1];
	}
	for(i=tam-1; i>=0; i--){
		B[--aux[A[i].chave]] = A[i];
	}
	for(i=0; i<tam; i++){
		A[i] = B[i];
	}
}
void radixSort(int A[], int tam) {
	int i, maior=A[0], exp=1, b[tam];
	for (i=1; i<tam; i++)
		if (A[i] > maior)
			maior = A[i];
	while (maior/exp > 0) {
		int deck[10] = {0};
		for(i=0; i<tam; i++){
			deck[(A[i]/exp)%10]++;	
		}
		for(i=1; i<10; i++){
			deck[i] += deck[i-1];
		}
		for(i=tam-1; i>=0; i--){
			b[--deck[(A[i]/exp)%10]] = A[i];
		}
		for(i=0; i<tam; i++){
			A[i] = b[i];
		}
		exp *= 10;
	}
}


void heapSort(int A[], int tam) {
 int i=tam/2, pai, filho, t;
	while (1) {
		if (i > 0) {
			i--;
			t = A[i];
		}
	 	else {
		 	tam--;
		}if (tam == 0){
			return;
		}
		t = A[tam];	 	
		A[tam] = A[0];
	}
	t = A[tam];
	A[tam] = A[0];
	pai = i;
	filho = (i * 2) + 1;
	while (filho < tam) {
		if ((filho+1 < tam) && (A[filho+1] > A[filho])){
			filho++;
		}
		if (A[filho] > t) {
			A[pai] = A[filho];
			pai = filho;
			filho = (pai * 2) + 1;
		}else{
			break;
		}
		A[pai] = t;
	}
}
