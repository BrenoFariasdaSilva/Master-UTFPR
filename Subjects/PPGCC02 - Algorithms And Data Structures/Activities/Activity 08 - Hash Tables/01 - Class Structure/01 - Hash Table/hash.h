#ifndef _HASH_H_
#define _HASH_H_

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

struct registro {
  int chave;
  int dado;
};

typedef struct registro TipoElemento;
typedef struct hash Hash;

Hash* hash_criar(int tamanho);
int   hash_tamanho(Hash *ha);
void  hash_destruir(Hash** enderecoHash);
bool  hash_inserir(Hash *ha, TipoElemento *elemento);
bool  hash_remover(Hash *h, int chave, TipoElemento **elemento);
bool  hash_cheio(Hash *ha);
bool  hash_vazio(Hash *ha);
void  hash_imprimir(Hash *ha);
bool hash_ehValida(Hash* h);

int  hash_funcao(Hash* h, int chave);
int  hash_funcao_secundaria(Hash* h, int chave);

bool hash_inserir_linear(Hash *h, TipoElemento *elemento);
bool hash_inserir_quadratica(Hash *h, TipoElemento *elemento);
bool hash_inserir_duplo(Hash *h, TipoElemento *elemento);

bool hash_buscar_linear(Hash *h, int chave, TipoElemento **elemento);
bool hash_buscar_quadratica(Hash *h, int chave, TipoElemento **elemento);
bool hash_buscar_duplo(Hash *h, int chave, TipoElemento **elemento);

bool hash_remover_linear(Hash *h, int chave, TipoElemento **elemento);
bool hash_remover_quadratica(Hash *h, int chave, TipoElemento **elemento);
bool hash_remover_duplo(Hash *h, int chave, TipoElemento **elemento);

void hash_listar(Hash *h);

float hash_fator_carga(Hash *h);
bool hash_redimensionar(Hash *h, int novo_tamanho);
int hash_colisoes(Hash *h);

#endif
