/*
 * Descrição: Relacionado com a aula de revisão de vetores (arrays unidimensionais) e ponteiros.
 * Autor: Breno Farias da Silva.
 * Data: 32/04/2025.
 */

// Compile: gcc 06-structsAndPointers.c -o 06-structsAndPointers
// Run: ./06-structsAndPointers

#include <stdio.h> // Printf, scanf

#pragma pack(1) // Alinhamento de 1 byte. Assim, o sizeof(struct Aluno) dá 29 e não 32, pois explicitamente tiramos o alinhamento padrão de 4 bytes para 1 byte.

typedef struct {
	unsigned int ra;
	char nome[12];
	float notas[3];
	char aprovado;
} Aluno;

/*
 * Função principal do programa.
 * argc: quantidade de argumentos passados na chamada do programa.
 * argv: vetor com os argumentos passados na chamada do programa.
 * retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
*/
int main(int argc, char *argv[]) {
	Aluno a1 = {1, "Breno", {10.0, 9.9, 9.8}, 1};

	Aluno *p1 = &a1;

	printf("(a1.ra = %d, ", a1.ra);
	printf("(*p1).ra = %d, ", (*p1).ra);
	printf("p1->ra = %d\n", p1->ra);

	return 0;
}
