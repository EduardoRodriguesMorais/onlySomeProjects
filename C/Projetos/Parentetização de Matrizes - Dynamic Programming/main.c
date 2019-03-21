#include <stdio.h>
#include <stdlib.h>
#define MAX_INT 99999
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void escreva (int s[][6],int i, int j);

//Programação dinâmica 
int main(int argc, char *argv[]) {
		
	int i, j, k, l, q, n,max;
	
	int p[] = {30, 35, 15, 5, 10, 20, 25};
	n = 6;
	int m[n][n], s[n][n]; // 
	for (i=0; i<n; i++){
		m[i][i] = 0;
	}
	for (l=1; l<n; l++) {
		for (i=0; i<n-l; i++) {
			j = i + l;
			m[i][j] = MAX_INT;
			for (k=i; k<j; k++) {
				q = m[i][k] + m[k+1][j] + (p[i]*p[k+1]*p[j+1]);
				if (q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k+1;
				}
			}
		}
	}
	printf("Multiplicacoes: %d\n", m[0][n-1]);
	
	printf("Ordem otima de multiplicacao: ");
	escreva (s,0,n-1);
	
	return 0;
}


void escreva (int s[][6],int i, int j){
	if (i == j){
		printf("A%d ", (i+1));
	}else{
		printf("(");
		escreva(s,i, s[i][j]-1);
		escreva(s,s[i][j],j);
		printf(")");
	}
	
}



