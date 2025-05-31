/*
 * Description: A seqüência de Fibonacci é uma seqüência de números inteiros positivos dada pela seguinte fórmula:
	Escreva uma função recursiva que receba um número inteiro positivo i>0 e devolva o i-ésimo termo da seqüência de Fibonacci, isto é, Fi. A função tem a seguinte assinatura: int Fib(int i)
 * Author: Breno Farias da Silva.
 * Date: 27/05/2025.
 */

// Compile: gcc main.c -o main
// Run: ./main

#include <stdio.h> // printf, scanf

int Fib(int i) {
	if (i == 1 || i == 2) {
		return 1; // Casos base: F1 = 1 e F2 = 1
	} else {
		return Fib(i - 1) + Fib(i - 2); // Passo recursivo
	}
}
