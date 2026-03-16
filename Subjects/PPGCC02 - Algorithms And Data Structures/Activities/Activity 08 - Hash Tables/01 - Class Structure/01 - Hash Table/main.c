#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"

// Função para gerar inteiro aleatório entre low e high (inclusive)
int randomInteger(int low, int high) {
	double d = (double) rand() / ((double) RAND_MAX + 1);
	int k = d * (high - low + 1);
	return low + k;
}

// Insere elementos de 0 até n-1 usando inserção sem tratamento de colisão
void teste_inserir_sem_tratamento(int tamanho) {
	printf("Teste inserção SEM tratamento de colisão\n");
	Hash *h = hash_criar(tamanho);
	if (!h) {
		printf("Falha ao criar hash\n");
		return;
	}

	for (int i = 0; i < tamanho; i++) {
		TipoElemento *el = (TipoElemento*) malloc(sizeof(TipoElemento));
		el->chave = i;
		el->dado = i * 10;

		if (!hash_inserir(h, el)) {
			printf("Falha inserindo chave %d (colisão ou tabela cheia)\n", i);
			free(el);
		}
	}

	hash_imprimir(h);
	printf("Colisões ocorridas: %d\n", hash_colisoes(h));
	hash_destruir(&h);
}

// Insere elementos com sondagem linear
void teste_inserir_linear(int tamanho) {
	printf("Teste inserção COM sondagem LINEAR\n");
	Hash *h = hash_criar(tamanho);
	if (!h) {
		printf("Falha ao criar hash\n");
		return;
	}

	int i = 0;
	while (!hash_cheio(h)) {
		TipoElemento *el = (TipoElemento*) malloc(sizeof(TipoElemento));
		el->chave = randomInteger(0, tamanho * 2);
		el->dado = el->chave * 10;

		if (!hash_inserir_linear(h, el)) {
			free(el);
		} else {
			i++;
		}
	}

	printf("Inseridos %d elementos\n", i);
	hash_imprimir(h);
	printf("Colisões ocorridas: %d\n", hash_colisoes(h));
	hash_destruir(&h);
}

// Insere elementos com sondagem quadrática
void teste_inserir_quadratica(int tamanho) {
	printf("Teste inserção COM sondagem QUADRÁTICA\n");
	Hash *h = hash_criar(tamanho);
	if (!h) {
		printf("Falha ao criar hash\n");
		return;
	}

	int i = 0;
	while (!hash_cheio(h)) {
		TipoElemento *el = (TipoElemento*) malloc(sizeof(TipoElemento));
		el->chave = randomInteger(0, tamanho * 2);
		el->dado = el->chave * 10;

		if (!hash_inserir_quadratica(h, el)) {
			free(el);
		} else {
			i++;
		}
	}

	printf("Inseridos %d elementos\n", i);
	hash_imprimir(h);
	printf("Colisões ocorridas: %d\n", hash_colisoes(h));
	hash_destruir(&h);
}

// Insere elementos com duplo hashing
void teste_inserir_duplo(int tamanho) {
	printf("Teste inserção COM duplo hashing\n");
	Hash *h = hash_criar(tamanho);
	if (!h) {
		printf("Falha ao criar hash\n");
		return;
	}

	int i = 0;
	while (!hash_cheio(h)) {
		TipoElemento *el = (TipoElemento*) malloc(sizeof(TipoElemento));
		el->chave = randomInteger(0, tamanho * 2);
		el->dado = el->chave * 10;

		if (!hash_inserir_duplo(h, el)) {
			free(el);
		} else {
			i++;
		}
	}

	printf("Inseridos %d elementos\n", i);
	hash_imprimir(h);
	printf("Colisões ocorridas: %d\n", hash_colisoes(h));
	hash_destruir(&h);
}

// Função para testar busca linear
void teste_buscar_linear(Hash *h, int chave) {
	TipoElemento *res = NULL;
	if (hash_buscar_linear(h, chave, &res)) {
		printf("Encontrou chave %d com dado %d\n", chave, res->dado);
	} else {
		printf("Chave %d não encontrada\n", chave);
	}
}

// Função para testar remoção linear
void teste_remover_linear(Hash *h, int chave) {
	TipoElemento *res = NULL;
	if (hash_remover_linear(h, chave, &res)) {
		printf("Removido chave %d com dado %d\n", chave, res->dado);
		free(res);
	} else {
		printf("Falha ao remover chave %d\n", chave);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Uso: %s <tamanho_hash> <tipo_teste>\n", argv[0]);
		printf("Tipos de teste:\n");
		printf("  0 - inserção sem tratamento\n");
		printf("  1 - inserção sondagem linear\n");
		printf("  2 - inserção sondagem quadrática\n");
		printf("  3 - inserção duplo hashing\n");
		return 1;
	}

	int tamanho = atoi(argv[1]);
	int tipo = atoi(argv[2]);

	srand((unsigned)time(NULL));

	switch (tipo) {
		case 0:
			teste_inserir_sem_tratamento(tamanho);
			break;
		case 1:
			teste_inserir_linear(tamanho);
			break;
		case 2:
			teste_inserir_quadratica(tamanho);
			break;
		case 3:
			teste_inserir_duplo(tamanho);
			break;
		default:
			printf("Tipo de teste inválido\n");
			return 1;
	}

	return 0;
}
