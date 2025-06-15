#include "arvore_avl.h"

/**************************************
* FUNÇÕES AUXILIARES
**************************************/

int altura(No *no) {
    return (no == NULL) ? 0 : no->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int fator_balanceamento(No *no) {
    return (no == NULL) ? 0 : altura(no->esq) - altura(no->dir);
}

No* novoNo(TipoElemento valor) {
    No* novo = (No*) malloc(sizeof(No));
    novo->dado = valor;
    novo->esq = novo->dir = NULL;
    novo->altura = 1;
    return novo;
}

No* rotacao_direita(No *raiz) {
    No *novaRaiz = raiz->esq;
    No *subArvore = novaRaiz->dir;

    novaRaiz->dir = raiz;
    raiz->esq = subArvore;

    raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    novaRaiz->altura = max(altura(novaRaiz->esq), altura(novaRaiz->dir)) + 1;

    return novaRaiz;
}

No* rotacao_esquerda(No *raiz) {
    No *novaRaiz = raiz->dir;
    No *subArvore = novaRaiz->esq;

    novaRaiz->esq = raiz;
    raiz->dir = subArvore;

    raiz->altura = max(altura(raiz->esq), altura(raiz->dir)) + 1;
    novaRaiz->altura = max(altura(novaRaiz->esq), altura(novaRaiz->dir)) + 1;

    return novaRaiz;
}

No* rotacao_dupla_direita(No *raiz) {
    raiz->esq = rotacao_esquerda(raiz->esq);
    return rotacao_direita(raiz);
}

No* rotacao_dupla_esquerda(No *raiz) {
    raiz->dir = rotacao_direita(raiz->dir);
    return rotacao_esquerda(raiz);
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
        return raiz; // Não permite elementos duplicados

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    int fb = fator_balanceamento(raiz);

    // Casos de desequilíbrio

    // Esquerda pesada (LL)
    if (fb > 1 && elemento < raiz->esq->dado)
        return rotacao_direita(raiz);

    // Direita pesada (RR)
    if (fb < -1 && elemento > raiz->dir->dado)
        return rotacao_esquerda(raiz);

    // Esquerda-Direita (LR)
    if (fb > 1 && elemento > raiz->esq->dado)
        return rotacao_dupla_direita(raiz);

    // Direita-Esquerda (RL)
    if (fb < -1 && elemento < raiz->dir->dado)
        return rotacao_dupla_esquerda(raiz);

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
* CONSULTA
**************************************/
bool ab_consulta(No* raiz, TipoElemento dado) {
    if (raiz == NULL)
        return false;

    if (dado == raiz->dado)
        return true;
    else if (dado < raiz->dado)
        return ab_consulta(raiz->esq, dado);
    else
        return ab_consulta(raiz->dir, dado);
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
* ALTURA E TOTAL DE VÉRTICES
**************************************/
int ab_altura(No *raiz) {
    return (raiz == NULL) ? 0 : raiz->altura;
}

int ab_total_vertices(No *raiz) {
    if (raiz == NULL)
        return 0;
    return 1 + ab_total_vertices(raiz->esq) + ab_total_vertices(raiz->dir);
}
