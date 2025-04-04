/*
 * Descrição: Relacionado com a aula de revisão de vetores (arrays unidimensionais) e ponteiros.
 * Autor: Breno Farias da Silva.
 * Data: 03/04/2025.
 */

// Compile: gcc 03-voidVectorsAndPointers.c -o 03-voidVectorsAndPointers
// Run: ./03-voidVectorsAndPointers

#include <stdio.h> // Printf, scanf

/*
 * Função principal do programa.
 * argc: quantidade de argumentos passados na chamada do programa.
 * argv: vetor com os argumentos passados na chamada do programa.
 * retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
*/
int main(int argc, char *argv[]) {
	int vector[3] = {1, 2, 3};
	void *p = vector;

	printf("v[1] = %d\n", (*(int *)p+1));
	return 0;
}
