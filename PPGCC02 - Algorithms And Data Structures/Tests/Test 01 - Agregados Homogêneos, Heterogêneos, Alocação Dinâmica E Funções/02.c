/*
* Descrição: Faça uma função que receba duas matrizes e retorne a matriz resultado da multiplicação de ambas.
             A matriz resultado deverá ser alocada dinamicamente.
             Elabore três casos de teste com diferentes tamanhos de matrizes.
             As matrizes de teste podem ser alocadas estaticamente.
             Na multiplicação de matrizes, o número de colunas da primeira matriz deve ser igual ao número de linhas da segunda matriz.
             Se não for possível multiplicar as matrizes, a função deve retornar NULL.
             Caso a multiplicação seja possível, a função deve retornar o endereço da matriz resultado.
* Autor: Breno Farias da Silva
* Data: 06/05/2025
*/

#include <stdio.h> // Biblioteca necessária para usar printf
#include <stdlib.h> // Biblioteca necessária para usar malloc e free

/* Protótipos das funções */
int** produtoMatrizes(int** matrix1, int** matrix2, int r1, int c1, int r2, int c2);
int printMatrix(int** matrix, int r, int c);
void test1();
void test2();
void test3();

/*
 * Função que realiza a multiplicação de duas matrizes.
 * matrix1: ponteiro para a primeira matriz.
 * matrix2: ponteiro para a segunda matriz.
 * r1: número de linhas da matriz 1.
 * c1: número de colunas da matriz 1.
 * r2: número de linhas da matriz 2.
 * c2: número de colunas da matriz 2.
 * retorno: ponteiro para a matriz resultado ou NULL se não for possível realizar a multiplicação.
 */
int** produtoMatrizes(int** matrix1, int** matrix2, int r1, int c1, int r2, int c2) {
	if (matrix1 == NULL || matrix2 == NULL || r1 <= 0 || c1 <= 0 || r2 <= 0 || c2 <= 0) {
		return NULL;
	}

	if (c1 != r2) {
		printf("Erro: número de colunas da matriz A (%d) é diferente do número de linhas da matriz B (%d).\n", c1, r2);
		return NULL;
	}

	// Aloca dinamicamente a matriz resultado (r1 x c2)
	int** resultado = (int**) malloc(r1 * sizeof(int*));
	if (resultado == NULL) return NULL;

	for (int i = 0; i < r1; i++) {
		resultado[i] = (int*) calloc(c2, sizeof(int));
		if (resultado[i] == NULL) return NULL;
	}

	// Realiza a multiplicação
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c2; j++) {
			for (int k = 0; k < c1; k++) {
				resultado[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}

	return resultado;
}

/*
* Função para imprimir uma matriz na tela.
* matrix: ponteiro para a matriz.
* r: número de linhas.
* c: número de colunas.
* retorno: 0 em caso de sucesso, -1 caso erro.
*/
int printMatrix(int** matrix, int r, int c) {
	if (matrix == NULL || r <= 0 || c <= 0) return -1;

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	return 0;
}

/*
* Função de teste 1: Multiplicação de matriz 3x2 por matriz 2x3.
*/
void test1() {
	printf("Teste 1: Multiplicação 3x2 * 2x3\n");

	int m1[3][2] = {{1, 2}, {3, 4}, {5, 6}};
	int m2[2][3] = {{7, 8, 9}, {10, 11, 12}};

	int* ptr1[3] = {m1[0], m1[1], m1[2]};
	int* ptr2[2] = {m2[0], m2[1]};

	int** resultado = produtoMatrizes(ptr1, ptr2, 3, 2, 2, 3);

	if (resultado != NULL) {
		printf("Resultado:\n");
		printMatrix(resultado, 3, 3);
		for (int i = 0; i < 3; i++) free(resultado[i]);
		free(resultado);
	} else {
		printf("Multiplicação não realizada.\n");
	}
}

/*
* Função de teste 2: Multiplicação 2x2 * 2x2.
*/
void test2() {
	printf("Teste 2: Multiplicação 2x2 * 2x2\n");

	int m1[2][2] = {{2, 0}, {1, 3}};
	int m2[2][2] = {{1, 4}, {2, 5}};

	int* ptr1[2] = {m1[0], m1[1]};
	int* ptr2[2] = {m2[0], m2[1]};

	int** resultado = produtoMatrizes(ptr1, ptr2, 2, 2, 2, 2);

	if (resultado != NULL) {
		printf("Resultado:\n");
		printMatrix(resultado, 2, 2);
		for (int i = 0; i < 2; i++) free(resultado[i]);
		free(resultado);
	} else {
		printf("Multiplicação não realizada.\n");
	}
}

/*
* Função de teste 3: Tentativa de multiplicação inválida (dimensões incompatíveis).
*/
void test3() {
	printf("Teste 3: Multiplicação inválida (2x3 * 2x2)\n");

	int m1[2][3] = {{1, 2, 3}, {4, 5, 6}};
	int m2[2][2] = {{7, 8}, {9, 10}};

	int* ptr1[2] = {m1[0], m1[1]};
	int* ptr2[2] = {m2[0], m2[1]};

	int** resultado = produtoMatrizes(ptr1, ptr2, 2, 3, 2, 2);

	if (resultado != NULL) {
		printf("Resultado:\n");
		printMatrix(resultado, 2, 2);
		for (int i = 0; i < 2; i++) free(resultado[i]);
		free(resultado);
	} else {
		printf("Multiplicação não realizada: dimensões incompatíveis.\n");
	}
}

/*
* Função principal do programa.
* argc: quantidade de argumentos passados na chamada do programa.
* argv: vetor com os argumentos passados na chamada do programa.
* retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
*/
int main(int argc, char* argv[]) {
	test1();
	test2();
	test3();
	return 0;
}
