/*
 * Descrição: Faça uma função que receba um vetor de inteiros e organize o vetor de forma a manter os valores pares à esquerda e os ímpares à direita.
              Com restrição, não é permitido o uso de um vetor auxiliar. Elabore três casos de teste com diferentes tamanhos de vetores.
 * Autor: Breno Farias da Silva
 * Data: 06/05/2025
*/

#include <stdio.h> // Biblioteca necessária para usar printf

/* Cabeçalhos das funções utilizadas no programa */
int formatVector(int* vector, const int size);
int printVector(const int* vector, const int size);
void runTest(int* vector, const int size, const char* description);

/*
 * Função que reorganiza os elementos do vetor, colocando os pares à esquerda e os ímpares à direita.
 * vector: ponteiro para o vetor de inteiros a ser reorganizado.
 * size: tamanho do vetor.
 * retorno: 0 em caso de sucesso, -1 se o ponteiro for nulo ou o tamanho inválido.
*/
int formatVector(int* vector, const int size) {
   // Verifica se o ponteiro é nulo ou se o tamanho é inválido
   if (vector == NULL || size < 0) {
      return -1;
   }

   int left = 0; // Ponteiro que começa da esquerda do vetor
   int right = size - 1; // Ponteiro que começa da direita do vetor

   // Laço principal que continua enquanto os ponteiros não se cruzarem
   while (left < right) {
      // Avança o ponteiro da esquerda enquanto encontrar números pares
      while (left < right && vector[left] % 2 == 0) {
         left++;
      }

      // Recuar o ponteiro da direita enquanto encontrar números ímpares
      while (left < right && vector[right] % 2 != 0) {
         right--;
      }

      // Se ambos os ponteiros pararam em posições trocadas (ímpar à esquerda e par à direita)
      if (left < right) {
         // Realiza a troca dos valores
         int temp = vector[left];
         vector[left] = vector[right];
         vector[right] = temp;
      }
   }

   return 0; // Indica sucesso
}

/*
* Função que imprime os elementos de um vetor na tela.
* vector: ponteiro para o vetor de inteiros.
* size: tamanho do vetor.
* retorno: 0 em caso de sucesso, -1 em caso de erro.
*/
int printVector(const int* vector, const int size) {
   // Verifica se o ponteiro é nulo ou se o tamanho é inválido
   if (vector == NULL || size < 0) {
      return -1;
   }

   // Imprime os elementos do vetor separados por espaço
   for (int i = 0; i < size; i++) {
      printf("%d ", vector[i]);
   }
   printf("\n");

   return 0; // Indica sucesso
}

/*
* Função que executa um teste genérico, imprimindo o vetor original e o vetor formatado.
* vector: ponteiro para o vetor a ser testado.
* size: tamanho do vetor.
* description: string que descreve o teste (ex: "Teste 01:").
* retorno: void
*/
void runTest(int* vector, const int size, const char* description) {
   
   printf("%s\n", description);

   // Imprime o vetor antes da formatação
   printf("Vetor Original: ");
   printVector(vector, size);

   // Chama a função para formatar o vetor
   const int resultado = formatVector(vector, size);

   // Se a formatação foi bem-sucedida, imprime o vetor formatado
   if (resultado == 0) {
      printf("Vetor Formatado: ");
      printVector(vector, size);
   } else {
      printf("Erro ao formatar o vetor.\n");
   }

   printf("\n"); // Espaço visual entre os testes
}

/*
* Função principal do programa.
* argc: quantidade de argumentos passados na chamada do programa.
* argv: vetor com os argumentos passados na chamada do programa.
* retorno: status de execução do programa (0: sem erros, caso contrário, código de erro).
*/
int main(const int argc, const char* argv[]) {
   // Vetores de exemplo com tamanhos e distribuições diferentes de pares e ímpares
   int v1[] = {1, 2, 3, 4, 5, 6};               // Alternado
   int v2[] = {2, 4, 6, 1, 3, 5, 7};            // Pares à frente, ímpares ao final
   int v3[] = {1, 3, 5, 7, 2, 4, 6, 8};         // Ímpares à frente, pares ao final

   // Executa os testes chamando a função genérica com os vetores definidos
   runTest(v1, sizeof(v1) / sizeof(v1[0]), "Teste 01:");
   runTest(v2, sizeof(v2) / sizeof(v2[0]), "Teste 02:");
   runTest(v3, sizeof(v3) / sizeof(v3[0]), "Teste 03:");

   return 0; // Fim do programa com sucesso
}
