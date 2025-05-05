/*
 * Descrição: 
 * Exemplos de utilização das funções que criam dinamicamente e imprimem um produto.
 *
 * Autor: Breno Farias da Silva
 * Data: 25/04/2025
 */

// Compile and Run: gcc 06.c -o 06 && time ./06

#include <stdio.h>  // Funções: printf, scanf
#include <stdlib.h> // Funções: malloc, free

// Definição da estrutura Produto
typedef struct {
	unsigned int codigo;
	char nome[50];
	float preco;
} Produto;

/**
* Função para criar um produto dinamicamente e inicializar seus valores.
*
* @param codigo Código do produto.
* @param nome Nome do produto.
* @param preco Preço do produto.
* @return Ponteiro para o produto alocado dinamicamente.
*/
Produto* criarProduto(unsigned int codigo, const char* nome, float preco) {
	// Aloca memória dinamicamente para o produto
	Produto* novoProduto = (Produto*) malloc(sizeof(Produto));
	
	if (novoProduto == NULL) {
		printf("Erro ao alocar memória para o produto.\n");
		return NULL;
	}

	// Inicializa os valores do produto
	novoProduto->codigo = codigo;
	snprintf(novoProduto->nome, sizeof(novoProduto->nome), "%s", nome); // Copia o nome com segurança
	novoProduto->preco = preco;

	return novoProduto;
}

/**
* Função para imprimir os valores de um produto.
*
* @param produto Ponteiro para o produto a ser impresso.
*/
void imprimirProduto(const Produto* produto) {
	if (produto == NULL) {
		printf("Produto não encontrado.\n");
		return;
	}

	// Exibe os atributos do produto
	printf("Produto: %s\n", produto->nome);
	printf("Código: %u\n", produto->codigo);
	printf("Preço: %.2f\n", produto->preco);
}

/**
* Função principal do programa.
* Demonstra a criação e impressão de um produto.
* @return Código de status da execução (0: sucesso).
*/
int main() {
	// Exemplo 1: Criando e imprimindo um único produto
	Produto* p1 = criarProduto(101, "Cadeira", 150.75);
	printf("Detalhes do Produto 1:\n");
	imprimirProduto(p1);  // Imprime os detalhes do produto
	free(p1); // Libera a memória alocada para o produto

	// Exemplo 2: Criando e imprimindo outro produto
	Produto* p2 = criarProduto(102, "Mesa", 250.00);
	printf("\nDetalhes do Produto 2:\n");
	imprimirProduto(p2);  // Imprime os detalhes do produto
	free(p2); // Libera a memória alocada para o produto

	// Exemplo 3: Produto com outro nome e preço
	Produto* p3 = criarProduto(103, "Cama", 1200.50);
	printf("\nDetalhes do Produto 3:\n");
	imprimirProduto(p3);  // Imprime os detalhes do produto
	free(p3); // Libera a memória alocada para o produto

	return 0;
}
