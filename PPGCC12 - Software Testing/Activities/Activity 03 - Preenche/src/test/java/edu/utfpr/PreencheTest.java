import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import edu.utfpr.PreencheUtil;

public class PreencheTest {

    // Testes baseados em especificação

    @Test
    void testCaso1_strNull() {
        assertNull(PreencheUtil.preenche(null, 5, "-"));
    }

    @Test
    void testCaso2_strVazia() {
        assertEquals("...", PreencheUtil.preenche("", 3, "."));
    }

    @Test
    void testCaso3_1Caractere() {
        assertEquals("--a", PreencheUtil.preenche("a", 3, "-"));
    }

    @Test
    void testCaso4_tamanhoIgual() {
        assertEquals("abc", PreencheUtil.preenche("abc", 3, "*"));
    }

    @Test
    void testCaso5_diferenca1() {
        assertEquals("*abc", PreencheUtil.preenche("abc", 4, "*"));
    }

    @Test
    void testCaso6_preenchimentoLongo() {
        assertEquals("-=-abc", PreencheUtil.preenche("abc", 6, "-="));
    }

    @Test
    void testCaso7_stringPreencheVazia() {
        assertEquals("  abc", PreencheUtil.preenche("abc", 5, ""));
    }

    @Test
    void testCaso8_stringPreencheNull() {
        assertEquals("  abc", PreencheUtil.preenche("abc", 5, null));
    }

    @Test
    void testCaso9_strMaiorQueSize() {
        assertEquals("abcdef", PreencheUtil.preenche("abcdef", 4, "#"));
    }

    @Test
    void testCaso10_truncamentoPadrao() {
        assertEquals("1231231abc", PreencheUtil.preenche("abc", 10, "123"));
    }

    @Test
    void testCaso11_espacoExplicito() {
        assertEquals("  abc", PreencheUtil.preenche("abc", 5, " "));
    }

    // Testes adicionais para MC/DC

    @Test
    void testMC_DC_T8_strNullTodasCondicoesTrue() {
        assertNull(PreencheUtil.preenche(null, 5, ""));
    }

    @Test
    void testMC_DC_T16_todasCondicoesMenosStrNull() {
        assertEquals("abc", PreencheUtil.preenche("abc", 3, ""));
    }

    @Test
    void testMC_DC_T9_todasCondicoesFalse() {
        assertEquals("***abc", PreencheUtil.preenche("abc", 6, "*"));
    }

    @Test
    void testMC_DC_T13_stringPreencheNull() {
        assertEquals("  abc", PreencheUtil.preenche("abc", 5, null));
    }

    @Test
    void testMC_DC_T11_stringPreencheVazia() {
        assertEquals("  abc", PreencheUtil.preenche("abc", 5, ""));
    }

    @Test
    void testMC_DC_T10_fillLengthZero() {
        assertEquals("abcdef", PreencheUtil.preenche("abcdef", 4, "#"));
    }
}
