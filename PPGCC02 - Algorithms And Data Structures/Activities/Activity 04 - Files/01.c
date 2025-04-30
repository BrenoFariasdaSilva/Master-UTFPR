/*
 * Descrição: Insere uma string em uma posição específica de um arquivo existente,
 *            preservando o conteúdo original.
 *
 * Autor: Breno Farias da Silva
 * Data: 27/03/2025
 */

// Compile: gcc 01.c -o 01
// Run: ./01 nome_do_arquivo posicao texto_a_inserir

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Lê todo o conteúdo de um arquivo em memória.
 * 
 * @param nomeArquivo Caminho do arquivo a ser lido.
 * @param tamanho Ponteiro para armazenar o tamanho do conteúdo lido.
 * @return Ponteiro para o conteúdo do arquivo (deve ser liberado com free).
 */
char* lerArquivo(const char* nomeArquivo, long* tamanho) {
	FILE* arquivo = fopen(nomeArquivo, "rb");
	if (!arquivo) {
		perror("Erro ao abrir o arquivo para leitura");
		return NULL;
	}

	fseek(arquivo, 0, SEEK_END);
	*tamanho = ftell(arquivo);
	rewind(arquivo);

	char* conteudo = (char*) malloc(*tamanho + 1);
	if (!conteudo) {
		perror("Erro ao alocar memória");
		fclose(arquivo);
		return NULL;
	}

	fread(conteudo, 1, *tamanho, arquivo);
	conteudo[*tamanho] = '\0';

	fclose(arquivo);
	return conteudo;
}

/**
* Verifica se a posição de inserção é válida.
*
* @param posicao Posição a ser verificada.
* @param tamanho Tamanho do arquivo.
* @return 1 se for válida, 0 caso contrário.
*/
int posicaoValida(int posicao, long tamanho) {
	return posicao >= 0 && posicao <= tamanho;
}

/**
* Escreve o conteúdo original e o texto inserido no arquivo.
* 
* @param nomeArquivo Nome do arquivo a ser sobrescrito.
* @param conteudo Conteúdo original do arquivo.
* @param tamanho Tamanho do conteúdo original.
* @param posicao Posição onde o texto deve ser inserido.
* @param textoInserir Texto a ser inserido no arquivo.
*/
void inserirTextoNoArquivo(const char* nomeArquivo, const char* conteudo, long tamanho, int posicao, const char* textoInserir) {
	FILE* arquivo = fopen(nomeArquivo, "wb");
	if (!arquivo) {
		perror("Erro ao abrir o arquivo para escrita");
		return;
	}

	fwrite(conteudo, 1, posicao, arquivo); // Parte inicial
	fputs(textoInserir, arquivo); // Texto novo
	fwrite(conteudo + posicao, 1, tamanho - posicao, arquivo); // Resto

	fclose(arquivo);
}


/**
* Função principal do programa.
*/
int main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr, "Uso: %s <arquivo> <posicao> <texto>\n", argv[0]);
		return 1;
	}

	const char* nomeArquivo = argv[1];
	int posicao = atoi(argv[2]);
	const char* textoInserir = argv[3];
	long tamanho = 0;

	char* conteudo = lerArquivo(nomeArquivo, &tamanho);
	if (!conteudo)
		return 2;

	if (!posicaoValida(posicao, tamanho)) {
		fprintf(stderr, "Posição inválida. Deve estar entre 0 e %ld\n", tamanho);
		free(conteudo);
		return 3;
	}

	inserirTextoNoArquivo(nomeArquivo, conteudo, tamanho, posicao, textoInserir);

	printf("Texto \"%s\" inserido na posição %d com sucesso!\n", textoInserir, posicao);
	free(conteudo);
	return 0;
}
