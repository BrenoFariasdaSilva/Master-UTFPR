/*
 * Description: Escreva uma função recursiva que receba um número inteiro positivo n e devolva a soma de seus dígitos. A função tem a seguinte assinatura: int soma_digitos(int n);
 * Author: Breno Farias da Silva.
 * Date: 27/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

int soma_digitos(int n) {
	if (n < 10) {
		return n; // Caso base: n tem apenas um dígito
	} else {
		return (n % 10) + soma_digitos(n / 10); // Soma o último dígito com os anteriores
	}
}