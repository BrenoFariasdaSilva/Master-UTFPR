package edu.utfpr.bookstore;

import org.junit.jupiter.api.Test;
import java.time.LocalDate;
import java.time.Month;

import static org.mockito.Mockito.*;
import static org.assertj.core.api.Assertions.assertThat;
import static org.assertj.core.api.Assertions.offset;

public class ChristmasDiscountTest {

   private final Clock clock = mock(Clock.class);
   private final ChristmasDiscount discount = new ChristmasDiscount(clock);

   @Test
   void shouldApplyDiscountOnChristmas() {
      LocalDate christmas = LocalDate.of(2025, Month.DECEMBER, 25);
      when(clock.now()).thenReturn(christmas);

      double result = discount.applyDiscount(100.0);

      assertThat(result).isCloseTo(85.0, offset(0.001));
   }

   @Test
   void shouldNotApplyDiscountOnOtherDays() {
      LocalDate notChristmas = LocalDate.of(2025, Month.DECEMBER, 26);
      when(clock.now()).thenReturn(notChristmas);

      double result = discount.applyDiscount(100.0);

      assertThat(result).isCloseTo(100.0, offset(0.001));
   }
}
