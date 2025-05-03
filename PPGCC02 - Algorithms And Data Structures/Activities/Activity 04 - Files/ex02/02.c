/*
 * Descrição: Faça um programa em C que possibilite modificar um arquivo texto informando opções por parâmetro para:
					- remover linhas em branco.
					- remover espaços nos inícios de frases.
					- remover espaços nos finais de frases.
					- substituir a ocorrência de uma string por outra.
 * Autor: Breno Farias da Silva.
 * Data: 03/05/2025.
 */

// Compile: gcc 02.c -o 02
// Run: ./02 test.txt --remove-blank-lines --trim-start --replace Hello World

#include <stdio.h> // printf, fopen, fclose, fgets, fputs
#include <stdlib.h> // perror
#include <string.h> // strlen, strcpy, strncat, strstr, memmove
#include <ctype.h> // isspace

#define MAX_LINES 1000 // Tamanho máximo do vetor de linhas
#define MAX_LINE 1024 // Tamanho máximo de cada linha

/*
 * Descrição: Lê as linhas de um arquivo texto e armazena em um vetor.
 * filename: nome do arquivo a ser lido.
 * lines: matriz para armazenar as linhas lidas.
 * lineCount: ponteiro para armazenar a quantidade de linhas lidas.
 * retorno: 1 em caso de sucesso, 0 em caso de erro.
 */
int read_file_lines(const char* filename, char lines[][MAX_LINE], int* lineCount) {
	FILE* file = fopen(filename, "r"); // Abre o arquivo para leitura

	if (!file) { // Verifica se o arquivo foi aberto corretamente
		perror("Erro ao abrir o arquivo");
		return 0;
	}

	*lineCount = 0;
	while (fgets(lines[*lineCount], MAX_LINE, file)) { // Lê cada linha do arquivo
		(*lineCount)++;
		if (*lineCount >= MAX_LINES) break; // Verifica se o limite de linhas foi atingido
	}
	
	fclose(file); // Fecha o arquivo

	return 1;
}

/*
* Descrição: Remove as linhas em branco do vetor de linhas.
* lines: matriz contendo as linhas do arquivo.
* lineCount: ponteiro para a quantidade de linhas, que será atualizada após remoção.
* retorno: void.
*/
void remove_blank_lines(char lines[][MAX_LINE], int* lineCount) {
	int j = 0;

	for (int i = 0; i < *lineCount; i++) { // Percorre todas as linhas
		char* p = lines[i]; // Ponteiro para a linha atual
		while (isspace(*p)) p++; // Ignora espaços em branco
		if (*p != '\0' && *p != '\n') { // Verifica se a linha não está vazia
			if (i != j) strcpy(lines[j], lines[i]); // Copia linha não vazia para a posição j
			j++; 
		}
	}
	
	*lineCount = j; // Atualiza a quantidade de linhas
}

/*
* Descrição: Remove os espaços em branco do início de uma linha.
* line: string que representa a linha a ser modificada.
* retorno: void.
*/
void trim_line_start(char* line) {
	int i = 0;
	while (isspace(line[i])) i++; // Ignora espaços em branco
	if (i > 0) memmove(line, line + i, strlen(line + i) + 1); // Move a linha para a esquerda
}

/*
* Descrição: Remove os espaços em branco do final de uma linha, exceto o '\n'.
* line: string que representa a linha a ser modificada.
* retorno: void.
*/
void trim_line_end(char* line) {
	int len = strlen(line);
	while (len > 0 && isspace(line[len - 1]) && line[len - 1] != '\n') { // Ignora espaços em branco
		line[len - 1] = '\0'; // Substitui o espaço por '\0'
		len--; // Reduz o tamanho da linha
	}
}

/*
 * Descrição: Substitui todas as ocorrências de uma substring por outra em uma linha.
 * line: string onde a substituição será realizada.
 * oldStr: substring a ser substituída.
 * newStr: nova substring a ser inserida no lugar da original.
 * retorno: void.
 */
