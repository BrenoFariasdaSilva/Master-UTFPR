package edu.utfpr;

import net.jqwik.api.*;
import net.jqwik.api.constraints.*;

import static org.assertj.core.api.Assertions.*;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

public class IdentifierTest {

    Identifier identifier = new Identifier();

    @Property
    void validIdentifiers(@ForAll @AlphaChars @StringLength(min = 0, max = 5) String suffix) {
        // prefixa com uma letra, pois o primeiro caractere deve ser uma letra
        String id = "A" + suffix;
        // garante que o id tem no máximo 6 caracteres
        assumeTrue(id.length() <= 6);

        assertThat(identifier.validateIdentifier(id)).isTrue();
    }

    @Property
    void invalidLengthIdentifiers(@ForAll @StringLength(min = 7, max = 20) String id) {
        assertThat(identifier.validateIdentifier(id)).isFalse();
    }

    @Property
    void invalidCharacterIdentifiers(@ForAll @StringLength(min = 0, max = 5) String suffix) {
        // força um caractere inválido no início (não letra)
        String id = "1" + suffix;
        // garante que o id tem no máximo 6 caracteres
        assumeTrue(id.length() <= 6);

        assertThat(identifier.validateIdentifier(id)).isFalse();
    }
}
