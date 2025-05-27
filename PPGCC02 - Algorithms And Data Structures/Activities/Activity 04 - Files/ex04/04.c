/*
 * Descrição: Programa que retorna as dimensões (comprimento e altura) de uma imagem no formato GIF.
 * Autor: Breno Farias da Silva.
 * Data: 03/05/2025.
 *
 * Compile: gcc 04.c -o 04
 * Run: ./04 <nome_do_arquivo_gif>
 */

#include <stdio.h> // printf, perror
#include <stdlib.h> // exit
#include <stdint.h> // uint16_t (para representar as dimensões de 16 bits)

/*
 * Função para abrir e ler os bytes de um arquivo GIF.
 * filename: nome do arquivo GIF.
 * buffer: vetor onde os bytes serão armazenados.
 * numBytes: número de bytes a serem lidos do arquivo.
 * retorno: 1 se os bytes forem lidos com sucesso, 0 em caso de falha.
 */
int read_gif_header(const char *filename, unsigned char *buffer, size_t numBytes) {
	FILE *file = fopen(filename, "rb"); // Abre o arquivo em modo binário

	if (!file) { // Verifica se o arquivo foi aberto corretamente
		perror("Erro ao abrir o arquivo GIF");
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
 * Função para calcular as dimensões de uma imagem GIF.
 * gifHeader: buffer contendo os primeiros bytes do arquivo GIF.
 * comprimento: variável onde será armazenado o comprimento da imagem.
 * altura: variável onde será armazenada a altura da imagem.
 * retorno: 1 se as dimensões foram obtidas com sucesso, 0 caso contrário.
 */
int get_gif_dimensions(const unsigned char *gifHeader, uint16_t *comprimento, uint16_t *altura) {
	// A junção do 7º e 8º byte dá o comprimento (em 16 bits)
	*comprimento = (gifHeader[7] << 8) | gifHeader[6];
	// A junção do 9º e 10º byte dá a altura (em 16 bits)
	*altura = (gifHeader[9] << 8) | gifHeader[8];

	return 1; // Sucesso
}

/*
 * Função principal do programa.
 * argc: quantidade de argumentos passados na chamada do programa.
 * argv: vetor com os argumentos passados na chamada do programa.
 * retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
 */
int main(int argc, char *argv[]) {
	// Verifica se o usuário forneceu o nome do arquivo como argumento
	if (argc != 2) {
		fprintf(stderr, "Uso: %s <nome_do_arquivo_gif>\n", argv[0]);
		return -1;
	}

	const char *filename = argv[1];
	unsigned char gifHeader[10]; // Buffer para armazenar os primeiros 10 bytes do arquivo GIF

	// Lê os primeiros 10 bytes do arquivo GIF
	if (!read_gif_header(filename, gifHeader, sizeof(gifHeader))) {
		return -1;
	}

	uint16_t comprimento, altura;

	// Obtém as dimensões do GIF
	if (!get_gif_dimensions(gifHeader, &comprimento, &altura)) {
		return -1;
	}

	// Exibe as dimensões da imagem GIF
	printf("Dimensões da imagem GIF:\n");
	printf("Comprimento: %u pixels\n", comprimento);
	printf("Altura: %u pixels\n", altura);

	return 0;
}
