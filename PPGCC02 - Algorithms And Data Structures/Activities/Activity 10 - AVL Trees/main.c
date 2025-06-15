#include <stdio.h>
#include "arvore_avl.h"

void teste_rotacao_esquerda(){

	No *arvore = NULL;
	printf("Inserir 10\n");
	arvore = avl_inserir(arvore, 10);
	printf("Inserir 5\n");
	arvore = avl_inserir(arvore, 5);
	printf("Inserir 20\n");
	arvore = avl_inserir(arvore, 20);
	printf("Inserir 15\n");
	arvore = avl_inserir(arvore, 15);
	printf("Inserir 25\n");
	arvore = avl_inserir(arvore, 25);
	printf("Inserir 30\n");
	arvore = avl_inserir(arvore, 30);

	printf("Altura: %d\n", ab_altura(arvore));
	printf("Total de Vertices: %d\n", ab_total_vertices(arvore));

	printf("\n--EmOrdem--\n");	
	ab_em_ordem(arvore);

	ab_destruir(&arvore);
}

void teste_rotacao_direita(){

	No *arvore = NULL;
	printf("Inserir 25\n");
	arvore = avl_inserir(arvore, 25);
	printf("Inserir 15\n");
	arvore = avl_inserir(arvore, 15);
	printf("Inserir 30\n");
	arvore = avl_inserir(arvore, 30);
	printf("Inserir 10\n");
	arvore = avl_inserir(arvore, 10);
	printf("Inserir 20\n");
	arvore = avl_inserir(arvore, 20);
	printf("Inserir 5\n");
	arvore = avl_inserir(arvore, 5);
	
	printf("Altura: %d\n", ab_altura(arvore));
	printf("Total de Vertices: %d\n", ab_total_vertices(arvore));

	printf("\n--EmOrdem--\n");	
	ab_em_ordem(arvore);
	ab_destruir(&arvore);
}

void teste_rotacao_dupla_direita(){
	No *arvore = NULL;
	printf("Inserir 25\n");
	arvore = avl_inserir(arvore, 25);
	printf("Inserir 30\n");
	arvore = avl_inserir(arvore, 30);
	printf("Inserir 10\n");
	arvore = avl_inserir(arvore, 10);
	printf("Inserir 5\n");
	arvore = avl_inserir(arvore, 5);
	printf("Inserir 20\n");
	arvore = avl_inserir(arvore, 20);
	printf("Inserir 15\n");
	arvore = avl_inserir(arvore, 15);
	
	printf("Altura: %d\n", ab_altura(arvore));
	printf("Total de Vertices: %d\n", ab_total_vertices(arvore));

	printf("\n--EmOrdem--\n");	
	ab_em_ordem(arvore);
	ab_destruir(&arvore);
}

void teste_rotacao_dupla_esquerda(){
	No *arvore = NULL;
	printf("Inserir 10\n");
	arvore = avl_inserir(arvore, 10);
	printf("Inserir 5\n");
	arvore = avl_inserir(arvore, 5);
	printf("Inserir 25\n");
	arvore = avl_inserir(arvore, 25);
	printf("Inserir 30\n");
	arvore = avl_inserir(arvore, 30);
	printf("Inserir 15\n");
	arvore = avl_inserir(arvore, 15);
	printf("Inserir 20\n");
	arvore = avl_inserir(arvore, 20);
	
	printf("Altura: %d\n", ab_altura(arvore));
	printf("Total de Vertices: %d\n", ab_total_vertices(arvore));

	printf("\n--EmOrdem--\n");	
	ab_em_ordem(arvore);
	ab_destruir(&arvore);
}

void exercicio(){
	No *arvore = NULL;
	printf("Inserir 10\n");
	arvore = avl_inserir(arvore, 10);
	printf("Inserir 20\n");
	arvore = avl_inserir(arvore, 20);
	printf("Inserir 30\n");
	arvore = avl_inserir(arvore, 30);
	printf("Inserir 5\n");
	arvore = avl_inserir(arvore, 5);
	printf("Inserir 3\n");
	arvore = avl_inserir(arvore, 3);
	printf("Inserir 50\n");
	arvore = avl_inserir(arvore, 50);
	printf("Inserir 40\n");
	arvore = avl_inserir(arvore, 40);
	printf("Inserir 70\n");
	arvore = avl_inserir(arvore, 70);
	printf("Inserir 60\n");
	arvore = avl_inserir(arvore, 60);
	printf("Inserir 90\n");
	arvore = avl_inserir(arvore, 90);

	printf("Altura: %d\n", ab_altura(arvore));
	printf("Total de Vertices: %d\n", ab_total_vertices(arvore));

	printf("\n--EmOrdem--\n");	
	ab_em_ordem(arvore);
	ab_destruir(&arvore);

}
int main(){
	
	teste_rotacao_esquerda();
	teste_rotacao_direita();
	teste_rotacao_dupla_direita();
	teste_rotacao_dupla_esquerda();
	exercicio();
	return 0;
}