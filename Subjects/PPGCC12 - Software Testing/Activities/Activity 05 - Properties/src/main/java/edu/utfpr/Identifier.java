package edu.utfpr;


/*
 
 * ESPECIFICACAO: O programa deve determinar se um identificador é ou não 
 * válido em 'Silly Pascal' (uma estranha variante do Pascal). Um identificador 
 * válido deve comecar com uma letra e conter apenas letras ou dígitos. 
 * Além disso, deve ter no minimo 1 caractere e no maximo 6 caracteres de comprimento.
 */

public class Identifier {
    public boolean validateIdentifier(String s) {
        char achar;
        boolean valid_id = false;
        achar = s.charAt(0);
        valid_id = ((achar >= 'A') && (achar <= 'Z')) || ((achar >= 'a') && (achar <= 'z'));
      
        if (s.length() > 1) {
            achar = s.charAt(1);
            int i = 1;
            while (i < s.length() - 1) {
                achar = s.charAt(i);
                if (((achar >= 'A') && (achar <= 'Z')) || ((achar >= 'a') && (achar <= 'z')) || ((achar >= '0') && (achar <= '9'))) {
                    valid_id = false;
                }
                i++;
            }
        }
        if (valid_id && (s.length() >= 1) && (s.length() < 6))
            return true;
        else
            return false;
      }
}