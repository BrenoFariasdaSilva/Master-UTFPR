package edu.utfpr;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

import java.util.List;
import java.util.Arrays;

import org.junit.jupiter.api.Test;

public class AddTest {

    // Casos de exceção
    @Test
    void testLeftIsNull() {
        Add add = new Add();
        assertThrows(IllegalArgumentException.class, () -> {
            add.add(null, Arrays.asList(1, 2, 3));
        });
    }

    @Test
    void testRightIsNull() {
        Add add = new Add();
        assertThrows(IllegalArgumentException.class, () -> {
            add.add(Arrays.asList(1, 2, 3), null);
        });
    }

    // Casos de listas vazias
    @Test
    void testLeftIsEmpty() {
        Add add = new Add();
        List<Integer> result = add.add(Arrays.asList(), Arrays.asList(1, 2, 3));
        assertEquals(Arrays.asList(1, 2, 3), result);
    }

    @Test
    void testRightIsEmpty() {
        Add add = new Add();
        List<Integer> result = add.add(Arrays.asList(1, 2, 3), Arrays.asList());
        assertEquals(Arrays.asList(1, 2, 3), result);
    }

    // Casos de listas de tamanho 1
    @Test
    void testAddTwoOneDigitNumbersWithoutCarry() {
        Add add = new Add();
        List<Integer> result = add.add(Arrays.asList(2), Arrays.asList(3));
        assertEquals(Arrays.asList(5), result);
    }

    @Test
    void testAddTwoOneDigitNumbersWithCarry() {
        Add add = new Add();
        List<Integer> result = add.add(Arrays.asList(5), Arrays.asList(7));
        assertEquals(Arrays.asList(2, 1), result); // 5 + 7 = 12 -> [2, 1]
    }

    // Casos de listas com múltiplos elementos e tamanhos iguais
    @Test
    void testAddMultiDigitNumbersWithoutCarry() {
        Add add = new Add();
        List<Integer> result = add.add(Arrays.asList(1, 2, 3), Arrays.asList(4, 5, 6));
        assertEquals(Arrays.asList(5, 7, 9), result);
    }

    @Test
    void testAddMultiDigitNumbersWithCarryAndIncreaseSize() {
        Add add = new Add();
        List<Integer> result = add.add(Arrays.asList(9, 9, 9), Arrays.asList(1, 0, 0));
        assertEquals(Arrays.asList(0, 0, 0, 1), result); // 999 + 001 = 1000 -> [0, 0, 0, 1]
    }

    // Casos de listas de tamanhos diferentes
    @Test
    void testRightLongerThanLeft() {
        Add add = new Add();
        List<Integer> result = add.add(Arrays.asList(1, 2), Arrays.asList(3, 4, 5));
        assertEquals(Arrays.asList(4, 6, 5), result);
    }

    @Test
    void testLeftLongerThanRightWithCarry() {
        Add add = new Add();
        List<Integer> result = add.add(Arrays.asList(9, 9, 9), Arrays.asList(1));
        assertEquals(Arrays.asList(0, 0, 0, 1), result);
    }

    // Caso de valor limite
    @Test
    void testCarryOnLastDigit() {
        Add add = new Add();
        List<Integer> result = add.add(Arrays.asList(9), Arrays.asList(1));
        assertEquals(Arrays.asList(0, 1), result);
    }
}
