/*
 * Descrição: Revisão dos principais conceitos para a revisão para a primeira avaliação.
 * Autor: Breno Farias da Silva.
 * Data: 06/05/2025.
 */

#include <stdio.h> // Biblioteca para funções de entrada e saída, como printf e scanf.
#include <stdlib.h> // Biblioteca para alocação dinâmica de memória, como malloc e calloc.
#include <string.h> // Biblioteca para manipulação de strings, como strcmp, strcpy e strlen.

#pragma pack(1) // Define o alinhamento de memória para 1 byte.

/*
 * Estrutura que representa uma data de aniversário.
 * day: dia do aniversário (2 caracteres + '\0').
 * month: mês do aniversário (2 caracteres + '\0').
 * year: ano do aniversário (4 caracteres + '\0').
 */
typedef struct {
	char day[3]; // Dia do aniversário (ex.: "17").
	char month[3]; // Mês do aniversário (ex.: "04").
	char year[5]; // Ano do aniversário (ex.: "2001").
} Birthday;

/*
 * Estrutura que representa um usuário.
 * name: nome do usuário (até 9 caracteres + '\0').
 * age: idade do usuário.
 * date: data de aniversário do usuário (estrutura Birthday).
 */
typedef struct {
	char name[10]; // Nome do usuário (ex.: "Breno").
	unsigned short int age; // Idade do usuário (ex.: 25).
	Birthday date; // Data de aniversário do usuário.
} User;

/*
 * Função que imprime uma matriz 2D.
 * pMatrix: ponteiro para a matriz 2D.
 * m: número de linhas da matriz.
 * n: número de colunas da matriz.
 * retorno: 0 se bem-sucedido, -1 em caso de erro.
 */
int printMatrix(const int **pMatrix, const int m, const int n);

/*
 * Função que imprime os dados de um usuário estático.
 * user: estrutura do tipo User contendo os dados do usuário.
 * retorno: 0 se bem-sucedido.
 */
int printStaticUser(const User user);

/*
 * Função que imprime os dados de um usuário dinâmico.
 * user: ponteiro para a estrutura do tipo User contendo os dados do usuário.
 * retorno: 0 se bem-sucedido.
 */
int printDynamicUser(const User *user);

/*
 * Função que inicializa uma matriz 2D com valores sequenciais.
 * pMatrix: ponteiro para a matriz 2D.
 * m: número de linhas da matriz.
 * n: número de colunas da matriz.
 * retorno: 0 se bem-sucedido, -1 em caso de erro.
 */
int initializeMatrix(int **pMatrix, const int m, const int n);

/*
 * Implementação da função que imprime uma matriz 2D.
 */
int printMatrix(const int **pMatrix, const int m, const int n) {
	if (!pMatrix || m < 0 || n < 0) { // Verifica se a matriz é válida e se as dimensões são positivas.
		return -1; // Retorna erro se a matriz for inválida.
	}

	for (int i = 0; i < m; i++) { // Itera sobre as linhas da matriz.
		for (int j = 0; j < n; j++) { // Itera sobre as colunas da matriz.
			printf("%d ", pMatrix[i][j]); // Imprime o elemento atual.
		}
		printf("\n"); // Quebra de linha após cada linha da matriz.
	}
	printf("\n"); // Quebra de linha adicional após a matriz.

	return 0; // Retorna sucesso.
}

/*
 * Implementação da função que imprime os dados de um usuário estático.
 */
int printStaticUser(const User user) {
	printf("Static User: \n"); // Imprime o cabeçalho.
	printf("Name: %s\n", user.name); // Imprime o nome do usuário.
	printf("Age: %u\n", user.age); // Imprime a idade do usuário.
	printf("Birthday Date: %s/%s/%s\n\n", user.date.day, user.date.month, user.date.year); // Imprime a data de aniversário.

	return 0; // Retorna sucesso.
}

/*
 * Implementação da função que imprime os dados de um usuário dinâmico.
 */
int printDynamicUser(const User *user) {
	printf("Dynamic User: \n"); // Imprime o cabeçalho.
	printf("Name: %s\n", user->name); // Imprime o nome do usuário.
	printf("Age: %u\n", user->age); // Imprime a idade do usuário.
	printf("Birthday Date: %s/%s/%s\n\n", user->date.day, user->date.month, user->date.year); // Imprime a data de aniversário.

	return 0; // Retorna sucesso.
}

