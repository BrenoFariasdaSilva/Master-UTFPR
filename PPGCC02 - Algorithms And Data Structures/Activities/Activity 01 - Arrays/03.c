/*
 * Descrição:
 *   Gera uma matriz M x N preenchida com 0s e 1s aleatórios.
 *   Exibe todos os elementos com valor 1 que estão cercados apenas por 0s.
 *
 * Entradas:
 *   - Dois inteiros M e N representando as dimensões da matriz.
 *
 * Saídas:
 *   - Posições na matriz que contêm 1 e estão rodeadas apenas por 0s.
 *
 * Passos:
 *   1. Ler as dimensões M e N.
 *   2. Preencher a matriz com 0s e 1s aleatórios.
 *   3. Verificar quais elementos 1 estão cercados apenas por 0s.
 *   4. Exibir essas posições.
 *
 * Autor: Breno Farias da Silva
 * Data: 11/04/2025
 */

// Compile and Run: gcc 03.c -o 03 && time ./03

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 
 #define MAX 100 // Limite máximo para M e N
 
 /**
  * Verifica se a posição (i, j) com valor 1 está cercada apenas por 0s.
  *
  * @param matrix Matriz de inteiros.
  * @param M Número de linhas.
  * @param N Número de colunas.
  * @param i Linha do elemento atual.
  * @param j Coluna do elemento atual.
  * @return 1 se estiver cercado por 0s, 0 caso contrário.
  */
int isSurroundedByZeros(int matrix[MAX][MAX], int M, int N, int i, int j) {
	for (int di = -1; di <= 1; di++) {
		for (int dj = -1; dj <= 1; dj++) {
			if (di == 0 && dj == 0) continue; // Ignora o próprio elemento

			int ni = i + di;
			int nj = j + dj;

			if (ni >= 0 && ni < M && nj >= 0 && nj < N) {
				if (matrix[ni][nj] == 1) {
					return 0; // Vizinhança com 1, logo não é rodeada por 0s.
				}
			}
		}
	}
	return 1; // Vizinhança rodeada por 0s.
}
 
 /**
  * Função principal.
  * Lê a matriz, gera números aleatórios e exibe os 1s cercados por 0s.
  */
 int main() {
	int M, N;
	int matrix[MAX][MAX];

	srand(time(NULL)); // Semente para números aleatórios

	// Leitura das dimensões da matriz
	printf("Digite o número de linhas (M): ");
	scanf("%d", &M);

	printf("Digite o número de colunas (N): ");
	scanf("%d", &N);

	if (M <= 0 || N <= 0 || M > MAX || N > MAX) {
		printf("Tamanho inválido.\n");
		return 1;
	}

	// Geração da matriz com 0s e 1s
	printf("\nMatriz gerada:\n");
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			matrix[i][j] = rand() % 2;
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	// Verificação de valores 1 cercados por 0s
	printf("\nPosições com 1 cercado por 0s:\n");
	int found = 0;
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			if (matrix[i][j] == 1 && isSurroundedByZeros(matrix, M, N, i, j)) {
				printf("1 na posição [%d][%d]\n", i, j);
				found = 1;
			}
		}
	}

	if (!found) {
		printf("Nenhum valor 1 está cercado apenas por 0s.\n");
	}

	return 0;
 }
 