void replace_string(char* line, const char* oldStr, const char* newStr) {
	char buffer[MAX_LINE];
	char* pos;
	const char* current = line;

	buffer[0] = '\0';

	while ((pos = strstr(current, oldStr)) != NULL) { // Encontra a substring
		strncat(buffer, current, pos - current); // Copia parte antes da substring
		strcat(buffer, newStr); // Adiciona nova substring
		current = pos + strlen(oldStr); // Avança na linha
	}

	strcat(buffer, current); // Adiciona o restante da string
	strcpy(line, buffer); // Atualiza linha original
}

/*
* Descrição: Processa os argumentos da linha de comando e aplica as transformações solicitadas.
* argc: número de argumentos da linha de comando.
* argv: vetor de strings com os argumentos passados.
* lines: matriz contendo as linhas do arquivo.
* lineCount: ponteiro para a quantidade de linhas.
* retorno: void.
*/
void process_arguments(int argc, char* argv[], char lines[][MAX_LINE], int* lineCount) {
	for (int i = 2; i < argc; i++) {
		if (strcmp(argv[i], "--remove-blank-lines") == 0) {
			remove_blank_lines(lines, lineCount);
		} else if (strcmp(argv[i], "--trim-start") == 0) {
			for (int j = 0; j < *lineCount; j++) trim_line_start(lines[j]);
		} else if (strcmp(argv[i], "--trim-end") == 0) {
			for (int j = 0; j < *lineCount; j++) trim_line_end(lines[j]);
		} else if (strcmp(argv[i], "--replace") == 0 && i + 2 < argc) {
			const char* oldStr = argv[i + 1];
			const char* newStr = argv[i + 2];
			for (int j = 0; j < *lineCount; j++) {
				replace_string(lines[j], oldStr, newStr);
			}
			i += 2;
		} else {
			printf("Parâmetro desconhecido ou mal formatado: %s\n", argv[i]);
		}
	}
}

/*
* Descrição: Escreve as linhas modificadas em um arquivo texto.
* filename: nome do arquivo a ser escrito.
* lines: matriz contendo as linhas a serem escritas.
* lineCount: quantidade de linhas a serem escritas.
* retorno: 1 em caso de sucesso, 0 em caso de erro.
*/
int write_file_lines(const char* filename, char lines[][MAX_LINE], int lineCount) {
	FILE* file = fopen(filename, "w");

	if (!file) {
		perror("Erro ao escrever no arquivo");
		return 0;
	}

	for (int i = 0; i < lineCount; i++) {
		fputs(lines[i], file); // Escreve a linha no arquivo
	}

	fclose(file);
	return 1;
}

/*
* Descrição: Função principal que gerencia leitura, modificação e escrita de um arquivo texto.
* argc: número de argumentos da linha de comando.
* argv: vetor de strings com os argumentos passados.
* retorno: 0 em caso de sucesso, 1 em caso de erro.
*/
int main(int argc, char* argv[]) {
	if (argc < 3) {
		printf("Uso: %s arquivo.txt [opções]\n", argv[0]);
		printf("Opções disponíveis:\n");
		printf("  --remove-blank-lines\n");
		printf("  --trim-start\n");
		printf("  --trim-end\n");
		printf("  --replace OLD NEW\n");
		return -1;
	}

	char lines[MAX_LINES][MAX_LINE];
	int lineCount;

	if (!read_file_lines(argv[1], lines, &lineCount)) { // Lê o arquivo
		return -1;
	}

	process_arguments(argc, argv, lines, &lineCount); // Processa os argumentos

	if (!write_file_lines(argv[1], lines, lineCount)) { // Escreve o arquivo
		return -1;
	}

	printf("Modificações aplicadas com sucesso ao arquivo '%s'.\n", argv[1]);
	return 0;
}
