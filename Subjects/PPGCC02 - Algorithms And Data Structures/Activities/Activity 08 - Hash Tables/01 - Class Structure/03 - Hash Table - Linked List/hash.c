#include "hash.h"

typedef struct nodo {
	TipoElemento *elemento;
	struct nodo *prox;
} Nodo;

struct hash {
	int qtde, tamanho;
	Nodo **itens; // vetor de listas encadeadas
	int colisoes;
};

/**************************************
* FUNÇÕES AUXILIARES
**************************************/

bool hash_ehValida(Hash* h){
	return (h != NULL);
}

int hash_funcao(Hash* h, int chave){
	return chave % h->tamanho;
}

// Cria um novo nodo para a lista encadeada
Nodo* nodo_criar(TipoElemento *elemento) {
	Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
	if (!novo) return NULL;
	novo->elemento = elemento;
	novo->prox = NULL;
	return novo;
}

/**************************************
* IMPLEMENTAÇÃO
**************************************/

Hash* hash_criar(int tamanho){
	if (tamanho <= 0) return NULL;

	Hash *h = (Hash*) malloc(sizeof(Hash));
	if (h == NULL) return NULL;

	h->itens = (Nodo**) malloc(sizeof(Nodo*) * tamanho);
	if (h->itens == NULL) {
		free(h);
		return NULL;
	}

	for (int i = 0; i < tamanho; i++) {
		h->itens[i] = NULL;
	}

	h->qtde = 0;
	h->tamanho = tamanho;
	h->colisoes = 0;

	return h;
}

void hash_destruir(Hash** enderecoHash){
	if (enderecoHash == NULL) return;
	if (!hash_ehValida(*enderecoHash)) return;

	Hash *h = *enderecoHash;

	// libera todas as listas encadeadas
	for (int i = 0; i < h->tamanho; i++) {
		Nodo *atual = h->itens[i];
		while (atual != NULL) {
			Nodo *tmp = atual;
			atual = atual->prox;
			if (tmp->elemento) free(tmp->elemento);
			free(tmp);
		}
	}

	free(h->itens);
	free(h);
	*enderecoHash = NULL;
}

bool hash_inserir(Hash *h, TipoElemento *elemento){
	if (!hash_ehValida(h) || elemento == NULL) return false;

	int pos = hash_funcao(h, elemento->chave);

	Nodo *atual = h->itens[pos];
	// Verifica se chave já existe (não insere duplicado)
	while(atual != NULL) {
		if (atual->elemento->chave == elemento->chave) {
			return false; // duplicado
		}
		atual = atual->prox;
	}

	// Incrementa colisão se já houver elemento no bucket
	if (h->itens[pos] != NULL) {
		h->colisoes++;
	}

	// Insere no início da lista encadeada
	Nodo *novo = nodo_criar(elemento);
	if (novo == NULL) return false;

	novo->prox = h->itens[pos];
	h->itens[pos] = novo;
	h->qtde++;

	return true;
}

bool hash_buscar_linear(Hash *h, int chave, TipoElemento **elemento){
	if (!hash_ehValida(h) || elemento == NULL) return false;

	int pos = hash_funcao(h, chave);
	Nodo *atual = h->itens[pos];
	while (atual != NULL) {
		if (atual->elemento->chave == chave) {
			*elemento = atual->elemento;
			return true;
		}
		atual = atual->prox;
	}
	return false;
}

bool hash_remover_linear(Hash *h, int chave, TipoElemento **elemento){
	if (!hash_ehValida(h) || elemento == NULL) return false;

	int pos = hash_funcao(h, chave);
	Nodo *atual = h->itens[pos];
	Nodo *ant = NULL;

	while (atual != NULL) {
		if (atual->elemento->chave == chave) {
			// Remove o nodo da lista
			if (ant == NULL) {
				h->itens[pos] = atual->prox;
			} else {
				ant->prox = atual->prox;
			}
			*elemento = atual->elemento;
			free(atual);
			h->qtde--;
			return true;
		}
		ant = atual;
		atual = atual->prox;
	}
	return false;
}

int hash_tamanho(Hash *ha){
	if (!hash_ehValida(ha)) return -1;
	return ha->qtde;
}

bool hash_cheio(Hash *ha){
	if (!hash_ehValida(ha)) return false;
	// Tabela nunca fica "cheia" com encadeamento
	return false;
}

bool hash_vazio(Hash *ha){
	if (!hash_ehValida(ha)) return true;
	return (ha->qtde == 0);
}

void hash_imprimir(Hash *h){
	if (!hash_ehValida(h)) return;

	printf("[");
	for (int i = 0; i < h->tamanho; i++) {
		printf("Pos[%d]: ", i);
		Nodo *atual = h->itens[i];
		if (atual == NULL) {
			printf("NULL");
		} else {
			while (atual != NULL) {
				printf("%d -> ", atual->elemento->chave);
				atual = atual->prox;
			}
			printf("NULL");
		}
		if (i < h->tamanho - 1) printf(", ");
	}
	printf("]\n");
}

void hash_listar(Hash *h){
	if (!hash_ehValida(h)) return;

	printf("Elementos armazenados:\n");
	for (int i = 0; i < h->tamanho; i++) {
		Nodo *atual = h->itens[i];
		while (atual != NULL) {
			printf("Pos[%d]: Chave=%d, Dado=%d\n", i, atual->elemento->chave, atual->elemento->dado);
			atual = atual->prox;
		}
	}
}

float hash_fator_carga(Hash *h) {
	if (!hash_ehValida(h) || h->tamanho == 0) return 0.0f;
	return (float) h->qtde / h->tamanho;
}

bool hash_redimensionar(Hash *h, int novo_tamanho) {
	if (!hash_ehValida(h) || novo_tamanho <= h->qtde) return false;

	Nodo **novos_itens = (Nodo **) malloc(sizeof(Nodo*) * novo_tamanho);
	if (novos_itens == NULL) return false;

	for (int i = 0; i < novo_tamanho; i++)
		novos_itens[i] = NULL;

	// Reinsere todos os elementos existentes na nova tabela
	for (int i = 0; i < h->tamanho; i++) {
		Nodo *atual = h->itens[i];
		while (atual != NULL) {
			TipoElemento *el = atual->elemento;
			int nova_pos = el->chave % novo_tamanho;

			// Insere no início da lista no novo vetor
			Nodo *novo = (Nodo*) malloc(sizeof(Nodo));
			if (!novo) {
				// Em caso de erro, libera parcialmente e retorna false
				for (int j = 0; j < novo_tamanho; j++) {
					Nodo *tmp = novos_itens[j];
					while (tmp != NULL) {
						Nodo *prox = tmp->prox;
						free(tmp);
						tmp = prox;
					}
				}
				free(novos_itens);
				return false;
			}
			novo->elemento = el;
			novo->prox = novos_itens[nova_pos];
			novos_itens[nova_pos] = novo;

			atual = atual->prox;
		}
	}

	// Libera as listas antigas (não libera os elementos, pois foram realocados)
	for (int i = 0; i < h->tamanho; i++) {
		Nodo *atual = h->itens[i];
		while (atual != NULL) {
			Nodo *tmp = atual;
			atual = atual->prox;
			free(tmp);
		}
	}

	free(h->itens);
	h->itens = novos_itens;
	h->tamanho = novo_tamanho;

	return true;
}

int hash_colisoes(Hash *h){
	if (!hash_ehValida(h)) return -1;
	return h->colisoes;
}
