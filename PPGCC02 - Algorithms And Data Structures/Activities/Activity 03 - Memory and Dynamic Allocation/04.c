/*
 * Descrição: Este programa demonstra duas abordagens para criar vetores dinamicamente:
 * uma utilizando retorno direto (vetor_novoA) e outra utilizando passagem de ponteiro (vetor_novoB).
 * Em ambas, o vetor é alocado com um tamanho e preenchido com um valor definido.
 *
 * Autor: Breno Farias da Silva
 * Data: 25/04/2025
 */

// Compile and Run: gcc 04.c -o 04 && time ./04

#include <stdio.h>  // Funções: printf
#include <stdlib.h> // Funções: malloc, free

/**
 * Cria dinamicamente um vetor de inteiros e o preenche com um valor.
 *
 * @param tam Tamanho do vetor.
 * @param val Valor para preencher cada posição.
 * @return Ponteiro para o vetor criado.
 */
int* vetor_novoA(int tam, int val) {
	if (tam <= 0) return NULL;

	int *vetor = (int*) malloc(tam * sizeof(int));
	if (vetor == NULL) return NULL;

	for (int i = 0; i < tam; i++) {
		vetor[i] = val;
	}

	return vetor;
}

/**
 * Cria dinamicamente um vetor de inteiros e o preenche com um valor.
 *
 * @param tam Tamanho do vetor.
 * @param val Valor para preencher cada posição.
 * @param endereco Ponteiro para onde será armazenado o endereço do vetor criado.
 */
void vetor_novoB(int tam, int val, int **endereco) {
	if (tam <= 0 || endereco == NULL) {
		if (endereco != NULL) *endereco = NULL;
		return;
	}

	*endereco = (int*) malloc(tam * sizeof(int));
	if (*endereco == NULL) return;

	for (int i = 0; i < tam; i++) {
		(*endereco)[i] = val;
	}
}

/**
 * Função principal do programa.
 *
 * Cria dois vetores usando abordagens diferentes e exibe seus conteúdos.
 *
 * @return Código de status da execução (0: sucesso).
 */
int main() {
	int *v1, *v2;

	v1 = vetor_novoA(10, -1); // Vetor com 10 posições preenchidas com -1
	vetor_novoB(5, 0, &v2); // Vetor com 5 posições preenchidas com 0

	printf("v1: ");
	for (int i = 0; i < 10; i++) {
		printf("%d ", v1[i]);
	}

	printf("\nv2: ");
	for(int i = 0; i < 5; i++) {
		printf("%d ", v2[i]);
	}

	free(v1); // Libera a memória alocada para v1
	free(v2); // Libera a memória alocada para v2

	return 0;
}
