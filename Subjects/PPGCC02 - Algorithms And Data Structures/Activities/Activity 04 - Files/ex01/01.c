/*
* Descrição: Faça um programa em C que realiza leitura de strings e insere em posições específicas de um arquivo texto.
* Autor: Breno Farias da Silva.
* Data: 03/05/2025.
*/

// Compile: gcc 01.c -o 01
// Run: ./01

#include <stdio.h> // printf, scanf, fopen, fclose, fgets, fputs
#include <stdlib.h> // perror
#include <string.h> // strlen, strncpy, strcat, strcspn

#define MAX_CONTENT 10000 // Tamanho máximo do conteúdo do arquivo
#define MAX_STRING 1000 // Tamanho máximo da string a ser inserida
#define MAX_FILENAME 100 // Tamanho máximo do nome do arquivo

/*
* Descrição: Solicita ao usuário o nome do arquivo, a string a ser inserida e a posição da inserção.
* filename: buffer para armazenar o nome do arquivo.
* insertStr: buffer para armazenar a string a ser inserida.
* position: ponteiro para armazenar a posição de inserção.
* maxLen: tamanho máximo da string a ser inserida.
* retorno: 1 se a entrada for obtida com sucesso.
*/
int get_user_input(char* filename, char* insertStr, int* position, int maxLen) {
	printf("Digite o nome do arquivo texto: ");
	scanf("%s", filename);

	printf("Digite a string que deseja inserir: ");
	getchar(); // Limpa o caractere de nova linha pendente
	fgets(insertStr, maxLen, stdin);
	insertStr[strcspn(insertStr, "\n")] = '\0'; // Remove o '\n' do final

	printf("Digite a posição para inserção: ");
	scanf("%d", position);

	return 1;
}

/*
* Descrição: Lê o conteúdo de um arquivo texto para um buffer.
* filename: nome do arquivo a ser lido.
* buffer: buffer onde o conteúdo será armazenado.
* maxLen: tamanho máximo permitido para o buffer.
* retorno: 1 se leitura for bem-sucedida, 0 caso contrário.
*/
int read_file(const char* filename, char* buffer, int maxLen) {
	FILE* file = fopen(filename, "r"); // Abre o arquivo para leitura

	if (!file) { // Verifica se o arquivo foi aberto com sucesso
		perror("Erro ao abrir o arquivo para leitura");
		return 0;
	}

	int readBytes = fread(buffer, sizeof(char), maxLen - 1, file); // Lê o conteúdo do arquivo
	buffer[readBytes] = '\0'; // Garante terminação da string
	fclose(file); // Fecha o arquivo

	return 1;
}

/*
* Descrição: Verifica se a posição de inserção está dentro dos limites do conteúdo.
* pos: posição desejada.
* contentLen: tamanho do conteúdo original.
* retorno: 1 se posição for válida, 0 caso contrário.
*/
int is_valid_position(int pos, int contentLen) {
	return pos >= 0 && pos <= contentLen;
}

/*
* Descrição: Insere uma string em uma posição específica dentro de uma string original.
* original: string original.
* insertStr: string a ser inserida.
* position: posição onde a string será inserida.
* output: buffer onde o novo conteúdo será armazenado.
* retorno: void.
*/
void insert_string(const char* original, const char* insertStr, int position, char* output) {
	strncpy(output, original, position); // Copia até a posição desejada
	output[position] = '\0'; // Finaliza temporariamente a string
	strcat(output, insertStr); // Adiciona a string a ser inserida
	strcat(output, &original[position]); // Adiciona o restante do conteúdo original
}

/*
* Descrição: Escreve o conteúdo fornecido em um arquivo.
* filename: nome do arquivo a ser sobrescrito.
* content: conteúdo a ser escrito no arquivo. *
* retorno: 1 se escrita for bem-sucedida, 0 caso contrário.
*/
int write_file(const char* filename, const char* content) {
	FILE* file = fopen(filename, "w"); // Abre o arquivo para escrita

	if (!file) { // Verifica se o arquivo foi aberto com sucesso
		perror("Erro ao abrir o arquivo para escrita");
		return 0;
	}

	fputs(content, file); // Escreve o conteúdo no arquivo
	fclose(file); // Fecha o arquivo
	
	return 1;
}

/*
* Descrição: Função principal do programa.
* argc: quantidade de argumentos passados na chamada do programa.
* argv: vetor com os argumentos passados na chamada do programa.
* retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
*/
int main(void) {
	char filename[MAX_FILENAME];
	char insertStr[MAX_STRING];
	int position;

	char fileContent[MAX_CONTENT];
	char newContent[MAX_CONTENT];

	// Obtém as entradas do usuário
	if (!get_user_input(filename, insertStr, &position, MAX_STRING)) {
		return -1;
	}

	// Lê o conteúdo do arquivo
	if (!read_file(filename, fileContent, MAX_CONTENT)) {
		return -1;
	}

	// Valida a posição de inserção
	if (!is_valid_position(position, strlen(fileContent))) {
		printf("Erro: posição inválida. O arquivo possui %lu caracteres.\n", strlen(fileContent));
		return -1;
	}

	// Insere a string na posição desejada
	insert_string(fileContent, insertStr, position, newContent);

	// Escreve o novo conteúdo no arquivo
	if (!write_file(filename, newContent)) {
		return -1;
	}

	printf("Inserção realizada com sucesso no arquivo '%s'.\n", filename);
	return 0;
}
