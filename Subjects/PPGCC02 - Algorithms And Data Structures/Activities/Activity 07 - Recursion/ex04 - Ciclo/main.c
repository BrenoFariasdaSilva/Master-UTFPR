/*
 * Description: Considere o seguinte processo para gerar uma seqüência de números. Comece com um inteiro n. Se n é par, divida por 2. Se n é ímpar, multiplique por 3 e some 1. Repita esse processo com o novo valor de n, terminando quando n = 1. Por exemplo, a seqüência de números a seguir é gerada para n = 22
22 11 34 17 52 26 13 40 20 10 5 16 8 4 2 1 
É conjecturado que esse processo termina com n = 1 para todo inteiro n > 0. Para uma entrada n, o comprimento do ciclo de n é o número de elementos gerados na seqüência. No exemplo acima, o comprimento do ciclo de 22 é 16.

Considerando a informação acima, escreva:
uma função não-recursiva com a seguinte assinatura: int ciclo(int n) que receba um número inteiro positivo n, mostre a seqüência gerada pelo processo descrito acima na saída e devolva o comprimento do ciclo de n.
uma versão recursiva da função do item (a) com a seguinte assinatura: int cicloR(int n) que receba um número inteiro positivo n, mostre a seqüência gerada pelo processo descrito acima na saída e devolva o comprimento do ciclo de n.
 * Author: Breno Farias da Silva.
 * Date: 27/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h>

#include <stdio.h>

// Função não recursiva
int ciclo(int n) {
	int count = 1; // Contador do número de elementos na sequência
	printf("%d ", n);

	while (n != 1) {
		if (n % 2 == 0) {
			n = n / 2;
		} else {
			n = 3 * n + 1;
		}
		printf("%d ", n);
		count++;
	}

	printf("\n");
	return count;
}

// Função recursiva
int cicloR(int n) {
	printf("%d ", n);

	if (n == 1) {
		return 1; // Caso base
	}

	if (n % 2 == 0) {
		return 1 + cicloR(n / 2);
	} else {
		return 1 + cicloR(3 * n + 1);
	}
}