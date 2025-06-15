#ifndef _ARVORE_AVL_H_
#define _ARVORE_AVL_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**************************************
* DEFINIÇÕES DE TIPOS
**************************************/
typedef int TipoElemento;

typedef struct no {
    TipoElemento dado;
    int altura;
    struct no *esq, *dir;
} No;

/**************************************
* FUNÇÕES AVL - INSERÇÃO
**************************************/
// Inserção balanceada na árvore AVL
No* avl_inserir(No *raiz, TipoElemento elemento);

/**************************************
* FUNÇÕES DE CONSULTA
**************************************/
// Consulta se um elemento existe na árvore
bool ab_consulta(No* raiz, TipoElemento dado);

/**************************************
* FUNÇÕES DE DESTRUIÇÃO
**************************************/
// Libera toda a memória da árvore
void ab_destruir(No** enderecoRaiz);

/**************************************
* FUNÇÕES DE TRAVESSIA
**************************************/
// Travessia pré-ordem
void ab_pre_ordem(No* raiz);
// Travessia em ordem
void ab_em_ordem(No* raiz);
// Travessia pós-ordem
void ab_pos_ordem(No* raiz);

/**************************************
* FUNÇÕES DE INFORMAÇÃO
**************************************/
// Retorna a altura da árvore
int ab_altura(No *raiz);
// Retorna o total de vértices (nós) da árvore
int ab_total_vertices(No *raiz);

#endif
