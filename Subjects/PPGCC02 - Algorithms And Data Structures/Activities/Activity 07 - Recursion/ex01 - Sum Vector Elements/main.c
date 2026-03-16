/*
 * Description: Escreva uma função recursiva que receba um número inteiro n > 0 e um vetor v de números com ponto flutuante com n elementos, e calcule e devolva a soma desses números. A função tem a seguinte assinatura: float soma(int n, float *v);
 * Author: Breno Farias da Silva.
 * Date: 27/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h>

float soma(int n, float *v) {
	if (n == 1) {
		return v[0]; // Caso base: apenas um elemento no vetor
	} else {
		return v[n - 1] + soma(n - 1, v); // Soma o último elemento com a soma dos anteriores
	}
}