/*
 * Implementação da função que inicializa uma matriz 2D com valores sequenciais.
 */
int initializeMatrix(int **pMatrix, const int m, const int n) {
	if (!pMatrix || m < 0 || n < 0) { // Verifica se a matriz é válida e se as dimensões são positivas.
		return -1; // Retorna erro se a matriz for inválida.
	}

	int counter = 1; // Inicializa o contador para preencher a matriz.
	for (int i = 0; i < m; i++) { // Itera sobre as linhas da matriz.
		for (int j = 0; j < n; j++) { // Itera sobre as colunas da matriz.
			pMatrix[i][j] = counter++; // Atribui o valor atual do contador e incrementa.
		}
	}

	return 0; // Retorna sucesso.
}

/*
 * Função principal do programa.
 * argc: quantidade de argumentos passados na chamada do programa.
 * argv: vetor com os argumentos passados na chamada do programa.
 * retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
 */
int main(const int argc, const char *argv[]) {
	printf("argc: %d\n", argc); // Imprime a quantidade de argumentos.

	for (int i = 0; i < argc; i++) { // Itera sobre os argumentos.
		printf("argv[%d] = %s, strlen(argv[%d]) = %lu\n", i, argv[i], i, strlen(argv[i])); // Imprime o argumento atual e seu tamanho.
	}

	char programName[10]; // Declaração de uma string para armazenar o nome do programa.
	strcpy(programName, argv[0]); // Copia o nome do programa para a string.
	printf("\nprogramName = %s\n", programName); // Imprime o nome do programa.

	if (argc > 1) { // Verifica se há argumentos suficientes.
		char *endptr; // Ponteiro para verificar erros na conversão.
		long m = strtol(argv[1], &endptr, 10); // Converte o primeiro argumento para um número.
		long n = strtol(argv[2], NULL, 10);		// Converte o segundo argumento para um número.

		if (*endptr != '\0' || m <= 0) { // Verifica se a conversão foi bem-sucedida.
			printf("Erro: argumento '%s' não é um número válido ou é menor/igual a zero.\n", argv[1]);
			return 1; // Retorna erro.
		}

		printf("argv[0] = %s, strcmp(argv[0], \"./main\") = %d\n\n", argv[0], (int)strcmp(argv[0], "./main"));

		// Alocação de memória para uma matriz 2D.
		int **pMatrix = (int **) malloc(m * sizeof(int *));
		if (pMatrix == NULL) { // Verifica se a alocação foi bem-sucedida.
			printf("Erro: falha ao alocar memória para as linhas da matriz.\n");
			return 1; // Retorna erro.
		}

		for (int i = 0; i < m; i++) { // Itera sobre as linhas da matriz.
			pMatrix[i] = (int *) malloc(n * sizeof(int)); // Aloca memória para cada linha.
			if (pMatrix[i] == NULL) { // Verifica se a alocação foi bem-sucedida.
				printf("Erro ao alocar a %d linha", i);
				return -1; // Retorna erro.
			}
		}

		int resultPrint = printMatrix((const int **)pMatrix, m, n); // Imprime a matriz inicial.
		const int resultadoInit = initializeMatrix(pMatrix, m, n); // Inicializa a matriz.
		resultPrint = printMatrix((const int **)pMatrix, m, n); // Imprime a matriz inicializada.
	}

	User staticUser = {"Breno", 25, {"17", "04", "2001"}}; // Declaração de um usuário estático.
	printStaticUser(staticUser); // Imprime os dados do usuário estático.

	User *dynamicUser = (User *) malloc(sizeof(User)); // Aloca memória para um usuário dinâmico.
	strcpy(dynamicUser->name, "Breno"); // Inicializa o nome do usuário.
	dynamicUser->age = 25; // Inicializa a idade do usuário.
	strcpy(dynamicUser->date.day, "17"); // Inicializa o dia do aniversário.
	strcpy(dynamicUser->date.month, "04"); // Inicializa o mês do aniversário.
	strcpy(dynamicUser->date.year, "2001"); // Inicializa o ano do aniversário.
	printDynamicUser(dynamicUser); // Imprime os dados do usuário dinâmico.

	return 0; // Retorna sucesso.
}