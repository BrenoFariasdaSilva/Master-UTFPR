/*
 * Descrição: Apresenta a estrutura básica de um programa em C.
 * Autor: Breno Farias da Silva.
 * Data: 27/03/2025.
 */

// Compile: gcc $filename.c -o $filenameWithoutExtension
// Run: ./filenameWithoutExtension

#include <stdio.h> // Printf, scanf
#include <stdint.h> // Tipos de dados inteiros: uint8_t, uint16_t, uint32_t, uint64_t.
#include <string.h> // Funções para manipulação de strings: strlen, strcpy, strcat, strcmp.

#define MAX 20 // Define uma constante.

/*
 * Função principal do programa.
 * argc: quantidade de argumentos passados na chamada do programa.
 * argv: vetor com os argumentos passados na chamada do programa.
 * retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
*/
int main(int argc, char *argv[]) {
	printf("arcg: %d\n", argc);
	printf("argv[0]: %s\n", argv[0]);

	// Characters:
	char charvalue; // 4 Bits / 1 Byte.

	// Integers:
	short shortvalue; // 8 Bits -> 2 Bytes.
	int intvalue; // 32 Bits -> 4 Bytes.
	long longvalue; // 64 Bits -> 8 Bytes.

	// Floating Point:
	float floatvalue; // 32 bits -> 4 Bytes.
	double doublevalue; // 64 bits -> 8 Bytes.

	// Unsigned Integers:
	uint8_t uint8value; // 8 Bits -> 1 Byte.
	uint16_t uint16value; // 16 Bits -> 2 Bytes.
	uint32_t uint32value; // 32 Bits -> 4 Bytes.
	uint64_t uint64value; // 64 Bits -> 8 Bytes.

	printf("Size of Long: %ld\n", sizeof(longvalue));
	printf("Size of Double: %ld\n", sizeof(doublevalue));

	// Strings
	char firstString[MAX] = "First String";
	printf("First String: %s\n", firstString);
	char secondString[] = "Second String";

	// print the secod string but limit the output to 4 characters.
	printf("Second String: %.4s\n", secondString);
	// print the secod string but limit the output to minimum 20 characters.
	printf("Second String: %20s\n", secondString);

	// Szie of the string.
	printf("Size of First String: %ld\n", sizeof(firstString));
	// The actual size of the string.
	printf("Size of First String: %ld\n", strlen(firstString));

	for (int i = 0; i < MAX; i++) {
		printf("First String[%d]: %c\n", i, firstString[i]);
	}

	// Arrays
	int firstvector[] = {1, 2, 3, 4, 5};
	printf("First Vector Pointer: %p\n", firstvector);
	printf("*First Vector: %d\n", *firstvector); // Equivalent to firstvector[0].
	printf("First Vector[0]: %d\n", firstvector[0]);
	
	printf("Entire First Vector: ");
	for (int i = 0; i < 5; i++) { // print the entire array.
		printf("%d ", i, firstvector[i]);
	}
	printf("\n");

	int secondvector[MAX] = {1, 2, 3, 4, 5};
	printf("Second Vector[0]: %d\n", secondvector[0]);

	printf("Type an string: ");
	char input[MAX];
	// gets(input); // Bad, as it does not limit the input size.
	// fgets(input, MAX, stdin); // Good, as it limits the input size.
	// scanf("%s", input); // Bad, as it does not limit the input size and stops at the first space. To fix it, use regular expressions.
	// scanf("%[^\n]", input); // Good, as it limits the input size and stops at the first new line.
	scanf("%20[^\n]", input); // Good, as it limits the input size and stops at the first new line, but you cant use the constant MAX. To fix it, use the fgets function.
	printf("Input: %s\n", input); 

	return 0;
}
