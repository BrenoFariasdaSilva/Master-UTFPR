/*
 * Description: Podemos calcular a potência x^n de uma maneira mais eficiente. Observe primeiro que se n é uma potência de 2 então x^n pode ser computada usando sequências de quadrados. Por exemplo, x^4 é o quadrado de x^2 e assim x^4 pode ser computado usando somente duas multiplicações ao invés de três. Esta técnica pode ser usada mesmo quando n não é uma potência de 2, usando a seguinte fórmula:
Escreva uma função que receba dois números inteiros x e n, calcule e devolva x^n usando a fórmula acima. A função tem a seguinte assinatura int potencia(int x, int n);
 * Author: Breno Farias da Silva.
 * Date: 27/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

int potencia(int x, int n) {
	if (n == 0) {
		return 1; // Qualquer número elevado a 0 é 1
	}

	int meio = potencia(x, n / 2);

	if (n % 2 == 0) {
		return meio * meio;
	} else {
		return x * meio * meio;
	}
}
