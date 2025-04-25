/*
 * Descrição: Escreve um procedimento que calcula um array de inteiros com o produto dos elementos de outros dois arrays de inteiros.
 * O procedimento deve seguir a assinatura abaixo:
 * int* produto(int *v1, int *v2, int N);
 * Onde *v1 e *v2 são ponteiros para arrays de inteiros, e N representa o número de elementos dos arrays.
 * O array resultante deve ser alocado dinamicamente, e cada um dos seus elementos deve conter o produto dos elementos dos outros dois arrays na respectiva posição.
 * Por exemplo, v3[i] = v2[i] * v1[i].
 * Observe os casos de teste para identificar as validações necessárias.
 *
 * Autor: Breno Farias da Silva
 * Data: 25/04/2025
 */

// Compile and Run: gcc 01.c -o 01 && time ./01

#include <stdio.h>  // Funções de entrada e saída: printf
#include <stdlib.h> // Funções de alocação dinâmica: malloc, free

/**
 * Calcula o produto elemento a elemento de dois arrays de inteiros.
 *
 * @param v1 Ponteiro para o primeiro array de inteiros.
 * @param v2 Ponteiro para o segundo array de inteiros.
 * @param N Número de elementos dos arrays.
 * @return Ponteiro para o novo array contendo os produtos, ou NULL em caso de erro.
 */
int* produto(int *v1, int *v2, int N) {
	// Verificação de entrada inválida: ponteiros nulos ou tamanho inválido
	if (v1 == NULL || v2 == NULL || N <= 0) {
		return NULL;
	}

	// Alocação dinâmica para o array de resultado
	int *resultado = (int *)malloc(N * sizeof(int));
	if (resultado == NULL) {
	// Retorna NULL em caso de falha na alocação de memória
		return NULL;
	}

	// Cálculo do produto elemento a elemento
	for (int i = 0; i < N; i++) {
		resultado[i] = v1[i] * v2[i];
	}

	return resultado;
}

/**
 * Função principal do programa.
 *
 * Executa casos de teste para verificar o funcionamento da função produto.
 *
 * @return Código de status da execução (0: sucesso).
 */
int main() {
	// Caso de teste 1
	int vetor1[5] = {0, 0, 1, 2, 2};
	int vetor2[5] = {0, 0, 1, 2, 2};
	int *resultado1 = produto(vetor1, vetor2, 5);

	printf("Resultado 1: ");
	for (int i = 0; i < 5; i++) {
		printf("%d ", resultado1[i]);
	}
	printf("\n");
	free(resultado1); // Liberação de memória

	// Caso de teste 2
	int vetor3[8] = {7, 6, 5, 4, 3, 2, 1, 0};
	int vetor4[8] = {7, 6, 5, 4, 3, 2, 1, 0};
	int *resultado2 = produto(vetor3, vetor4, 8);

	printf("Resultado 2: ");
	for (int i = 0; i < 8; i++) {
		printf("%d ", resultado2[i]);
	}
	printf("\n");
	free(resultado2); // Liberação de memória

	// Caso de teste com ponteiros nulos
	int *resultado3 = produto(NULL, NULL, 8);
	printf("Resultado 3 (NULL esperado): %d\n", resultado3 == NULL);

	// Caso de teste com tamanho inválido
	int vetor5[8] = {7, 6, 5, 4, 3, 2, 1, 0};
	int vetor6[8] = {7, 6, 5, 4, 3, 2, 1, 0};
	int *resultado4 = produto(vetor5, vetor6, -1);
	printf("Resultado 4 (NULL esperado): %d\n", resultado4 == NULL);

	return 0;
}
