#ifndef _ARVORE_BINARIA_H_
#define _ARVORE_BINARIA_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef int TipoElemento;
typedef struct no No;

struct no {
   TipoElemento dado;
   struct no *esq, *dir;
};

void ab_destruir(No** enderecoRaiz);
bool ab_inserir(No **enderecoRaiz, TipoElemento dado);
bool ab_remover(No **enderecoRaiz, TipoElemento dado);
bool ab_consulta(No* raiz, TipoElemento dado);
void ab_pre_ordem(No* raiz);
void ab_em_ordem(No* raiz);
void ab_pos_ordem(No* raiz);
int ab_altura(No *raiz);
int ab_total_vertices(No *raiz);
No* criar_no(TipoElemento elemento);
No* encontrar_minimo(No* raiz);
No* encontrar_maximo(No* raiz);
int ab_profundidade(No *raiz, TipoElemento dado);
int ab_contar_folhas(No *raiz);
int ab_contar_nos_internos(No *raiz);
bool ab_esta_balanceada(No *raiz);
bool ab_sao_iguais(No *raiz1, No *raiz2);
No* ab_sucessor(No *raiz, TipoElemento dado);
No* ab_predecessor(No *raiz, TipoElemento dado);

TipoElemento* ab_para_lista(No *raiz, int *tamanho);

#endif
