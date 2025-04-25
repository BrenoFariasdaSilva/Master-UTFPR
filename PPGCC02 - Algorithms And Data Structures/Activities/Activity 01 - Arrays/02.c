/*
 * Descrição: A moda de um vetor de números é o número m no vetor que é repetido com maior frequência.
 * Se mais de um número for repetido com frequência máxima igual, não existirá uma moda.
 * Escreva um programa em C que aceite um vetor de números e retorne a moda dos números no vetor.
 *
 * Entradas:
 *   - Um número inteiro representando o tamanho do vetor (deve ser >= 2).
 *   - Os elementos do vetor (números inteiros).
 *
 * Saídas:
 *   - Valor da moda ou uma mensagem indicando que não existe moda.
 *
 * Passos:
 *   1. Ler o tamanho do vetor.
 *   2. Ler os elementos do vetor.
 *   3. Ordenar o vetor com Quick Sort.
 *   4. Calcular a moda.
 *   5. Exibir o vetor ordenado e a moda.
 *
 * Autor: Breno Farias da Silva
 * Data: 11/04/2025
 */

// Compile and Run: gcc 02.c -o 02 && time ./02

#include <stdio.h> // Funções: printf, scanf
#include <limits.h> // Constante: INT_MIN

/**
 * Ordena um vetor de inteiros usando o algoritmo Quick Sort.
 *
 * @param array Vetor de inteiros a ser ordenado.
 * @param low Índice inicial do vetor.
 * @param high Índice final do vetor.
 */
void quick_sort(int *array, int low, int high) {
	if (low < high) {
		int pivot = array[high];
		int i = low - 1;

		for (int j = low; j < high; j++) {
			if (array[j] <= pivot) {
				i++;
				int temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}

		int temp = array[i + 1];
		array[i + 1] = array[high];
		array[high] = temp;

		int pivot_index = i + 1;
		quick_sort(array, low, pivot_index - 1);
		quick_sort(array, pivot_index + 1, high);
	}
}

/**
 * Conta a frequência de cada valor no vetor ordenado.
 *
 * @param size Tamanho do vetor.
 * @param array Vetor ordenado de inteiros.
 * @param frequency_array Vetor onde serão armazenadas as frequências.
 * @return Quantidade de grupos distintos.
 */
int count_frequency(const int size, const int *array, int *frequency_array) {
	if (array == NULL || frequency_array == NULL || size <= 0) {
		return -1;
	}

	int i = 0, k = 0;

	while (i < size) {
		int current = array[i];
		int freq = 1;

		while (i + 1 < size && array[i + 1] == current) {
			freq++;
			i++;
		}

		frequency_array[k++] = freq;
		i++;
	}

	return k;
}

/**
 * Retorna a moda de um vetor ordenado com base nas frequências calculadas.
 *
 * @param size Tamanho do vetor.
 * @param array Vetor ordenado.
 * @param frequency_array Frequência dos elementos.
 * @return Moda se existir; INT_MIN se não houver moda.
 */
int get_mode(int size, const int *array, const int *frequency_array) {
	int max_freq = 0;
	int mode = INT_MIN;
	int tie = 0;

	int i = 0, j = 0;

	while (i < size) {
		int current = array[i];
		int freq = frequency_array[j];
		if (freq > max_freq) {
			max_freq = freq;
			mode = current;
			tie = 0;
		} else if (freq == max_freq && current != mode) {
			tie = 1;
		}
		i += freq;
		j++;
	}

	return (tie || max_freq == 1) ? INT_MIN : mode;
}

/**
 * Função principal.
 * 
 * Lê os dados, ordena o vetor, calcula e imprime a moda.
 */
int main() {
	int size = 0;

	while (size < 2) {
		printf("Digite o tamanho do vetor (>= 2): ");
		scanf("%d", &size);

		if (size < 2) {
			printf("Tamanho inválido! Tente novamente.\n");
		}
	}

	int array[size];

	for (int i = 0; i < size; i++) {
		printf("Digite o elemento %d: ", i + 1);
		scanf("%d", &array[i]);
	}

	quick_sort(array, 0, size - 1);

	printf("\nVetor ordenado: ");
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");

	int frequency_array[size];
	int group_count = count_frequency(size, array, frequency_array);

	if (group_count == -1) {
		printf("Erro ao calcular frequência.\n");
		return -1;
	}

	int mode = get_mode(size, array, frequency_array);

	if (mode != INT_MIN) {
		printf("Moda: %d\n", mode);
	} else {
		printf("Não existe moda nesse vetor, pois há valores com a mesma frequência máxima!\n");
	}

	return 0;
}
