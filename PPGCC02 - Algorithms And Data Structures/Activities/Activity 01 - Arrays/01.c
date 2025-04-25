/*
 * Descrição: A mediana de um vetor de números é o elemento m do vetor, tal que metade dos números
	restantes no vetor é maior ou igual a m e metade é menor ou igual a m, se o número de elementos
	no vetor for ímpar. Se o número de elementos for par, a mediana será a média dos dois elementos,
	m1 e m2, tal que metade dos elementos restantes é maior ou igual a ml e m2, e metade dos
	elementos é menor ou igual a m1 e m2. Escreva um programa em C que aceite um vetor de números
	e retorne a mediana dos números no vetor.
 *
 * Entradas:
 *   - Um número inteiro representando o tamanho do vetor (deve ser >= 2).
 *   - Os elementos do vetor (números inteiros).
 *
 * Saídas:
 *   - Valor da mediana.
 *
 * Passos:
 *   1. Ler o tamanho do vetor.
 *   2. Ler os elementos do vetor.
 *   3. Ordenar o vetor com Quick Sort.
 *   4. Calcular a mediana.
 *   5. Exibir o vetor ordenado e a mediana.
 *
 * Autor: Breno Farias da Silva
 * Data: 11/04/2025
 */

// Compile and Run: gcc 01.c -o 01 && time ./01

#include <stdio.h> // Funções: printf, scanf

/**
 * Ordena um vetor de inteiros usando o algoritmo Quick Sort.
 *
 * @param vector Vetor de inteiros a ser ordenado.
 * @param low Índice inicial do vetor.
 * @param high Índice final do vetor.
 */
void quickSort(int *vector, int low, int high) {
	if (low < high) {
		int pivot = vector[high];
		int i = low - 1;

		for (int j = low; j < high; j++) {
			if (vector[j] <= pivot) {
				i++;
				int temp = vector[i];
				vector[i] = vector[j];
				vector[j] = temp;
			}
		}

		int temp = vector[i + 1];
		vector[i + 1] = vector[high];
		vector[high] = temp;

		int pivotIndex = i + 1;
		quickSort(vector, low, pivotIndex - 1);
		quickSort(vector, pivotIndex + 1, high);
	}
}

/**
 * Chama o algoritmo de ordenação Quick Sort se o vetor for válido.
 *
 * @param size Tamanho do vetor.
 * @param vector Ponteiro para o vetor a ser ordenado.
 * @return Retorna 0 se executado com sucesso.
 */
int sortVector(int size, int *vector) {
	if (vector != NULL && size > 0) {
		quickSort(vector, 0, size - 1);
	}
	return 0;
}

/**
 * Calcula a mediana de um vetor de inteiros ordenado.
 *
 * @param size Tamanho do vetor.
 * @param vector Ponteiro para o vetor ordenado.
 * @return Valor da mediana.
 */
int getMedian(const int size, const int *vector) {
	return (size % 2 == 0) 
		? (vector[size/2 - 1] + vector[size/2]) / 2 
		: vector[size/2];
}

/**
 * Função principal do programa.
 *
 * Solicita ao usuário o tamanho e os elementos de um vetor, ordena o vetor,
 * calcula a mediana e exibe os resultados.
 *
 * @return Código de status da execução (0: sucesso).
 */
int main() {
	int size = 0;

	// Solicita um tamanho de vetor válido
	while (size < 2) {
		printf("Digite o tamanho do vetor (>= 2): ");
		scanf("%d", &size);

		if (size < 2) {
			printf("Tamanho inválido! Tente novamente.\n");
		}
	}

	int vector[size];

	// Leitura dos elementos do vetor
	for (int i = 0; i < size; i++) {
		printf("Digite o elemento %d: ", i + 1);
		scanf("%d", &vector[i]);
	}

	// Exibe vetor original
	printf("\nVetor inserido: ");
	for (int i = 0; i < size; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");

	// Ordena o vetor
	sortVector(size, vector);


	// Calcula e exibe a mediana
	const int median = getMedian(size, vector);
	printf("Mediana do vetor: %d\n", median);

	return 0;
}
