#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"

// Gera inteiro aleatório entre low e high (inclusive)
int randomInteger(int low, int high) {
	double d = (double) rand() / ((double) RAND_MAX + 1);
	int k = d * (high - low + 1);
	return low + k;
}

// Testa inserção simples
void teste_inserir(Hash *h, int quantidade) {
	printf("\n=========== TESTE DE INSERÇÃO (%d elementos) ===========\n", quantidade);

	for (int i = 0; i < quantidade; i++) {
		TipoElemento *el = (TipoElemento*) malloc(sizeof(TipoElemento));
		el->chave = randomInteger(0, quantidade * 2);
		el->dado = el->chave * 10;

		if (!hash_inserir(h, el)) {
			// Não insere duplicado
			free(el);
		}
	}
	printf("Inserção concluída.\n");
}

// Testa busca
void teste_buscar(Hash *h, int chave) {
	TipoElemento *res = NULL;
	if (hash_buscar_linear(h, chave, &res)) {
		printf("  ✓ Encontrou chave %d com dado %d\n", chave, res->dado);
	} else {
		printf("  ✗ Chave %d não encontrada\n", chave);
	}
}

// Testa remoção
void teste_remover(Hash *h, int chave) {
	TipoElemento *res = NULL;
	if (hash_remover_linear(h, chave, &res)) {
		printf("  ✓ Removido chave %d com dado %d\n", chave, res->dado);
		free(res);
	} else {
		printf("  ✗ Falha ao remover chave %d\n", chave);
	}
}

int main() {
	srand((unsigned)time(NULL));

	int tamanho = 10;
	Hash *h = hash_criar(tamanho);
	if (!h) {
		printf("Erro: Falha ao criar a tabela hash.\n");
		return 1;
	}

	// Inserção
	teste_inserir(h, 15);

	// Impressão da estrutura
	printf("\n=========== ESTRUTURA DA TABELA HASH ===========\n");
	hash_imprimir(h);

	// Listagem dos elementos
	printf("\n=========== LISTAGEM COMPLETA DOS ELEMENTOS ===========\n");
	hash_listar(h);

	// Fator de carga
	printf("\n=========== FATOR DE CARGA ===========\n");
	printf("Fator de carga: %.2f\n", hash_fator_carga(h));

	// Busca
	printf("\n=========== TESTE DE BUSCA ===========\n");
	teste_buscar(h, 5);
	teste_buscar(h, 10);
	teste_buscar(h, 100); // provavelmente não existe

	// Remoção
	printf("\n=========== TESTE DE REMOÇÃO ===========\n");
	teste_remover(h, 5);
	teste_remover(h, 10);
	teste_remover(h, 100); // provavelmente não existe

	// Impressão após remoções
	printf("\n=========== ESTRUTURA APÓS REMOÇÕES ===========\n");
	hash_imprimir(h);

	// Verifica se está vazio
	printf("\n=========== VERIFICAÇÃO DE ESTADO ===========\n");
	printf("Hash está vazio? %s\n", hash_vazio(h) ? "Sim" : "Não");

	// Colisões
	printf("\n=========== COLISÕES ===========\n");
	printf("Número de colisões até agora: %d\n", hash_colisoes(h));

	// Redimensionamento
	printf("\n=========== REDIMENSIONAMENTO ===========\n");
	printf("Redimensionando para tamanho 20...\n");
	if (hash_redimensionar(h, 20)) {
		printf("Redimensionamento OK\n");
		hash_imprimir(h);
		printf("Novo fator de carga: %.2f\n", hash_fator_carga(h));
	} else {
		printf("Falha no redimensionamento\n");
	}

	// Liberação de memória
	printf("\n=========== FINALIZAÇÃO ===========\n");
	hash_destruir(&h);
	if (h == NULL) printf("Hash destruída com sucesso.\n");

	return 0;
}
