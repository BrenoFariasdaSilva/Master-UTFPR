/*
 * Descrição:
 * Funções para criar e imprimir um aluno com um vetor dinâmico de notas.
 *
 * Autor: Breno Farias da Silva
 * Data: 25/04/2025
 */

// Compile and Run: gcc 07.c -o 07 && time ./07

#include <stdio.h> // Funções: printf, scanf
#include <stdlib.h> // Funções: malloc, free

// Definição da estrutura Aluno
typedef struct {
	unsigned int codigo;
	char nome[50];
	float *notas; // Ponteiro para armazenar as notas do aluno
	unsigned int qtdNotas; // Quantidade de notas
} Aluno;

/**
 * Função para criar um aluno dinamicamente e alocar espaço para suas notas.
 *
 * @param codigo Código do aluno.
 * @param nome Nome do aluno.
 * @param qtdNotas Quantidade de notas do aluno.
 * @return Ponteiro para a estrutura do aluno alocada dinamicamente.
 */
Aluno *criarAluno(unsigned int codigo, const char *nome, unsigned int qtdNotas) {
	// Aloca memória dinamicamente para o aluno
	Aluno *novoAluno = (Aluno *)malloc(sizeof(Aluno));

	if (novoAluno == NULL) {
		printf("Erro ao alocar memória para o aluno.\n");
		return NULL;
	}

	// Inicializa o código e o nome do aluno
	novoAluno->codigo = codigo;
	snprintf(novoAluno->nome, sizeof(novoAluno->nome), "%s", nome);

	// Aloca memória para o vetor de notas com base na quantidade de notas
	novoAluno->notas = (float *)malloc(qtdNotas * sizeof(float));
	if (novoAluno->notas == NULL) {
		printf("Erro ao alocar memória para as notas do aluno.\n");
		free(novoAluno); // Libera a memória alocada para o aluno
		return NULL;
	}

	// Inicializa a quantidade de notas
	novoAluno->qtdNotas = qtdNotas;

	return novoAluno;
}

/**
 * Função para imprimir os valores de um aluno.
 *
 * @param aluno Ponteiro para o aluno a ser impresso.
 */
void imprimirAluno(const Aluno *aluno) {
	if (aluno == NULL) {
		printf("Aluno não encontrado.\n");
		return;
	}

	// Exibe as informações do aluno
	printf("Aluno: %s\n", aluno->nome);
	printf("Código: %u\n", aluno->codigo);
	printf("Notas: ");
	for (unsigned int i = 0; i < aluno->qtdNotas; i++) {
		printf("%.2f ", aluno->notas[i]);
	}
	printf("\n");
}

/**
 * Função principal do programa.
 *
 * Demonstra a criação e impressão de um aluno.
 *
 * @return Código de status da execução (0: sucesso).
 */
int main() {
	// Exemplo 1: Criando um aluno com 3 notas
	Aluno *aluno1 = criarAluno(1001, "João Silva", 3);
	if (aluno1 != NULL) {
		aluno1->notas[0] = 7.5;
		aluno1->notas[1] = 8.0;
		aluno1->notas[2] = 6.5;

		printf("Detalhes do Aluno 1:\n");
		imprimirAluno(aluno1); // Imprime os detalhes do aluno
		free(aluno1->notas);	// Libera a memória alocada para as notas
		free(aluno1); // Libera a memória alocada para o aluno
	}

	// Exemplo 2: Criando um aluno com 5 notas
	Aluno *aluno2 = criarAluno(1002, "Maria Oliveira", 5);
	if (aluno2 != NULL) {
		aluno2->notas[0] = 9.0;
		aluno2->notas[1] = 8.5;
		aluno2->notas[2] = 7.0;
		aluno2->notas[3] = 6.0;
		aluno2->notas[4] = 9.5;

		printf("\nDetalhes do Aluno 2:\n");
		imprimirAluno(aluno2); // Imprime os detalhes do aluno
		free(aluno2->notas); // Libera a memória alocada para as notas
		free(aluno2); // Libera a memória alocada para o aluno
	}

	return 0;
}
