#ifndef _HASH_H_
#define _HASH_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct registro {
  int chave;
  int dado;
};

typedef struct registro TipoElemento;
typedef struct hash Hash;

Hash* hash_criar(int tamanho);
int hash_tamanho(Hash *ha);
void hash_destruir(Hash **enderecoHash);
bool hash_inserir(Hash *ha, TipoElemento *elemento);
bool hash_remover_linear(Hash *h, int chave, TipoElemento **elemento);
bool hash_cheio(Hash *ha);
bool hash_vazio(Hash *ha);
void hash_imprimir(Hash *ha);
bool hash_ehValida(Hash *h);
bool hash_buscar_linear(Hash *h, int chave, TipoElemento **elemento);
void hash_listar(Hash *h);
float hash_fator_carga(Hash *h);
bool hash_redimensionar(Hash *h, int novo_tamanho);
int hash_colisoes(Hash *h);

#endif
