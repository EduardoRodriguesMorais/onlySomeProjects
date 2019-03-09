#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int tryMov(int i, int x, int y, int dx[], int dy[], int table[][8]);
void imprime(int table[][8]);

int main(int argc, char *argv[])
{
	int dx[8], dy[8], table[8][8], i, j; //Movimentos do cavalo
	dx[0] = 2;
	dx[1] = 1;
	dx[2] = -1;
	dx[3] = -2;
	dy[0] = 1;
	dy[1] = 2;
	dy[2] = 2;
	dy[3] = 1;
	dx[4] = -2;
	dx[5] = -1;
	dx[6] = 1;
	dx[7] = 2;
	dy[4] = -1;
	dy[5] = -2;
	dy[6] = -2;
	dy[7] = -1;

	for (i = 0; i < 8; i++)
	{
		printf("%d", i);
		for (j = 0; j < 4; j++)
		{
			printf("%d", j);
			table[i][j] = 0;
		}
	}

	return 0;
	table[0][0] = 1;
	tryMov(2, 0, 0, dx, dy, table);
	imprime(table);

	return 0;
}

int tryMov(int i, int x, int y, int dx[], int dy[], int table[][8])
{
	int totalCasas = 8 * 8; // Total de casas no tabuleiro
	int k = 0, u, v, done = 0;
	if (i == 65)
	{
		imprime(table);
		return 1;
	}
	if (i > totalCasas)
	{ //Verifica a quantidade de movimentos.
		done = 1;
	}
	while (!done && k < 8)
	{
		u = x + dx[k];
		v = y + dy[k];
		if ((u >= 0 && u <= 7) && (v >= 0 && v <= 7))
		{ //Aceita se estiver dentro do tabuleiro e a casa ainda n�o tiver sido visitada
			if (table[u][v] == 0)
			{
				table[u][v] = i;
				imprime(table);
				if (!tryMov(i + 1, u, v, dx, dy, table))
				{
					table[u][v] = 0; //Sem sucesso, descarta movimento
				}
				else
				{
					return 1;
				}
			}
		}
		k++;
	}
	return 0;
}

void imprime(int table[][8])
{
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			printf("  %d  |", table[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");
}
