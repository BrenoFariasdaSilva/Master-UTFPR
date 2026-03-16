#include "hash.h"

#define TAM_INICIAL 100000

/**************************************
* DADOS
**************************************/

struct hash{
  int qtde, tamanho;
  TipoElemento **itens;
  int colisoes;
};


/**************************************
* FUNÇÕES AUXILIARES
**************************************/

bool hash_ehValida(Hash* h){
	return (h != NULL? true: false);
}

int hash_funcao(Hash* h, int chave){
	return chave % h->tamanho;
}


/**************************************
* IMPLEMENTAÇÃO
**************************************/

Hash* hash_criar(int tamanho){
	if (tamanho <= 0) return NULL;

	Hash *h = (Hash*) malloc(sizeof(Hash)); 
	if (h == NULL) return NULL;

	h->itens = (TipoElemento**) malloc(sizeof(TipoElemento)*tamanho); 
	if (h->itens == NULL) {
		free(h);
		return NULL;
	}

	for (int i=0; i<tamanho;i++){
		h->itens[i] = NULL;
	}

	h->qtde = 0;
	h->tamanho = tamanho;
	h->colisoes = 0; // Inicializa o contador de colisões

	return h;
}

void  hash_destruir(Hash** enderecoHash){
	if (enderecoHash == NULL) return;
	if (!hash_ehValida(*enderecoHash)) return;

	Hash *h = *enderecoHash;
	free(h->itens);
	free(h);
	*enderecoHash = NULL;
}

bool hash_inserir(Hash *h, TipoElemento *elemento){
	if (!hash_ehValida(h) || elemento == NULL) return false;

	int pos = hash_funcao(h, elemento->chave);
	if (h->itens[pos] != NULL) return false; // Não há tratamento de colisão
	h->itens[pos] = elemento;
	h->qtde++;
	return true;
}

bool hash_remover(Hash *h, int chave, TipoElemento **elemento){
	if (!hash_ehValida(h) || elemento == NULL) return false;

	int pos = hash_funcao(h, chave);
	if (h->itens[pos] == NULL) return false; // Não considera tratamento de colisão
	*elemento = h->itens[pos];  
	h->itens[pos] = NULL;
	h->qtde--;

	return true;
}

int hash_tamanho(Hash *ha){
	if (!hash_ehValida(ha)) return -1;
	return ha->qtde;
}

bool hash_cheio(Hash *ha){
	if (!hash_ehValida(ha)) return false;
	return (ha->qtde == ha->tamanho);
}

bool hash_vazio(Hash *ha){
	if (!hash_ehValida(ha)) return true;
	if (ha->qtde == 0)
		return true;
	return false;
}

void hash_imprimir(Hash *h){
	if (!hash_ehValida(h)) return;

	printf("[");
	for (int i = 0; i < h->tamanho-1;i++){
		if(h->itens[i] != NULL){
			printf("%d, ", h->itens[i]->chave);
		}
		else{
			printf("NULL, ");
		}
	}
	if(h->itens[h->tamanho-1] != NULL){
		printf("%d", h->itens[h->tamanho-1]->chave);	
	}else{
		printf("NULL");
	}
	
	printf("]\n");
}

// Novas Funções

bool hash_inserir_linear(Hash *h, TipoElemento *elemento){
	if (!hash_ehValida(h) || elemento == NULL || hash_cheio(h)) return false;

	int pos = hash_funcao(h, elemento->chave);
	for (int i = 0; i < h->tamanho; i++) {
		int newPos = (pos + i) % h->tamanho;
		if (h->itens[newPos] == NULL) {
			h->itens[newPos] = elemento;
			h->qtde++;
			return true;
		} else {
			h->colisoes++; // Incrementa o contador de colisões
		}
	}

	return false; // tabela cheia
}

bool hash_inserir_quadratica(Hash *h, TipoElemento *elemento){
	if (!hash_ehValida(h) || elemento == NULL || hash_cheio(h)) return false;

	int pos = hash_funcao(h, elemento->chave);
	for (int i = 0; i < h->tamanho; i++) {
		int newPos = (pos + i*i) % h->tamanho;
		if (h->itens[newPos] == NULL) {
			h->itens[newPos] = elemento;
			h->qtde++;
			return true;
		} else {
			h->colisoes++; // Incrementa o contador de colisões
		}
	}

	return false;
}

int hash_funcao_secundaria(Hash* h, int chave) {
	if (!hash_ehValida(h)) return 1;
	return 1 + (chave % (h->tamanho - 1));
}

bool hash_inserir_duplo(Hash *h, TipoElemento *elemento){
	if (!hash_ehValida(h) || elemento == NULL || hash_cheio(h)) return false;

	int h1 = hash_funcao(h, elemento->chave);
	int h2 = hash_funcao_secundaria(h, elemento->chave);

	for (int i = 0; i < h->tamanho; i++) {
		int newPos = (h1 + i * h2) % h->tamanho;
		if (h->itens[newPos] == NULL) {
			h->itens[newPos] = elemento;
			h->qtde++;
			return true;
		} else {
			h->colisoes++; // Incrementa o contador de colisões
		}
	}

	return false;
}

