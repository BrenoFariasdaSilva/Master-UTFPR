package edu.utfpr;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import java.util.Arrays;

class BolicheTest {

   @Test
   void deveRetornarZeroParaTodasAsJogadasComZero() {
      int[] jogadas = new int[20];
      assertEquals(0, Boliche.calcular_pontuacao_boliche(jogadas));
   }

   @Test
   void devecalcular_pontuacao_bolicheSimples() {
      int[] jogadas = new int[20];
      Arrays.fill(jogadas, 3);
      assertEquals(60, Boliche.calcular_pontuacao_boliche(jogadas));
   }

   @Test
   void deveCalcularSpare() {
      int[] jogadas = {3, 7, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      assertEquals(14 + 6, Boliche.calcular_pontuacao_boliche(jogadas));
   }

   @Test
   void deveCalcularStrike() {
      int[] jogadas = {10, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
      assertEquals(18 + 8, Boliche.calcular_pontuacao_boliche(jogadas));
   }

   @Test
   void deveCalcularJogoPerfeito() {
      int[] jogadas = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
      assertEquals(300, Boliche.calcular_pontuacao_boliche(jogadas));
    }
}
