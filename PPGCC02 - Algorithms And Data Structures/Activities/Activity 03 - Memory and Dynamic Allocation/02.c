/*
* Descrição: Esta função calcula a interseção entre dois arrays de inteiros ordenando-os previamente
* com Quick Sort e depois comparando os elementos com dois ponteiros. Isso reduz a complexidade do algoritmo.
* A interseção é retornada em um array alocado dinamicamente e o tamanho é atualizado via ponteiro qtde.
*
* Autor: Breno Farias da Silva
* Data: 25/04/2025
*/

// Compile and Run: gcc 02.c -o 02 && time ./02

#include <stdio.h>
#include <stdlib.h>

/**
* Função auxiliar que troca os valores de dois inteiros.
*
* @param a Ponteiro para o primeiro inteiro.
* @param b Ponteiro para o segundo inteiro.
*/
void trocar(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

/**
* Função recursiva que implementa o algoritmo de ordenação Quick Sort.
*
* @param vetor Array de inteiros a ser ordenado.
* @param inicio Índice inicial da parte do array a ser ordenada.
* @param fim Índice final da parte do array a ser ordenada.
*/
void quickSort(int *vetor, int inicio, int fim) {
	if (inicio < fim) {
		int pivo = vetor[fim];
		int i = inicio - 1;

		for (int j = inicio; j < fim; j++) {
			if (vetor[j] < pivo) {
				i++;
				trocar(&vetor[i], &vetor[j]);
			}
		}

		trocar(&vetor[i + 1], &vetor[fim]);
		int posPivo = i + 1;

		quickSort(vetor, inicio, posPivo - 1);
		quickSort(vetor, posPivo + 1, fim);
	}
}

/**
* Função que calcula a interseção entre dois arrays inteiros ordenados.
*
* @param v1 Primeiro array.
* @param v2 Segundo array.
* @param n1 Tamanho do primeiro array.
* @param n2 Tamanho do segundo array.
* @param qtde Ponteiro para armazenar a quantidade de elementos na interseção.
* @return Ponteiro para array dinamicamente alocado com a interseção (sem duplicatas).
*/
int* intersecao(int *v1, int *v2, int n1, int n2, int* qtde) {
	// Validação das entradas
	if (v1 == NULL || v2 == NULL || qtde == NULL || n1 <= 0 || n2 <= 0) {
		if (qtde != NULL) *qtde = 0;
		return NULL;
	}

	// Ordena os dois arrays
	quickSort(v1, 0, n1 - 1);
	quickSort(v2, 0, n2 - 1);

	// Array temporário com tamanho máximo possível
	int *resultado = (int*)malloc((n1 < n2 ? n1 : n2) * sizeof(int));
	if (resultado == NULL) {
		*qtde = 0;
		return NULL;
	}

	int i = 0, j = 0, k = 0;

	// Percorre ambos os arrays com dois ponteiros
	while (i < n1 && j < n2) {
		if (v1[i] < v2[j]) {
			i++;
		} else if (v1[i] > v2[j]) {
			j++;
		} else {
			// Evita duplicatas consecutivas
			if (k == 0 || resultado[k - 1] != v1[i]) {
				resultado[k++] = v1[i];
			}
			i++;
			j++;
		}
	}

	// Atualiza o tamanho da interseção
	*qtde = k;

	// Redimensiona o array para o tamanho final
	resultado = realloc(resultado, k * sizeof(int));

	return resultado;
}

/**
* Função principal que realiza o teste da função de interseção.
*
* @return 0 em caso de sucesso.
*/
int main() {
	int v1[] = {4, 1, 2, 5, 6, 3};
	int v2[] = {8, 4, 5, 6, 7};
	int qtde = 0;

	int *v3 = intersecao(v1, v2, 6, 5, &qtde);

	printf("Interseção: ");
	for (int i = 0; i < qtde; i++) {
		printf("%d ", v3[i]);
	}
	printf("\n");

	free(v3); // Liberação de memória

	return 0;
}
