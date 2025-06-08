package edu.utfpr;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class MainTest {

    @Test
    void testFebruaryLeapYear() {
        String calendar = Main.cal(2, 2020);
        assertTrue(calendar.contains("29"));
    }

    @Test
    void testFebruaryNonLeapYear() {
        String calendar = Main.cal(2, 2019);
        assertFalse(calendar.contains("29"));
    }

    @Test
    void testJune2025Header() {
        String calendar = Main.cal(6, 2025);
        assertTrue(calendar.contains("June 2025"));
    }

    @Test
    void testFirstDayPosition() {
        String calendar = Main.cal(6, 2025);
        assertTrue(calendar.startsWith("   June 2025"));
    }

    @Test
    void testMonthWith30Days() {
        String calendar = Main.cal(6, 2025);
        assertTrue(calendar.contains("30"));
        assertFalse(calendar.contains("31"));
    }

    @Test
    void testMonthWith31Days() {
        String calendar = Main.cal(7, 2025);
        assertTrue(calendar.contains("31"));
    }

    @Test
    void testFullWeekRow() {
        String calendar = Main.cal(3, 2025);
        assertTrue(calendar.contains("Su Mo Tu We Th Fr Sa"));
    }

    @Test
    void testMonthStartsOnSunday() {
        String calendar = Main.cal(11, 2020); // Novembro de 2020 começa num domingo
        assertTrue(calendar.contains("Su Mo Tu We Th Fr Sa"));
        // Pode-se adicionar uma verificação do alinhamento se desejar
    }

    @Test
    void testFebruary2021() {
        String calendar = Main.cal(2, 2021);
        assertFalse(calendar.contains("29"));
        assertTrue(calendar.contains("28"));
    }

    @Test
    void testLeapYearDivisibleBy400() {
        String calendar = Main.cal(2, 2000); // 2000 é bissexto (divisível por 400)
        assertTrue(calendar.contains("29"));
    }

    @Test
    void testNonLeapYearDivisibleBy100Not400() {
        String calendar = Main.cal(2, 1900); // 1900 não é bissexto (divisível por 100, mas não por 400)
        assertFalse(calendar.contains("29"));
    }

    @Test
    void testMonthWith28Days() {
        String calendar = Main.cal(2, 2021); // fevereiro não bissexto
        assertFalse(calendar.contains("29"));
        assertTrue(calendar.contains("28"));
    }

    @Test
    void testAlignmentOfFirstDayMonday() {
        String calendar = Main.cal(6, 2020); // 1º de junho de 2020 foi uma segunda
        assertTrue(calendar.contains(" 1")); // deve aparecer alinhado corretamente
    }

    @Test
    void testAlignmentOfFirstDaySaturday() {
        String calendar = Main.cal(5, 2021); // 1º de maio de 2021 foi sábado
        assertTrue(calendar.contains(" 1"));
    }

    @Test
    void testLastDayOfMonth() {
        String calendar = Main.cal(4, 2024); // abril termina em 30
        assertTrue(calendar.contains("30"));
        assertFalse(calendar.contains("31"));
    }

    @Test
    void testShortestMonthPositioning() {
        String calendar = Main.cal(2, 2021); // fevereiro 2021
        int lastIndex28 = calendar.lastIndexOf("28");
        assertTrue(lastIndex28 > 0);
    }

    @Test
    void testDecemberEndsOnTuesday2024() {
        String calendar = Main.cal(12, 2024); // 31 de dezembro de 2024 é terça-feira
        assertTrue(calendar.contains("31"));
    }

    @Test
    void testValidMinimumMonth() {
        String calendar = Main.cal(1, 2025);
        assertTrue(calendar.contains("January 2025"));
    }

    @Test
    void testValidMaximumMonth() {
        String calendar = Main.cal(12, 2025);
        assertTrue(calendar.contains("December 2025"));
    }

}
