#include "arvore_avl.h"

/**************************************
* FUNÇÕES AUXILIARES
**************************************/

int max(int a, int b) {
   return (a > b) ? a : b;
}

int avl_fator_balanceamento(No *no) {
   return (no == NULL) ? 0 : ab_altura(no->esq) - ab_altura(no->dir);
}

No* novoNo(TipoElemento valor) {
   No* novo = (No*) malloc(sizeof(No));
   novo->dado = valor;
   novo->esq = novo->dir = NULL;
   novo->altura = 1;
   return novo;
}

No* avl_rotacao_direita(No *y) {
   No *x = y->esq;
   No *T2 = x->dir;

   x->dir = y;
   y->esq = T2;

   y->altura = max(ab_altura(y->esq), ab_altura(y->dir)) + 1;
   x->altura = max(ab_altura(x->esq), ab_altura(x->dir)) + 1;

   return x;
}

No* avl_rotacao_esquerda(No *x) {
   No *y = x->dir;
   No *T2 = y->esq;

   y->esq = x;
   x->dir = T2;

   x->altura = max(ab_altura(x->esq), ab_altura(x->dir)) + 1;
   y->altura = max(ab_altura(y->esq), ab_altura(y->dir)) + 1;

   return y;
}

No* avl_rotacao_dupla_direita(No *z) {
   z->esq = avl_rotacao_esquerda(z->esq);
   return avl_rotacao_direita(z);
}

No* avl_rotacao_dupla_esquerda(No *z) {
   z->dir = avl_rotacao_direita(z->dir);
   return avl_rotacao_esquerda(z);
}

/**************************************
* INSERÇÃO AVL
**************************************/
No* avl_inserir(No *raiz, TipoElemento elemento) {
   if (raiz == NULL)
      return novoNo(elemento);

   if (elemento < raiz->dado)
      raiz->esq = avl_inserir(raiz->esq, elemento);
   else if (elemento > raiz->dado)
      raiz->dir = avl_inserir(raiz->dir, elemento);
   else
      return raiz; // Não permite duplicatas

   raiz->altura = 1 + max(ab_altura(raiz->esq), ab_altura(raiz->dir));
   int fb = avl_fator_balanceamento(raiz);

   // Casos de desequilíbrio
   if (fb > 1 && elemento < raiz->esq->dado)
      return avl_rotacao_direita(raiz);

   if (fb < -1 && elemento > raiz->dir->dado)
      return avl_rotacao_esquerda(raiz);

   if (fb > 1 && elemento > raiz->esq->dado)
      return avl_rotacao_dupla_direita(raiz);

   if (fb < -1 && elemento < raiz->dir->dado)
      return avl_rotacao_dupla_esquerda(raiz);

   return raiz;
}

/**************************************
* BUSCA
**************************************/
No* avl_buscar(No* raiz, TipoElemento dado) {
   if (raiz == NULL || raiz->dado == dado)
      return raiz;

   if (dado < raiz->dado)
      return avl_buscar(raiz->esq, dado);
   else
      return avl_buscar(raiz->dir, dado);
}

/**************************************
* CONSULTA (bool)
**************************************/
bool ab_consulta(No* raiz, TipoElemento dado) {
   return avl_buscar(raiz, dado) != NULL;
}

/**************************************
* REMOÇÃO AVL
**************************************/
No* no_minimo(No* no) {
   No* atual = no;
   while (atual->esq != NULL)
      atual = atual->esq;
   return atual;
}

No* avl_remover(No* raiz, TipoElemento elemento) {
   if (raiz == NULL)
      return raiz;

   if (elemento < raiz->dado)
      raiz->esq = avl_remover(raiz->esq, elemento);
   else if (elemento > raiz->dado)
      raiz->dir = avl_remover(raiz->dir, elemento);
   else {
      // Nó com um ou nenhum filho
      if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
         No* temp = raiz->esq ? raiz->esq : raiz->dir;

         // Sem filho
         if (temp == NULL) {
            temp = raiz;
            raiz = NULL;
         } else
            *raiz = *temp; // Copia o conteúdo do filho

         free(temp);
      } else {
         // Nó com dois filhos: pega o menor da subárvore direita
         No* temp = no_minimo(raiz->dir);

         // Copia o valor
         raiz->dado = temp->dado;

         // Remove o sucessor
         raiz->dir = avl_remover(raiz->dir, temp->dado);
      }
   }

   // Se a árvore tinha apenas um nó
   if (raiz == NULL)
      return raiz;

   // Atualiza altura
   raiz->altura = 1 + max(ab_altura(raiz->esq), ab_altura(raiz->dir));

   // Verifica balanceamento
   int fb = avl_fator_balanceamento(raiz);

   // Casos de desequilíbrio

   // Esquerda pesada (LL)
   if (fb > 1 && avl_fator_balanceamento(raiz->esq) >= 0)
      return avl_rotacao_direita(raiz);

   // Esquerda-Direita (LR)
   if (fb > 1 && avl_fator_balanceamento(raiz->esq) < 0) {
      raiz->esq = avl_rotacao_esquerda(raiz->esq);
      return avl_rotacao_direita(raiz);
   }

   // Direita pesada (RR)
   if (fb < -1 && avl_fator_balanceamento(raiz->dir) <= 0)
      return avl_rotacao_esquerda(raiz);

   // Direita-Esquerda (RL)
   if (fb < -1 && avl_fator_balanceamento(raiz->dir) > 0) {
      raiz->dir = avl_rotacao_direita(raiz->dir);
      return avl_rotacao_esquerda(raiz);
   }

   return raiz;
}

/**************************************
* TRAVESSIAS
**************************************/
void ab_pre_ordem(No* raiz) {
   if (raiz != NULL) {
      printf("%d ", raiz->dado);
      ab_pre_ordem(raiz->esq);
      ab_pre_ordem(raiz->dir);
   }
}

void ab_em_ordem(No* raiz) {
   if (raiz != NULL) {
      ab_em_ordem(raiz->esq);
      printf("%d ", raiz->dado);
      ab_em_ordem(raiz->dir);
   }
}

void ab_pos_ordem(No* raiz) {
   if (raiz != NULL) {
      ab_pos_ordem(raiz->esq);
      ab_pos_ordem(raiz->dir);
      printf("%d ", raiz->dado);
   }
}

/**************************************
* DESTRUIÇÃO
**************************************/
void ab_destruir(No** enderecoRaiz) {
   if (*enderecoRaiz != NULL) {
      ab_destruir(&((*enderecoRaiz)->esq));
      ab_destruir(&((*enderecoRaiz)->dir));
      free(*enderecoRaiz);
      *enderecoRaiz = NULL;
   }
}

/**************************************
* INFORMAÇÕES
**************************************/
int ab_altura(No *raiz) {
   return (raiz == NULL) ? 0 : raiz->altura;
}

int ab_total_vertices(No *raiz) {
   if (raiz == NULL)
      return 0;
   return 1 + ab_total_vertices(raiz->esq) + ab_total_vertices(raiz->dir);
}
