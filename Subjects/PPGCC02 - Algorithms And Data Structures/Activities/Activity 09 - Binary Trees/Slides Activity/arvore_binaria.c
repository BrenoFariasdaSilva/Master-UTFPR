#include "arvore_binaria.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**************************************
* DADOS
**************************************/

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

No* encontrar_minimo(No* raiz) {
   while (raiz->esq != NULL) raiz = raiz->esq;
   return raiz;
}

No* encontrar_maximo(No* raiz) {
   while (raiz->dir != NULL) raiz = raiz->dir;
   return raiz;
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

/* ------- NOVAS FUNÇÕES ------- */

// Profundidade do nó com dado "dado" (raiz é nível 0)
// Retorna -1 se não encontrar
int ab_profundidade(No *raiz, TipoElemento dado) {
   if (raiz == NULL) return -1;
   if (raiz->dado == dado) return 0;
   int prof = ab_profundidade(raiz->esq, dado);
   if (prof >= 0) return prof + 1;
   prof = ab_profundidade(raiz->dir, dado);
   if (prof >= 0) return prof + 1;
   return -1;
}

// Conta o número de folhas (nós sem filhos)
int ab_contar_folhas(No *raiz) {
   if (raiz == NULL) return 0;
   if (raiz->esq == NULL && raiz->dir == NULL) return 1;
   return ab_contar_folhas(raiz->esq) + ab_contar_folhas(raiz->dir);
}

// Conta nós internos (com pelo menos um filho)
int ab_contar_nos_internos(No *raiz) {
   if (raiz == NULL) return 0;
   if (raiz->esq == NULL && raiz->dir == NULL) return 0;
   return 1 + ab_contar_nos_internos(raiz->esq) + ab_contar_nos_internos(raiz->dir);
}

// Verifica se a árvore está balanceada (diferença de altura das subárvores <= 1)
static int ab_altura_balanceada(No *raiz) {
   if (raiz == NULL) return 0;
   int alt_esq = ab_altura_balanceada(raiz->esq);
   if (alt_esq == -1) return -1;
   int alt_dir = ab_altura_balanceada(raiz->dir);
   if (alt_dir == -1) return -1;
   if (abs(alt_esq - alt_dir) > 1) return -1;
   return 1 + (alt_esq > alt_dir ? alt_esq : alt_dir);
}

bool ab_esta_balanceada(No *raiz) {
   return ab_altura_balanceada(raiz) != -1;
}

// Verifica se duas árvores são iguais (mesma estrutura e valores)
bool ab_sao_iguais(No *raiz1, No *raiz2) {
   if (raiz1 == NULL && raiz2 == NULL) return true;
   if (raiz1 == NULL || raiz2 == NULL) return false;
   if (raiz1->dado != raiz2->dado) return false;
   return ab_sao_iguais(raiz1->esq, raiz2->esq) && ab_sao_iguais(raiz1->dir, raiz2->dir);
}

// Encontra o sucessor em ordem para o dado (nó com menor valor maior que dado)
No* ab_sucessor(No *raiz, TipoElemento dado) {
   No *sucessor = NULL;
   No *atual = raiz;
   while (atual != NULL) {
      if (dado < atual->dado) {
         sucessor = atual;
         atual = atual->esq;
      } else {
         atual = atual->dir;
      }
   }
   return sucessor;
}

// Encontra o predecessor em ordem para o dado (nó com maior valor menor que dado)
No* ab_predecessor(No *raiz, TipoElemento dado) {
   No *predecessor = NULL;
   No *atual = raiz;
   while (atual != NULL) {
      if (dado > atual->dado) {
         predecessor = atual;
         atual = atual->dir;
      } else {
         atual = atual->esq;
      }
   }
   return predecessor;
}

// Helper para contar quantos nós tem
static void ab_contar_nos(No *raiz, int *contador) {
   if (raiz == NULL) return;
   (*contador)++;
   ab_contar_nos(raiz->esq, contador);
   ab_contar_nos(raiz->dir, contador);
}

// Helper para preencher lista em ordem
static void ab_preencher_lista(No *raiz, TipoElemento *lista, int *index) {
   if (raiz == NULL) return;
   ab_preencher_lista(raiz->esq, lista, index);
   lista[*index] = raiz->dado;
   (*index)++;
   ab_preencher_lista(raiz->dir, lista, index);
}

// Converte árvore para lista ordenada, retorna array alocado dinamicamente e atualiza tamanho
TipoElemento* ab_para_lista(No *raiz, int *tamanho) {
   if (raiz == NULL) {
      *tamanho = 0;
      return NULL;
   }
   int total = 0;
   ab_contar_nos(raiz, &total);

   TipoElemento *lista = (TipoElemento*)malloc(total * sizeof(TipoElemento));
   int idx = 0;
   ab_preencher_lista(raiz, lista, &idx);
   *tamanho = total;
   return lista;
}
