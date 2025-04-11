/*
 * Descrição: Relacionado com a aula de revisão de vetores (arrays unidimensionais) e ponteiros.
 * Autor: Breno Farias da Silva.
 * Data: 32/04/2025.
 */

// Compile: gcc 05-structs.c -o 05-structs
// Run: ./05-structs

#include <stdio.h> // Printf, scanf

#pragma pack(1) // Alinhamento de 1 byte. Assim, o sizeof(struct Aluno) dá 29 e não 32, pois explicitamente tiramos o alinhamento padrão de 4 bytes para 1 byte.

struct Aluno {
	unsigned int ra;
	char nome[12];
	float notas[3];
	char aprovado;
};

/*
 * Função principal do programa.
 * argc: quantidade de argumentos passados na chamada do programa.
 * argv: vetor com os argumentos passados na chamada do programa.
 * retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
*/
int main(int argc, char *argv[]) {
	printf("#Ppragma pack(1) - SizeOf(struct Aluno): %d\n", sizeof(struct Aluno));
	return 0;
}
