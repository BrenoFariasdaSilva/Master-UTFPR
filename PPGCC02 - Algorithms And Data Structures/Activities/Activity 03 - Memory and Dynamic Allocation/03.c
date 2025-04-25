/*
* Descrição: Esta função calcula a união entre dois arrays de inteiros. Ambos os arrays são ordenados
* com Quick Sort e percorridos simultaneamente com dois ponteiros. O array resultante, contendo a união
* sem duplicatas, é alocado dinamicamente e seu tamanho é informado por meio de um ponteiro.
*
* Autor: Breno Farias da Silva
* Data: 25/04/2025
*/

// Compile and Run: gcc 03.c -o 03 && time ./03

#include <stdio.h>
#include <stdlib.h>

/**
 * Função auxiliar que troca o valor de dois inteiros.
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
* Função que implementa o algoritmo de ordenação Quick Sort.
*
* Ordena o array de inteiros no intervalo entre os índices 'inicio' e 'fim'.
*
* @param vetor Ponteiro para o array a ser ordenado.
* @param inicio Índice inicial do intervalo de ordenação.
* @param fim Índice final do intervalo de ordenação.
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
* Função que calcula a união entre dois arrays inteiros ordenados.
*
* A função ordena ambos os arrays de entrada, remove duplicatas e retorna um novo array
* contendo todos os elementos únicos presentes em pelo menos um dos arrays.
*
* @param v1 Primeiro array.
* @param v2 Segundo array.
* @param n1 Tamanho do primeiro array.
* @param n2 Tamanho do segundo array.
* @param qtde Ponteiro para armazenar a quantidade de elementos da união.
* @return Ponteiro para array dinamicamente alocado com a união (sem duplicatas).
*/
int* uniao(int *v1, int *v2, int n1, int n2, int* qtde) {
	// Validação das entradas
	if (v1 == NULL || v2 == NULL || qtde == NULL || n1 < 0 || n2 < 0) {
		if (qtde != NULL) *qtde = 0;
		return NULL;
	}

	// Ordena os dois arrays
	quickSort(v1, 0, n1 - 1);
	quickSort(v2, 0, n2 - 1);

	// Aloca o array resultado com o tamanho máximo possível (n1 + n2)
	int *resultado = (int*)malloc((n1 + n2) * sizeof(int));
	if (resultado == NULL) {
		*qtde = 0;
		return NULL;
	}

	int i = 0, j = 0, k = 0;

	// Percorre os dois arrays simultaneamente com dois ponteiros
	while (i < n1 && j < n2) {
		if (v1[i] < v2[j]) {
			if (k == 0 || resultado[k - 1] != v1[i])
				resultado[k++] = v1[i];
			i++;
		} else if (v1[i] > v2[j]) {
			if (k == 0 || resultado[k - 1] != v2[j])
				resultado[k++] = v2[j];
			j++;
		} else {
			// Elemento comum aos dois arrays
			if (k == 0 || resultado[k - 1] != v1[i])
				resultado[k++] = v1[i];
			i++;
			j++;
		}
	}

	// Copia os elementos restantes de v1
	while (i < n1) {
		if (k == 0 || resultado[k - 1] != v1[i])
			resultado[k++] = v1[i];
		i++;
	}

	// Copia os elementos restantes de v2
	while (j < n2) {
		if (k == 0 || resultado[k - 1] != v2[j])
			resultado[k++] = v2[j];
		j++;
	}

	*qtde = k;

	// Redimensiona o array para o tamanho final da união
	resultado = realloc(resultado, k * sizeof(int));

	return resultado;
}

/**
* Função principal para testes.
*
* Exibe a união de dois arrays de inteiros fornecidos.
*/
int main() {
	int v1[] = {5, 1, 2, 3, 1, 2};
	int v2[] = {4, 5, 6, 2, 3};
	int qtde = 0;

	int *v3 = uniao(v1, v2, 6, 5, &qtde);

	printf("União: ");
	for (int i = 0; i < qtde; i++) {
		 printf("%d ", v3[i]);
	}
	printf("\n");

	free(v3); // Liberação da memória alocada

	return 0;
}