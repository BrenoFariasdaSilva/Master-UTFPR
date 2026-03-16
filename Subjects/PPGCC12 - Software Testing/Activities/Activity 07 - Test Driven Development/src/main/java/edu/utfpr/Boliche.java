package edu.utfpr;

public class Boliche {

   public static int calcular_pontuacao_boliche(int[] jogadas) {
      int score = 0;
      int index = 0;

      for (int frame = 0; frame < 10; frame++) {
         if (jogadas[index] == 10) { // Strike
            score += 10 + jogadas[index + 1] + jogadas[index + 2];
            index++;
         } else if (jogadas[index] + jogadas[index + 1] == 10) { // Spare
            score += 10 + jogadas[index + 2];
            index += 2;
         } else {
            score += jogadas[index] + jogadas[index + 1];
            index += 2;
         }
      }

      return score;
   }
}
