/*
 * Descrição: Relacionado com a aula de revisão de vetores (arrays unidimensionais) e ponteiros.
 * Autor: Breno Farias da Silva.
 * Data: 02/04/2025.
 */

// Compile: gcc 02-vectorsAndPointers.c -o 02-vectorsAndPointers
// Run: ./02-vectorsAndPointers

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
	int **p2 = &p;

	printf("Endereço de vector: \nvector: %p, &vector: %p, &vector[0]: %p\n", vector, &vector, &vector[0]);

	printf("\nFormas de Imprimir o valor 3 que se encontra no índice 2 do vetor vector: \nvector[2]: %d, *(vector+2): %d, p[2]: %d, *(p+2): %d, *((*p2)+2): %d, (*p2)[2]: %d, p2[0][2]: %d\n", vector[2], *(vector+2), p[2], *(p+2), *((*p2)+2), (*p2)[2], p2[0][2]);

	int *x = &vector[2];
	printf("Formas de Imprimir o valor 1 que se encontra no índice 0 do vetor vector a partir do ponteiro x que aponta, inicialmente, para a posição do inteiro 3 no vetor vector \nx[-2]: %d, *(x-2): %d\n", x[-2], *(x-2));
	return 0;
}
