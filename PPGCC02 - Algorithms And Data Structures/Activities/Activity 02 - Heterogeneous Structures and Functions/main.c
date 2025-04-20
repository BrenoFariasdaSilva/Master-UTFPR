/*
 * Descrição: Programa que gerencia um cadastro de alunos, permitindo inserir alunos, listar suas médias e filtrar por ano de nascimento.
 * Autor: Breno Farias da Silva.
 * Data: 20/04/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf
#include <string.h> // fgets, strlen, strcspn (para remover '\n' do final da string)

#define MAX_ALUNOS 20

/**
 * Estrutura para representar uma data (dia, mês e ano).
 */
typedef struct {
	int dia;
	int mes;
	int ano;
} Data;

/**
* Estrutura para representar um aluno com RA, nome, 3 notas e data de nascimento.
*/
typedef struct {
	int ra;
	char nome[100];
	float notas[3];
	Data nascimento;
} Aluno;

/**
* Calcula a média aritmética das três notas de um aluno.
* @param notas Vetor com 3 notas.
* @return Média aritmética das notas.
*/
float calcularMedia(float notas[3]) {
	return (notas[0] + notas[1] + notas[2]) / 3.0;
}

/**
* Insere um novo aluno no array de alunos.
* @param alunos Array de alunos.
* @param quantidade Ponteiro para a quantidade atual de alunos.
*/
void inserirAluno(Aluno alunos[], int *quantidade) {
	if (*quantidade >= MAX_ALUNOS) {
		printf("Número máximo de alunos atingido.\n");
		return;
	}

	Aluno novo;

	printf("RA: ");
	scanf("%d", &novo.ra);
	getchar(); // limpa o buffer do teclado

	printf("Nome: ");
	fgets(novo.nome, sizeof(novo.nome), stdin);
	novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove o '\n' ao final do nome

	for (int i = 0; i < 3; i++) {
		printf("Nota %d: ", i + 1);
		scanf("%f", &novo.notas[i]);
	}

	printf("Data de nascimento (DD MM AAAA): ");
	scanf("%d %d %d", &novo.nascimento.dia, &novo.nascimento.mes, &novo.nascimento.ano);

	alunos[*quantidade] = novo;
	(*quantidade)++;

	printf("Aluno inserido com sucesso!\n");
}

/**
* Lista os nomes e as médias das notas de todos os alunos cadastrados.
*
* @param alunos Array de alunos.
* @param quantidade Quantidade de alunos cadastrados.
*/
void listarMedias(Aluno alunos[], int quantidade) {
	if (quantidade == 0) {
		printf("Nenhum aluno cadastrado.\n");
		return;
	}

	printf("Listando alunos e médias:\n");
	for (int i = 0; i < quantidade; i++) {
		printf("Nome: %s | Média: %.2f\n", alunos[i].nome, calcularMedia(alunos[i].notas));
	}
}

/**
* Lista os nomes dos alunos que nasceram após um determinado ano.
*
* @param alunos Array de alunos.
* @param quantidade Quantidade de alunos cadastrados.
*/
void listarPorAnoNascimento(Aluno alunos[], int quantidade) {
	int ano;
	printf("Digite o ano de corte: ");
	scanf("%d", &ano);

	int encontrados = 0;
	printf("Alunos nascidos após %d:\n", ano);
	for (int i = 0; i < quantidade; i++) {
		if (alunos[i].nascimento.ano > ano) {
			printf("%s\n", alunos[i].nome);
			encontrados++;
		}
	}

	if (!encontrados) {
		printf("Nenhum aluno encontrado.\n");
	}
}

/*
* Função principal do programa.
* argc: quantidade de argumentos passados na chamada do programa.
* argv: vetor com os argumentos passados na chamada do programa.
* retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
*/
int main(int argc, char *argv[]) {
	Aluno alunos[MAX_ALUNOS];
	int quantidade = 0;
	int opcao;

	do {
		printf("\n==== MENU ====\n");
		printf("1. Inserir novo aluno\n");
		printf("2. Listar nomes e médias\n");
		printf("3. Listar alunos por ano de nascimento\n");
		printf("0. Sair\n");
		printf("Escolha uma opção: ");
		scanf("%d", &opcao);
		getchar(); // limpar buffer

		switch (opcao) {
			case 1:
				inserirAluno(alunos, &quantidade);
				break;
			case 2:
				listarMedias(alunos, quantidade);
				break;
			case 3:
				listarPorAnoNascimento(alunos, quantidade);
				break;
			case 0:
				printf("Encerrando o programa.\n");
				break;
			default:
				printf("Opção inválida!\n");
		}
	} while (opcao != 0);

	return 0;
}
