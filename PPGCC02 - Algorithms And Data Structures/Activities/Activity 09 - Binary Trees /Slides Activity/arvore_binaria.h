#ifndef _ARVORE_BINARIA_H_
#define _ARVORE_BINARIA_H_

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

typedef int TipoElemento;
typedef struct no No;

void ab_destruir(No** enderecoRaiz);
bool ab_inserir(No **enderecoRaiz, TipoElemento dado);
bool ab_remover(No **enderecoRaiz, TipoElemento dado);
bool ab_consulta(No* raiz, TipoElemento dado);
void ab_pre_ordem(No* raiz);
void ab_em_ordem(No* raiz);
void ab_pos_ordem(No* raiz);
int ab_altura(No *raiz);
int ab_total_vertices(No *raiz);

#endif