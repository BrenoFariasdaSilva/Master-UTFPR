#include <stdio.h>
#include "arvore_avl.h"

void imprimir_altura_e_total(No* arvore) {
    printf("Altura: %d\n", ab_altura(arvore));
    printf("Total de Vertices: %d\n", ab_total_vertices(arvore));
}

void teste_rotacao_esquerda() {
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

    imprimir_altura_e_total(arvore);

    printf("\n--EmOrdem--\n");    
    ab_em_ordem(arvore);
    printf("\n");

    ab_destruir(&arvore);
}

void teste_rotacao_direita() {
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

    imprimir_altura_e_total(arvore);

    printf("\n--EmOrdem--\n");    
    ab_em_ordem(arvore);
    printf("\n");

    ab_destruir(&arvore);
}

void teste_rotacao_dupla_direita() {
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

    imprimir_altura_e_total(arvore);

    printf("\n--EmOrdem--\n");    
    ab_em_ordem(arvore);
    printf("\n");

    ab_destruir(&arvore);
}

void teste_rotacao_dupla_esquerda() {
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

    imprimir_altura_e_total(arvore);

    printf("\n--EmOrdem--\n");    
    ab_em_ordem(arvore);
    printf("\n");

    ab_destruir(&arvore);
}

void teste_remocao() {
    No* arvore = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    printf("Inserindo valores: ");
    for (int i = 0; i < 7; i++) {
        printf("%d ", valores[i]);
        arvore = avl_inserir(arvore, valores[i]);
    }
    printf("\n");

    imprimir_altura_e_total(arvore);

    printf("\n--EmOrdem antes da remoção--\n");
    ab_em_ordem(arvore);
    printf("\n");

    int remover[] = {20, 30, 50};
    for (int i = 0; i < 3; i++) {
        printf("Removendo %d\n", remover[i]);
        arvore = avl_remover(arvore, remover[i]);
        printf("--EmOrdem após remoção de %d--\n", remover[i]);
        ab_em_ordem(arvore);
        printf("\n");
        imprimir_altura_e_total(arvore);
        printf("\n");
    }

    ab_destruir(&arvore);
}

void teste_consulta_e_busca() {
    No* arvore = NULL;
    int valores[] = {10, 20, 5, 15, 25};
    for (int i = 0; i < 5; i++) {
        arvore = avl_inserir(arvore, valores[i]);
    }

    int busca_valores[] = {15, 100};
    for (int i = 0; i < 2; i++) {
        int val = busca_valores[i];
        bool existe = ab_consulta(arvore, val);
        printf("Consulta %d: %s\n", val, existe ? "Encontrado" : "Não encontrado");
        No* nodo = avl_buscar(arvore, val);
        if (nodo != NULL)
            printf("Busca retornou nó com valor: %d\n", nodo->dado);
        else
            printf("Busca retornou NULL para valor %d\n", val);
    }

    ab_destruir(&arvore);
}

void exercicio() {
    No *arvore = NULL;
    int valores[] = {10, 20, 30, 5, 3, 50, 40, 70, 60, 90};
    for (int i = 0; i < 10; i++) {
        printf("Inserir %d\n", valores[i]);
        arvore = avl_inserir(arvore, valores[i]);
    }

    imprimir_altura_e_total(arvore);

    printf("\n--EmOrdem--\n");
    ab_em_ordem(arvore);
    printf("\n");

    ab_destruir(&arvore);
}

int main() {
    teste_rotacao_esquerda();
    teste_rotacao_direita();
    teste_rotacao_dupla_direita();
    teste_rotacao_dupla_esquerda();
    teste_remocao();
    teste_consulta_e_busca();
    exercicio();

    return 0;
}
