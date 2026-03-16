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
* FUNÇÕES AVL - REMOÇÃO
**************************************/
// Remoção balanceada na árvore AVL
No* avl_remover(No* raiz, TipoElemento elemento);

/**************************************
* FUNÇÕES DE CONSULTA
**************************************/
// Consulta se um elemento existe na árvore
bool ab_consulta(No* raiz, TipoElemento dado);

// Busca um nó com determinado valor e retorna o ponteiro (NULL se não existir)
No* avl_buscar(No* raiz, TipoElemento dado);

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

/**************************************
* FUNÇÕES AUXILIARES (ROTACIONAR)
**************************************/
// Rotação simples à direita
No* avl_rotacao_direita(No* y);
// Rotação simples à esquerda
No* avl_rotacao_esquerda(No* x);
// Rotação dupla à direita
No* avl_rotacao_dupla_direita(No* z);
// Rotação dupla à esquerda
No* avl_rotacao_dupla_esquerda(No* z);

// Obtém o fator de balanceamento do nó
int avl_fator_balanceamento(No* no);

#endif
