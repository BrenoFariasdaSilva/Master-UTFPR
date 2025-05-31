/*
 * Description: Altere as implementações lista_dupla.c e lista_sentinela.c para incluir uma função
 para cada implementação com a seguinte assinatura: bool inverte(Lista *l);.
 Na sua resposta deixe claro sobre qual lista sua implementação se refere.
 * Author: Breno Farias da Silva.
 * Date: 27/03/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <stdbool.h> // bool, true, false

// Lista Dupla
bool inverte(Lista* l) {
	if (!l || l->qtde <= 1) return false;

	No* atual = l->inicio;
	No* temp = NULL;

	while (atual != NULL) {
		// Troca os ponteiros anterior e próximo do nó atual
		temp = atual->ant;
		atual->ant = atual->prox;
		atual->prox = temp;

		// Avança para o próximo nó (que agora está no ponteiro 'ant')
		atual = atual->ant;
	}

	// Troca o início com o fim da lista
	temp = l->inicio;
	l->inicio = l->fim;
	l->fim = temp;

	return true;
}

// Lista Sentinela
bool inverte(Lista* l) {
	if (!l || l->qtde <= 1) return false;

	No* atual = l->sentinela;
	No* temp = NULL;

	do {
		// Troca os ponteiros anterior e próximo do nó atual
		temp = atual->ant;
		atual->ant = atual->prox;
		atual->prox = temp;

		// Avança para o próximo nó (que agora está no ponteiro 'ant')
		atual = atual->ant;
	} while (atual != l->sentinela);

	return true;
}