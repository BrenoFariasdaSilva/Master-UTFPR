package edu.utfpr;

/*
 * ESPECIFICAÇÃO:
 * O método estático preenche() realiza o preenchimento à esquerda de uma string, utilizando outra string fornecida como preenchimento.
 * 
 * Assinatura:
 * public static String preenche(final String str, final int size, String stringPreenche)
 * 
 * Parâmetros:
 * - str: a string original a ser preenchida. Pode ser null.
 * - size: o tamanho final desejado da string preenchida.
 * - stringPreenche: a string usada como preenchimento. Se for null ou vazia, será substituída por um espaço (" ").
 * 
 * Regras de funcionamento:
 * - Se str for null, o método retorna null.
 * - Se o comprimento de str for maior ou igual ao valor de size, str é retornada sem modificações.
 * - Caso contrário, o método preenche à esquerda a string str com repetições de stringPreenche até atingir o tamanho size.
 * - O preenchimento é truncado caso ultrapasse o tamanho necessário.
 * 
 * Exemplo de uso:
 * preenche("abc", 5, "-") retorna "--abc"
 * preenche("abc", 6, "*") retorna "***abc"
 * preenche("abc", 3, "-") retorna "abc"
 * preenche(null, 4, "-") retorna null
 * preenche("abc", 5, null) retorna "  abc"
 */

public class PreencheUtil {

    public static String preenche(final String str, final int size, String stringPreenche) {
        if (str == null) {
            return null;
        }

        if (stringPreenche == null || stringPreenche.isEmpty()) {
            stringPreenche = " ";
        }

        int fillLength = size - str.length();
        if (fillLength <= 0) {
            return str;
        }

        StringBuilder filler = new StringBuilder();
        while (filler.length() < fillLength) {
            filler.append(stringPreenche);
        }

        return filler.substring(0, fillLength) + str;
    }
}
