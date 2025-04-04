/*
 * Descrição: Relacionado com a aula de revisão de vetores (arrays unidimensionais) e ponteiros.
 * Autor: Breno Farias da Silva.
 * Data: 02/04/2025.
 */

// Compile: gcc 03-matrixAndPointers.c -o 03-matrixAndPointers
// Run: ./03-matrixAndPointers

#include <stdio.h> // Printf, scanf

/*
 * Função principal do programa.
 * argc: quantidade de argumentos passados na chamada do programa.
 * argv: vetor com os argumentos passados na chamada do programa.
 * retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
*/
int main(int argc, char *argv[]) {
	int m[3][2] = {{10, 20}, {30, 40}, {50, 60}};
	int *p = (int *) m;

	// Imprima o valor 60 da matriz ma[2][1]
	printf("ma[2][1] = %d, ", m[2][1]);
	printf("*(p+(2*2+1)) = %d, ", *(p+(2*2+1)));
	printf("p[5] = %d \n", p[5]);
	// printf("p[2][1] = %d, ", p[2][1]); // Não é válido, pois p é um ponteiro para inteiro e não para ponteiro de matriz
	return 0;
}
