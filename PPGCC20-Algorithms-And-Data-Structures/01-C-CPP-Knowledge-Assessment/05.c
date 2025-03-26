// 5. Escreva uma função em C que receba um vetor de inteiros como parâmetro e implemente o algoritmo de ordenação Bubble Sort.

void bubbleSort(const int vetor[], int n) {
   int temp = 0;
   for (int i = 0; i < n -1; i++) {
      for (int j = 0; j < n - i - 1; j++) {
         if (arr[j] > arr[j + 1]) {
               temp = arr[j];
               arr[j] = arr[j+1];
               arr[j+1] = temp;
         }
      }
   }
}