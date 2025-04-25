/*
 * Descrição: Função que dobra o tamanho de um vetor alocado dinamicamente,
 * preserva os valores existentes e preenche as posições adicionais com zero.
 *
 * Autor: Breno Farias da Silva
 * Data: 25/04/2025
 */

// Compile and Run: gcc 05.c -o 05 && time ./05

#include <stdio.h> // Funções: printf
#include <stdlib.h> // Funções: malloc, free, calloc

/**
 * Função que dobra o tamanho de um vetor dinamicamente alocado.
 * A nova memória é preenchida com zeros nas posições adicionais.
 *
 * @param vetor Ponteiro para o vetor a ser dobrado.
 * @param tamanho Tamanho atual do vetor.
 * @return O novo tamanho do vetor.
 */
int vetor_dobraTamanho(int **vetor, int tamanho) {
	if (vetor == NULL || *vetor == NULL || tamanho <= 0) {
		return 0; // Retorna 0 em caso de erro.
	}

	// Alocar novo vetor com o dobro do tamanho
	int novoTamanho = tamanho * 2;
	int *novoVetor = (int*) malloc(novoTamanho * sizeof(int));

	if (novoVetor == NULL) {
		return 0; // Retorna 0 em caso de falha na alocação
	}

	// Copiar os valores do vetor antigo para o novo vetor
	for (int i = 0; i < tamanho; i++) {
		novoVetor[i] = (*vetor)[i];
	}

	// Preencher as novas posições com zero
	for (int i = tamanho; i < novoTamanho; i++) {
		novoVetor[i] = 0;
	}

	// Desalocar o vetor antigo
	free(*vetor);

	// Atualizar a referência do vetor para apontar para o novo vetor
	*vetor = novoVetor;

	// Retornar o novo tamanho
	return novoTamanho;
}

/**
 * Função principal do programa.
 *
 * Demonstra a utilização da função vetor_dobraTamanho.
 *
 * @return Código de status da execução (0: sucesso).
 */
int main() {
	// Aloca vetor dinamicamente com 3 elementos (inicializados com 0)
	int* v = (int*) calloc(3, sizeof(int));
	v[0] = 2;
	v[1] = 4;
	v[2] = 6;

	// Chama a função para dobrar o tamanho do vetor
	int novoTamanho = vetor_dobraTamanho(&v, 3);

	// Exibe o conteúdo do vetor após a modificação
	printf("Novo vetor: ");
	for (int i = 0; i < novoTamanho; i++) {
		printf("%d ", v[i]);
	}
	printf("\n");

	// Libera a memória alocada
	free(v);

	return 0;
}