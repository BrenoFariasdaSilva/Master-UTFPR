/*
* Descrição: Faça uma estrutura (struct) que represente uma fração (numerador e denominador).
             Elabore funções: (A) some duas frações e (B) simplifique uma fração.
             Elabore dois casos de teste com diferentes tamanhos de frações.  
* Autor: Breno Farias da Silva
* Data: 06/05/2025
*/

#include <stdio.h> // printf
#include <stdlib.h> // abs para módulo

// Structura que representa uma fração
typedef struct {
	int numerador;
	int denominador;
} Fraction;

/*
* Função auxiliar que calcula o máximo divisor comum (MDC) entre dois inteiros.
* a: primeiro inteiro.
* b: segundo inteiro.
* retorno: o valor do MDC entre a e b.
*/
int mdc(int a, int b) {
	a = abs(a);
	b = abs(b);

	while (b != 0) {
		int temp = b;
		b = a % b;
		a = temp;
	}

	return a;
}

/*
* Função que simplifica uma fração.
* fraction: fração a ser simplificada.
* retorno: fração simplificada.
*/
Fraction fractionsSimplify(Fraction fraction) {
	int divisor = mdc(fraction.numerador, fraction.denominador);
	fraction.numerador /= divisor;
	fraction.denominador /= divisor;
	return fraction;
}

/*
* Função que realiza a soma de duas frações.
* fraction1: primeira fração.
* fraction2: segunda fração.
* retorno: fração resultado da soma, já simplificada.
*/
Fraction fractionsSum(Fraction fraction1, Fraction fraction2) {
	Fraction result;

	// Encontrar denominador comum
	result.denominador = fraction1.denominador * fraction2.denominador;
	result.numerador = (fraction1.numerador * fraction2.denominador) + (fraction2.numerador * fraction1.denominador);

	return result;
}

/*
* Função de teste 1 do código. Executa operações com frações fixas.
* retorno: void
*/
void test1() {
	printf("Teste 01:\n");

	Fraction f1 = {2, 3};
	Fraction f2 = {1, 4};

	Fraction soma = fractionsSum(f1, f2);
	printf("Soma das frações: %d/%d + %d/%d = %d/%d\n", 
		f1.numerador, f1.denominador, f2.numerador, f2.denominador, soma.numerador, soma.denominador);

	Fraction f3 = {14, 28};
	Fraction simplificada = fractionsSimplify(f3);
	printf("Fração original: %d/%d -> Simplificada: %d/%d\n", 
		f3.numerador, f3.denominador, simplificada.numerador, simplificada.denominador);
}

/*
* Função de teste 2 do código. Executa operações com outras frações fixas.
* retorno: void
*/
void test2() {
	printf("\nTeste 02:\n");

	Fraction f1 = {4, 5};
	Fraction f2 = {3, 8};

	Fraction soma = fractionsSum(f1, f2);
	printf("Soma das frações: %d/%d + %d/%d = %d/%d\n", 
		f1.numerador, f1.denominador, f2.numerador, f2.denominador, soma.numerador, soma.denominador);

	Fraction f3 = {7, 11};
	Fraction simplificada = fractionsSimplify(f3);
	printf("Fração original: %d/%d -> Simplificada: %d/%d\n", 
		f3.numerador, f3.denominador, simplificada.numerador, simplificada.denominador);
}

/*
* Função principal do programa.
* argc: quantidade de argumentos passados na chamada do programa.
* argv: vetor com os argumentos passados na chamada do programa.
* retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
*/
int main(const int argc, const char* argv[]) {
	test1();
	test2();

	return 0;
}
