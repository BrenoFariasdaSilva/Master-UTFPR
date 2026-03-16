// 1. Escreva uma função em C que receba três números inteiros como parâmetros e retorne o maior deles.

#include <stdio.h>
#include <stdlib.h>

int biggest(const int a, const int b, const int c) {
   return (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c); // Operador ternário
}

int main() {
   const int x = 10, y = 25, z = 15;

   printf("O maior número é: %d\n", biggest(x, y, z));

   return 0;
}
