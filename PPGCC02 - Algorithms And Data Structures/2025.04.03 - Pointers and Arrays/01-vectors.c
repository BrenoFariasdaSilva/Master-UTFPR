/*
 * Descrição: Relacionado com a aula de revisão de vetores (arrays unidimensionais).
 * Autor: Breno Farias da Silva.
 * Data: 02/04/2025.
 */

// Compile: gcc 01-vectors.c -o 01-vectors
// Run: ./01-vectors

#include <stdio.h> // Printf, scanf

/*
 * Função principal do programa.
 * argc: quantidade de argumentos passados na chamada do programa.
 * argv: vetor com os argumentos passados na chamada do programa.
 * retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
*/
int main(int argc, char *argv[]) {
	int vector[3] = {1, 2, 3};
	int *p = vector;
	printf("endereço de vector: %p\n", vector);
	printf("endereço de vector: %p\n", &vector);
	printf("endereço de vector: %p\n", &vector[0]);

	printf("vector[2]: %d, *(vector+2): %d, p[2]: %d, *(p+2): %d\n", vector[2], *(vector+2), p[2], *(p+2));

	return 0;
}