bool hash_buscar_linear(Hash *h, int chave, TipoElemento **elemento) {
	if (!hash_ehValida(h) || elemento == NULL) return false;

	int pos = hash_funcao(h, chave);
	for (int i = 0; i < h->tamanho; i++) {
		int newPos = (pos + i) % h->tamanho;
		if (h->itens[newPos] == NULL) return false;
		if (h->itens[newPos]->chave == chave) {
			*elemento = h->itens[newPos];
			return true;
		}
	}
	return false;
}

bool hash_buscar_quadratica(Hash *h, int chave, TipoElemento **elemento) {
	if (!hash_ehValida(h) || elemento == NULL) return false;

	int pos = hash_funcao(h, chave);
	for (int i = 0; i < h->tamanho; i++) {
		int newPos = (pos + i*i) % h->tamanho;
		if (h->itens[newPos] == NULL) return false;
		if (h->itens[newPos]->chave == chave) {
			*elemento = h->itens[newPos];
			return true;
		}
	}
	return false;
}

bool hash_buscar_duplo(Hash *h, int chave, TipoElemento **elemento) {
	if (!hash_ehValida(h) || elemento == NULL) return false;

	int h1 = hash_funcao(h, chave);
	int h2 = hash_funcao_secundaria(h, chave);

	for (int i = 0; i < h->tamanho; i++) {
		int newPos = (h1 + i * h2) % h->tamanho;
		if (h->itens[newPos] == NULL) return false;
		if (h->itens[newPos]->chave == chave) {
			*elemento = h->itens[newPos];
			return true;
		}
	}
	return false;
}

bool hash_remover_linear(Hash *h, int chave, TipoElemento **elemento) {
	if (!hash_ehValida(h) || elemento == NULL) return false;

	int pos = hash_funcao(h, chave);
	for (int i = 0; i < h->tamanho; i++) {
		int newPos = (pos + i) % h->tamanho;
		if (h->itens[newPos] == NULL) return false;
		if (h->itens[newPos]->chave == chave) {
			*elemento = h->itens[newPos];
			h->itens[newPos] = NULL;
			h->qtde--;
			return true;
		}
	}
	return false;
}

bool hash_remover_quadratica(Hash *h, int chave, TipoElemento **elemento) {
	if (!hash_ehValida(h) || elemento == NULL) return false;

	int pos = hash_funcao(h, chave);
	for (int i = 0; i < h->tamanho; i++) {
		int newPos = (pos + i*i) % h->tamanho;
		if (h->itens[newPos] == NULL) return false;
		if (h->itens[newPos]->chave == chave) {
			*elemento = h->itens[newPos];
			h->itens[newPos] = NULL;
			h->qtde--;
			return true;
		}
	}
	return false;
}

bool hash_remover_duplo(Hash *h, int chave, TipoElemento **elemento) {
	if (!hash_ehValida(h) || elemento == NULL) return false;

	int h1 = hash_funcao(h, chave);
	int h2 = hash_funcao_secundaria(h, chave);

	for (int i = 0; i < h->tamanho; i++) {
		int newPos = (h1 + i * h2) % h->tamanho;
		if (h->itens[newPos] == NULL) return false;
		if (h->itens[newPos]->chave == chave) {
			*elemento = h->itens[newPos];
			h->itens[newPos] = NULL;
			h->qtde--;
			return true;
		}
	}
	return false;
}

void hash_listar(Hash *h){
	if (!hash_ehValida(h)) return;

	printf("Elementos armazenados:\n");
	for (int i = 0; i < h->tamanho; i++) {
		if (h->itens[i] != NULL) {
			printf("Pos[%d]: Chave=%d, Dado=%d\n", i, h->itens[i]->chave, h->itens[i]->dado);
		}
	}
}

float hash_fator_carga(Hash *h) {
	if (!hash_ehValida(h) || h->tamanho == 0) return 0.0f;
	return (float) h->qtde / h->tamanho;
}

bool hash_redimensionar(Hash *h, int novo_tamanho) {
	if (!hash_ehValida(h) || novo_tamanho <= h->qtde) return false;

	// Cria nova tabela com novo tamanho
	TipoElemento **novos_itens = (TipoElemento **) malloc(sizeof(TipoElemento*) * novo_tamanho);
	if (novos_itens == NULL) return false;

	for (int i = 0; i < novo_tamanho; i++)
		novos_itens[i] = NULL;

	// Reinsere todos os elementos existentes na nova tabela
	for (int i = 0; i < h->tamanho; i++) {
		if (h->itens[i] != NULL) {
			TipoElemento *el = h->itens[i];
			int nova_pos = el->chave % novo_tamanho;

			// Sondagem linear para reinserção
			for (int j = 0; j < novo_tamanho; j++) {
				int pos_tentativa = (nova_pos + j) % novo_tamanho;
				if (novos_itens[pos_tentativa] == NULL) {
					novos_itens[pos_tentativa] = el;
					break;
				}
			}
		}
	}

	// Libera tabela antiga e atualiza ponteiro
	free(h->itens);
	h->itens = novos_itens;
	h->tamanho = novo_tamanho;

	return true;
}

int hash_colisoes(Hash *h){
	if (!hash_ehValida(h)) return -1;
	return h->colisoes;
}