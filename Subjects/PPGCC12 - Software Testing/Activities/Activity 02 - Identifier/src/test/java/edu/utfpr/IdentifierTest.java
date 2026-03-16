package edu.utfpr;

import static org.junit.Assert.assertEquals;

import org.junit.jupiter.api.Test;

public class IdentifierTest {


    // @Test
    // public void testValidIdentifier() {
    //     Identifier identifier = new Identifier();
    //     assertEquals(true, identifier.validateIdentifier("abc123"));
    // }

    // @Test
    // public void testInvalidIdentifierStartingWithDigit() {
    //     Identifier identifier = new Identifier();
    //     assertEquals(false, identifier.validateIdentifier("1abc"));
    // }

    // @Test
    // public void testInvalidIdentifierWithSpecialCharacter() {
    //     Identifier identifier = new Identifier();
    //     assertEquals(false, identifier.validateIdentifier("abc@123"));
    // }

    // @Test
    // public void testInvalidIdentifierTooLong() {
    //     Identifier identifier = new Identifier();
    //     assertEquals(false, identifier.validateIdentifier("abcdefg"));
    // }

    // @Test
    // public void testValidIdentifierWithSingleCharacter() {
    //     Identifier identifier = new Identifier();
    //     assertEquals(true, identifier.validateIdentifier("a"));
    // }

    // @Test
    // public void testInvalidIdentifierEmptyString() {
    //     Identifier identifier = new Identifier();
    //     assertEquals(false, identifier.validateIdentifier(""));
    // }

    // @Test
    // public void testInvalidIdentifierWithSpace() {
    //     Identifier identifier = new Identifier();
    //     assertEquals(false, identifier.validateIdentifier("abc 123"));
    // }

    // @Test
    // public void testValidIdentifierWithMaxLength() {
    //     Identifier identifier = new Identifier();
    //     assertEquals(true, identifier.validateIdentifier("abcde"));
    // }

    @Test
    public void testEmptyString() {
        Identifier identifier = new Identifier();
        assertEquals(false, identifier.validateIdentifier("")); // Caso 1
    }

    @Test
    public void testSingleLetter() {
        Identifier identifier = new Identifier();
        assertEquals(true, identifier.validateIdentifier("a")); // Caso 2
    }

    @Test
    public void testValidIdentifierMaxLength() {
        Identifier identifier = new Identifier();
        assertEquals(true, identifier.validateIdentifier("abc123")); // Caso 3
    }

    @Test
    public void testIdentifierTooLong() {
        Identifier identifier = new Identifier();
        assertEquals(false, identifier.validateIdentifier("abcdefg")); // Caso 4
    }

    @Test
    public void testStartsWithDigit() {
        Identifier identifier = new Identifier();
        assertEquals(false, identifier.validateIdentifier("1abc")); // Caso 5
    }

    @Test
    public void testContainsSpace() {
        Identifier identifier = new Identifier();
        assertEquals(false, identifier.validateIdentifier("a b")); // Caso 6
    }

    @Test
    public void testContainsAtSymbol() {
        Identifier identifier = new Identifier();
        assertEquals(false, identifier.validateIdentifier("ab@1")); // Caso 7
    }

    @Test
    public void testValidIdentifierShort() {
        Identifier identifier = new Identifier();
        assertEquals(true, identifier.validateIdentifier("abc12")); // Caso 8
    }

    @Test
    public void testEndsWithExclamation() {
        Identifier identifier = new Identifier();
        assertEquals(false, identifier.validateIdentifier("ab1c!")); // Caso 9
    }

    @Test
    public void testMixedCaseWithDigit() {
        Identifier identifier = new Identifier();
        assertEquals(true, identifier.validateIdentifier("AbC9")); // Caso 10
    }

    public void testLongEmptyString() {
        Identifier identifier = new Identifier();
        assertEquals(false, identifier.validateIdentifier(" ")); // Caso 11
    }
}
