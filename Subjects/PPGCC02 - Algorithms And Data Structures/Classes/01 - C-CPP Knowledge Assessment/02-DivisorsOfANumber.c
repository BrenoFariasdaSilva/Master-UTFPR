// 2. Escreva uma função em C que receba um número inteiro como parâmetro e retorne todos os seus divisores em um vetor.

#include <stdio.h>
#include <stdlib.h>

int *arrayDivisores(const int number, int *size) {
   if (number == 0) {
      *size = 0;
      return NULL; // Não há divisores bem definidos para zero
   }

   int count = 0;

   // Contar o número de divisores
   for (int divisor_atual = 1; divisor_atual <= number; divisor_atual++) {
      if (number % divisor_atual == 0)
         count++;
   }

   // Alocar memória com base na quantidade de divisores
   int *divisors = (int *)malloc(sizeof(int) * count);
   if (divisors == NULL) {
      return NULL; // Verifica se a alocação falhou
   }

   // Preencher o vetor com os divisores
   int i = 0;
   for (int divisor_atual = 1; divisor_atual <= number; divisor_atual++) {
      if (number % divisor_atual == 0) {
         divisors[i++] = divisor_atual;
      }
   }

   *size = count;
   return divisors;
}

int main() {
   int number = -28, size;
   int *divisors = arrayDivisores(number, &size);

   if (divisors != NULL) {
      printf("Divisores de %d: ", number);
      for (int i = 0; i < size; i++) {
         printf("%d ", divisors[i]);
      }
      printf("\n");
      free(divisors); // Liberar memória alocada
   }

   return 0;
}
