/*
 * Description: Altere as implementações lista_dupla.c e lista_sentinela.c para incluir uma função para cada implementação com a seguinte assinatura: bool troca(Lista *l, int x, int y);. Na sua resposta deixe claro sobre qual lista sua implementação se refere. A função troca o elemento da posição x pelo elemento da posição y na lista l.
 * Author: Breno Farias da Silva.
 * Date: 27/03/2025.
*/

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

// Lista Dupla
bool troca(Lista *l, int x, int y) {
	if (x == y || l == NULL || x < 0 || y < 0) return false;

	No *px = l->inicio;
	No *py = l->inicio;
	int ix = 0, iy = 0;

	while (px != NULL && ix < x) {
		px = px->prox;
		ix++;
	}

	while (py != NULL && iy < y) {
		py = py->prox;
		iy++;
	}

	if (px == NULL || py == NULL) return false;

	// Trocar os dados dos nós
	int tmp = px->dado;
	px->dado = py->dado;
	py->dado = tmp;

	return true;
}

// Lista Sentinela
bool troca(Lista *l, int x, int y) {
	if (x == y || l == NULL || x < 0 || y < 0) return false;

	No *px = l->sentinela->prox;
	No *py = l->sentinela->prox;
	int ix = 0, iy = 0;

	while (px != l->sentinela && ix < x) {
		px = px->prox;
		ix++;
	}

	while (py != l->sentinela && iy < y) {
		py = py->prox;
		iy++;
	}

	if (px == l->sentinela || py == l->sentinela) return false;

	// Trocar os dados dos nós
	int tmp = px->dado;
	px->dado = py->dado;
	py->dado = tmp;

	return true;
}