// 3. Escreva uma função em C que receba uma matriz 3x3 de números inteiros como parâmetro e retorne a sua transposta.

int* matrizTransposta(int matriz[3][3]) {
   int transposta[3][3] = {0};

   for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
         transposta[i][j] = matriz[j][i];
      }
   }

   return transposta;
}
