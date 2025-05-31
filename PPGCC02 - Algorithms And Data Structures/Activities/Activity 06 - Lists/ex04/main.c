/*
 * Description: Altere as implementações lista_dupla.c e lista_sentinela.c para incluir uma função para cada implementação com a seguinte assinatura: bool eh_ordenada(Lista *l);. Na sua resposta deixe claro sobre qual lista sua implementação se refere. A função recebe uma lista e devolve verdadeira se os seus dados estão ordenados (crescente ou decrescente). Caso contrário, devolve falso. Não é admitido usar um vetor auxiliar para implementação.
 * Author: Breno Farias da Silva.
 * Date: 27/03/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

// Lista Dupla
bool eh_ordenada(Lista *l) {
	if (l == NULL || l->inicio == NULL || l->inicio->prox == NULL)
		return true; // Lista vazia ou com um único elemento é ordenada

	No *atual = l->inicio;
	bool crescente = true, decrescente = true;

	while (atual->prox != NULL) {
		if (atual->dado > atual->prox->dado)
			crescente = false;
		if (atual->dado < atual->prox->dado)
			decrescente = false;
		atual = atual->prox;
	}

	return crescente || decrescente;
}

// Lista Sentinela
bool eh_ordenada(Lista *l) {
	if (l == NULL || l->sentinela->prox == l->sentinela || l->sentinela->prox->prox == l->sentinela)
		return true; // Lista vazia ou com um único elemento é ordenada

	No *atual = l->sentinela->prox;
	bool crescente = true, decrescente = true;

	while (atual->prox != l->sentinela) {
		if (atual->dado > atual->prox->dado)
			crescente = false;
		if (atual->dado < atual->prox->dado)
			decrescente = false;
		atual = atual->prox;
	}

	return crescente || decrescente;
}