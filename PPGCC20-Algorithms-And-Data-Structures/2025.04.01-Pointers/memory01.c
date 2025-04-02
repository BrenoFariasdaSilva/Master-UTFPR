/*
 * Descrição: Relacionado com a aula de revisão de ponteiros e alocação de memória.
 * Autor: Breno Farias da Silva.
 * Data: 01/04/2025.
 */

// Compile: gcc memory01.c -o memory01
// Run: ./memory01

// size memory01 --format=SysV
// O comando serve para ver a alocação estática de memória de um binário (text (código), bss (variáveis não inicializadas), e data(variáveis inicializadas))

const int valor = 100;
const double d=100.5;
const int num;

#include <stdio.h> // Printf, scanf
#include <limits.h> // Constantes como INT_MAX, INT_MIN, etc.

/*
 * Função principal do programa.
 * argc: quantidade de argumentos passados na chamada do programa.
 * argv: vetor com os argumentos passados na chamada do programa.
 * retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
*/
int main(int argc, char *argv[]) {
	printf("Tamanho \nsizeof(double) %ld, sizeof(d): %ld\n", sizeof(double), sizeof(d));

	short int test = 0;
	printf("test = 0: %d   ", test);
	printf("INT MAX: %d\n", INT_MAX);
	test = INT_MAX;
	printf("test = INT_MAX: %d\n", test);

	printf("FIM\n");

	return 0;
}
