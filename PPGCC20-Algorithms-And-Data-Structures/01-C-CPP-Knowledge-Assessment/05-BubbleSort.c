// 5. Escreva uma função em C que receba um vetor de inteiros como parâmetro e implemente o algoritmo de ordenação Bubble Sort.

#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int vetor[], int n) {
   int temp = 0;
   for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < n - i - 1; j++) {
         if (vetor[j] > vetor[j + 1]) {
            // Troca os elementos
            temp = vetor[j];
            vetor[j] = vetor[j + 1];
            vetor[j + 1] = temp;
         }
      }
   }
}

void printArray(int vetor[], int n) {
   for (int i = 0; i < n; i++) {
      printf("%d ", vetor[i]);
   }
   printf("\n");
}

int main() {
   int vetor[] = {64, 34, 25, 12, 22, 11, 90};
   int n = sizeof(vetor) / sizeof(vetor[0]);

   printf("Vetor antes da ordenação: ");
   printArray(vetor, n);

   bubbleSort(vetor, n);

   printf("Vetor após a ordenação: ");
   printArray(vetor, n);

   return 0;
}
