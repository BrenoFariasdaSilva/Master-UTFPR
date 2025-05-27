/*
* Descrição: Identifica o tipo de um arquivo com base em seu número mágico (magic number).
* Autor: Breno Farias da Silva.
* Data: 03/05/2025.
* 
* Compile: gcc 03.c -o 03
* Execute: ./03
*/

#include <stdio.h> // printf, scanf, perror, fprintf
#include <stdlib.h> // exit
#include <string.h> // strncmp

#define MAX_MAGIC_BYTES 8 // Número máximo de bytes mágicos a serem lidos
#define MAX_FILENAME 100 // Tamanho máximo do nome do arquivo

/*
* Função para obter o nome do arquivo informado pelo usuário.
* filename: buffer onde o nome será armazenado.
* maxLen: tamanho máximo do nome do arquivo.
* retorno: 1 se obtido com sucesso.
*/
int get_filename_from_user(char* filename, int maxLen) {
	printf("Digite o nome do arquivo que deseja analisar: ");

	if (fgets(filename, maxLen, stdin) == NULL) {
		fprintf(stderr, "Erro ao ler o nome do arquivo.\n");
		return 0;
	}

	// Remover o '\n' se presente
	filename[strcspn(filename, "\n")] = '\0';

	return 1;
}

/*
* Lê os primeiros bytes de um arquivo e armazena no buffer fornecido.
* filename: nome do arquivo a ser lido.
* buffer: vetor onde os bytes serão armazenados.
* numBytes: quantidade de bytes a serem lidos.
* retorno: 1 em caso de sucesso, 0 em caso de falha.
*/
int read_magic_bytes(const char* filename, unsigned char* buffer, size_t numBytes) {
	FILE* file = fopen(filename, "rb"); // Abre o arquivo em modo binário

	if (!file) { // Verifica se o arquivo foi aberto corretamente
		perror("Erro ao abrir o arquivo");
		return 0;
	}

	size_t bytesRead = fread(buffer, sizeof(unsigned char), numBytes, file); // Lê os bytes do arquivo
	fclose(file); // Fecha o arquivo

	if (bytesRead < numBytes) { // Verifica se o número de bytes lidos é menor que o esperado
		fprintf(stderr, "Erro: Arquivo muito pequeno para análise.\n");
		return 0;
	}

	return 1;
}

/*
* Função que exibe o tipo do arquivo com base no número mágico.
* magic: vetor de bytes contendo os primeiros bytes do arquivo.
* retorno: void.
*/
void identify_file_type(const unsigned char* magic) {
	if (magic[0] == 0xFF && magic[1] == 0xD8) {
		printf("Tipo identificado: JPEG\n");
	} else if (magic[0] == 0x89 && strncmp((char*)&magic[1], "PNG", 3) == 0) {
		printf("Tipo identificado: PNG\n");
	} else if (magic[0] == 'P' && magic[1] == 'K') {
		printf("Tipo identificado: ZIP (ou DOCX/XLSX/...) \n");
	} else if (magic[0] == 0x25 && magic[1] == 0x50 && magic[2] == 0x44 && magic[3] == 0x46) {
		printf("Tipo identificado: PDF\n");
	} else if (magic[0] == 0x7F && magic[1] == 'E' && magic[2] == 'L' && magic[3] == 'F') {
		printf("Tipo identificado: Executável ELF (Linux)\n");
	} else {
		printf("Tipo de arquivo desconhecido.\n");
	}
}

/*
* Função principal do programa.
* argc: quantidade de argumentos passados na chamada do programa.
* argv: vetor com os argumentos passados na chamada do programa.
* retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
*/
int main(void) {
	char filename[MAX_FILENAME];
	unsigned char magic[MAX_MAGIC_BYTES];

	if (!get_filename_from_user(filename, MAX_FILENAME)) { // Solicita o nome do arquivo ao usuário
		return -1;
	}

	if (!read_magic_bytes(filename, magic, MAX_MAGIC_BYTES)) { // Lê os primeiros bytes do arquivo
		return -1;
	}

	identify_file_type(magic); // Identifica o tipo do arquivo com base nos bytes lidos

	return 0;
}
