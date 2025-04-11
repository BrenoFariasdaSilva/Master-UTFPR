// 3. Escreva uma função em C que receba uma matriz 3x3 de números inteiros como parâmetro e retorne a sua transposta.

#include <stdio.h>
#include <stdlib.h>

int* matrizTransposta(const int matriz[3][3]) {
   // Alocar dinamicamente memória para a matriz transposta (3x3)
   int* transposta = (int*) malloc(9 * sizeof(int)); // 3x3 = 9 elementos

   if (transposta == NULL) {
      printf("Erro na alocação de memória.\n");
      return NULL;
   }

   // Preencher a matriz transposta
   for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
         transposta[i * 3 + j] = matriz[j][i];
      }
   }

   return transposta;
}

void imprimirMatriz(const int* matriz) {
   for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
         printf("%d ", matriz[i * 3 + j]);
      }
      printf("\n");
   }
}

int main() {
   int matriz[3][3] = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9}
   };

   int* transposta = matrizTransposta(matriz);
   
   if (transposta != NULL) {
      printf("Matriz Transposta:\n");
      imprimirMatriz(transposta);
      free(transposta); // Liberar a memória alocada
   }

   return 0;
}
