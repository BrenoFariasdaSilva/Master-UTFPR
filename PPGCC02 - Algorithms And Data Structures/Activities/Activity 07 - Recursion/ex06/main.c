/*
 * Description: Implemente uma busca binária em um arranjo ordenado v do item. Os parâmetros inicio e fim referem-se a parte do arranjo a ser analisada. int busca(int *v, int inicio, int fim, int item);
 * Author: Breno Farias da Silva.
 * Date: 27/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

int busca(int *v, int inicio, int fim, int item) {
	if (inicio > fim) {
		return -1; // Item não encontrado
	}

	int meio = (inicio + fim) / 2;

	if (v[meio] == item) {
		return meio; // Item encontrado
	} else if (v[meio] > item) {
		return busca(v, inicio, meio - 1, item); // Busca na metade esquerda
	} else {
		return busca(v, meio + 1, fim, item); // Busca na metade direita
	}
}
