#include "arvore_binaria.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**************************************
* DADOS
**************************************/

struct no {
    TipoElemento dado;
    struct no *esq, *dir;
};

/**************************************
* FUNÇÕES AUXILIARES
**************************************/

No* criar_no(TipoElemento elemento) {
    No* novo = (No*)malloc(sizeof(No));
    novo->dado = elemento;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

/**************************************
* IMPLEMENTAÇÃO
**************************************/

void ab_destruir(No **enderecoRaiz) {
    if (*enderecoRaiz == NULL) return;
    ab_destruir(&((*enderecoRaiz)->esq));
    ab_destruir(&((*enderecoRaiz)->dir));
    free(*enderecoRaiz);
    *enderecoRaiz = NULL;
}

bool ab_inserir(No **enderecoRaiz, TipoElemento elemento) {
    if (*enderecoRaiz == NULL) {
        *enderecoRaiz = criar_no(elemento);
        return true;
    }

    if (elemento < (*enderecoRaiz)->dado) {
        return ab_inserir(&(*enderecoRaiz)->esq, elemento);
    } else if (elemento > (*enderecoRaiz)->dado) {
        return ab_inserir(&(*enderecoRaiz)->dir, elemento);
    }

    return false; // elemento já existe
}

No* encontrar_minimo(No* raiz) {
    while (raiz->esq != NULL) raiz = raiz->esq;
    return raiz;
}

bool ab_remover(No** enderecoRaiz, TipoElemento dado) {
    if (*enderecoRaiz == NULL) return false;

    if (dado < (*enderecoRaiz)->dado) {
        return ab_remover(&(*enderecoRaiz)->esq, dado);
    } else if (dado > (*enderecoRaiz)->dado) {
        return ab_remover(&(*enderecoRaiz)->dir, dado);
    } else {
        // nó encontrado
        No* temp;
        if ((*enderecoRaiz)->esq == NULL) {
            temp = *enderecoRaiz;
            *enderecoRaiz = (*enderecoRaiz)->dir;
            free(temp);
        } else if ((*enderecoRaiz)->dir == NULL) {
            temp = *enderecoRaiz;
            *enderecoRaiz = (*enderecoRaiz)->esq;
            free(temp);
        } else {
            temp = encontrar_minimo((*enderecoRaiz)->dir);
            (*enderecoRaiz)->dado = temp->dado;
            return ab_remover(&(*enderecoRaiz)->dir, temp->dado);
        }
        return true;
    }
}

void ab_pre_ordem(No* raiz) {
    if (raiz == NULL) return;
    printf("%d ", raiz->dado);
    ab_pre_ordem(raiz->esq);
    ab_pre_ordem(raiz->dir);
}

void ab_em_ordem(No* raiz) {
    if (raiz == NULL) return;
    ab_em_ordem(raiz->esq);
    printf("%d ", raiz->dado);
    ab_em_ordem(raiz->dir);
}

void ab_pos_ordem(No* raiz) {
    if (raiz == NULL) return;
    ab_pos_ordem(raiz->esq);
    ab_pos_ordem(raiz->dir);
    printf("%d ", raiz->dado);
}

int ab_altura(No *raiz) {
    if (raiz == NULL) return -1;
    int alt_esq = ab_altura(raiz->esq);
    int alt_dir = ab_altura(raiz->dir);
    return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

int ab_total_vertices(No *raiz) {
    if (raiz == NULL) return 0;
    return 1 + ab_total_vertices(raiz->esq) + ab_total_vertices(raiz->dir);
}

bool ab_consulta(No* raiz, TipoElemento dado) {
    if (raiz == NULL) return false;
    if (dado == raiz->dado) return true;
    if (dado < raiz->dado)
        return ab_consulta(raiz->esq, dado);
    else
        return ab_consulta(raiz->dir, dado);
}
