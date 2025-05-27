// 4. Escreva uma função em C que receba um arquivo de texto como parâmetro e conte o número de palavras que começam com a letra 'a'.

#include <stdio.h>
#include <stdlib.h>

void lerArquivo(const char *file_name) {
   FILE *fptr = fopen(file_name, "r");

   if (fptr == NULL) {
      printf("Erro ao abrir o arquivo.\n");
      return;
   }

   char ch;
   int count = 0, inWord = 0;

   while ((ch = fgetc(fptr)) != EOF) {
      if (ch >= 'A' && ch <= 'Z') {
         ch += 32; // Adiciona 32 para converter de maiúsculo para minúsculo
      }

      // Verifica se o caractere é alfabético
      if ((ch >= 'a' && ch <= 'z')) {
         if (!inWord) {
            inWord = 1; // Estamos começando uma palavra
            if (ch == 'a') {
               count++; // A palavra começa com 'a'
            }
         }
      }
      else {
         inWord = 0; // Caractere não alfabético, fim de uma palavra
      }
   }

   fclose(fptr);

   printf("Número de palavras que começam com 'a': %d\n", count);
}

int main() {
   lerArquivo("file.txt");
   return 0;
}
