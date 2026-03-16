#include <stdio.h>
#include "arvore_binaria.h"

void imprimir_lista(TipoElemento* lista, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", lista[i]);
	}
	printf("\n");
}

void teste1(){

	No *arvore = NULL;
	ab_inserir(&arvore, 20);
	ab_inserir(&arvore, 10);
	ab_inserir(&arvore, 30);
	ab_inserir(&arvore, 5);
	ab_inserir(&arvore, 15);
	ab_inserir(&arvore, 11);
	ab_inserir(&arvore, 16);

	printf("Altura: %d\n", ab_altura(arvore));
	printf("Total de Vertices: %d\n", ab_total_vertices(arvore));
	printf("Total de folhas: %d\n", ab_contar_folhas(arvore));
	printf("Total de nós internos: %d\n", ab_contar_nos_internos(arvore));
	printf("Está balanceada? %s\n", ab_esta_balanceada(arvore) ? "Sim" : "Não");

	printf("\n--PreOrdem----\n");    
	ab_pre_ordem(arvore);
	printf("\n--EmOrdem--\n");    
	ab_em_ordem(arvore);
	printf("\n--PosOrdem-\n");    
	ab_pos_ordem(arvore);

	// Testar sucessor e predecessor
	TipoElemento valor = 15;
	No* no_sucessor = ab_sucessor(arvore, valor);
	if (no_sucessor != NULL) 
		printf("\nSucessor de %d: %d\n", valor, no_sucessor->dado);
	else
		printf("\nSucessor de %d: nao encontrado\n", valor);

	No* no_predecessor = ab_predecessor(arvore, valor);
	if (no_predecessor != NULL)
		printf("Predecessor de %d: %d\n", valor, no_predecessor->dado);
	else
		printf("Predecessor de %d: nao encontrado\n", valor);

	// Converter para lista ordenada e imprimir
	int n = ab_total_vertices(arvore);
	TipoElemento* lista = ab_para_lista(arvore, &n);

	for (int i = 0; i < n; i++) {
		printf("%d ", lista[i]);
	}
	printf("\n");

	free(lista); // não esqueça de liberar a memória alocada

	ab_destruir(&arvore);
}

void teste2(){

	No *arvore1 = NULL;
	ab_inserir(&arvore1, 20);
	ab_inserir(&arvore1, 10);
	ab_inserir(&arvore1, 30);
	ab_inserir(&arvore1, 40);
	ab_inserir(&arvore1, 25);
	ab_inserir(&arvore1, 15);
	ab_inserir(&arvore1, 5);

	No *arvore2 = NULL;
	ab_inserir(&arvore2, 20);
	ab_inserir(&arvore2, 10);
	ab_inserir(&arvore2, 30);
	ab_inserir(&arvore2, 40);
	ab_inserir(&arvore2, 25);
	ab_inserir(&arvore2, 15);
	ab_inserir(&arvore2, 5);

	printf("Arvores iguais? %s\n", ab_sao_iguais(arvore1, arvore2) ? "Sim" : "Não");

	ab_remover(&arvore2, 5);
	printf("Após remover 5 de arvore2, árvores iguais? %s\n", ab_sao_iguais(arvore1, arvore2) ? "Sim" : "Não");

	ab_destruir(&arvore1);
	ab_destruir(&arvore2);
}

int main(){
	printf("=== Teste 1 ===\n");
	teste1();

	printf("\n=== Teste 2 ===\n");
	teste2();

	return 0;
}