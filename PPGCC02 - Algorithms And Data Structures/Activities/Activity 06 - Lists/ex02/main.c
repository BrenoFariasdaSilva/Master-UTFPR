/*
 * Description: Altere as implementações lista_dupla.c e lista_sentinela.c para incluir uma função para cada implementação com a seguinte assinatura: Lista * intercalaListas(Lista *l1, Lista *l2);. Na sua resposta deixe claro sobre qual lista sua implementação se refere. A função recebe duas listas l1 = [x1, ... , xn] e l2 = [y1, ... , ym] como parâmetro e retorna uma lista formada pelos elementos de l1 e l2 intercalados. A lista resultante será da forma [x1, y1, ... , xm, ym, xm+1, ... , xn] se m ≤ n ou [x1, y1, . . . , xn, yn, yn+1, . . . , ym] se m > n. Nenhum nó adicional deve ser criado e as listas l1 e l2 devem ficar vazias ao final.
 * Author: Breno Farias da Silva.
 * Date: 27/03/2025.
*/

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

// Lista Dupla
Lista* intercalaListas(Lista* l1, Lista* l2) {
	if (!lista_ehValida(l1) || !lista_ehValida(l2)) return NULL;

	Lista* nova = lista_criar();
	No *n1 = l1->inicio;
	No *n2 = l2->inicio;

	while (n1 != NULL || n2 != NULL) {
		if (n1 != NULL) {
			No* prox = n1->prox;

			// Remove n1 da lista l1
			if (n1->ant) n1->ant->prox = n1->prox;
			else l1->inicio = n1->prox;
			if (n1->prox) n1->prox->ant = n1->ant;
			else l1->fim = n1->ant;

			// Insere no fim da nova lista
			n1->prox = NULL;
			n1->ant = nova->fim;
			if (nova->fim) nova->fim->prox = n1;
			else nova->inicio = n1;
			nova->fim = n1;
			nova->qtde++;

			l1->qtde--;
			n1 = prox;
		}

		if (n2 != NULL) {
			No* prox = n2->prox;

			// Remove n2 da lista l2
			if (n2->ant) n2->ant->prox = n2->prox;
			else l2->inicio = n2->prox;
			if (n2->prox) n2->prox->ant = n2->ant;
			else l2->fim = n2->ant;

			// Insere no fim da nova lista
			n2->prox = NULL;
			n2->ant = nova->fim;
			if (nova->fim) nova->fim->prox = n2;
			else nova->inicio = n2;
			nova->fim = n2;
			nova->qtde++;

			l2->qtde--;
			n2 = prox;
		}
	}

	l1->inicio = l1->fim = NULL;
	l2->inicio = l2->fim = NULL;
	return nova;
}

// Lista Sentinela
Lista* intercalaListas(Lista* l1, Lista* l2) {
	if (!lista_ehValida(l1) || !lista_ehValida(l2)) return NULL;

	Lista* nova = lista_criar();
	No* n1 = l1->sentinela->prox;
	No* n2 = l2->sentinela->prox;

	while (n1 != l1->sentinela || n2 != l2->sentinela) {
		if (n1 != l1->sentinela) {
			No* prox = n1->prox;
			desconecta_no(n1);
			insere_direita(nova->sentinela->ant, n1);
			nova->qtde++;
			l1->qtde--;
			n1 = prox;
		}

		if (n2 != l2->sentinela) {
			No* prox = n2->prox;
			desconecta_no(n2);
			insere_direita(nova->sentinela->ant, n2);
			nova->qtde++;
			l2->qtde--;
			n2 = prox;
		}
	}

	return nova;
}