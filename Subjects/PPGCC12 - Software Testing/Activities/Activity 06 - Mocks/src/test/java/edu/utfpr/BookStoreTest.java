package edu.utfpr.bookstore;

import org.junit.jupiter.api.Test;
import static org.mockito.Mockito.*;
import static org.assertj.core.api.Assertions.assertThat;

import java.util.HashMap;
import java.util.Map;

public class BookStoreTest {

   @Test
   void testComplexOrder() {
      BookRepository bookRepo = mock(BookRepository.class);
      BuyBookProcess process = mock(BuyBookProcess.class);

      Map<String, Integer> order = new HashMap<>();
      order.put("BOOK-1", 5);
      order.put("BOOK-2", 10);
      order.put("BOOK-3", 22);

      Book book1 = new Book("BOOK-1", 20.0, 11);
      Book book2 = new Book("BOOK-2", 25.0, 10);
      Book book3 = new Book("BOOK-3", 37.0, 21);

      when(bookRepo.findByISBN("BOOK-1")).thenReturn(book1);
      when(bookRepo.findByISBN("BOOK-2")).thenReturn(book2);
      when(bookRepo.findByISBN("BOOK-3")).thenReturn(book3);

      BookStore store = new BookStore(bookRepo, process);
      Overview overview = store.getPriceForCart(order);

      double expectedPrice = (5 * 20) + (10 * 25) + (21 * 37);

      assertThat(overview.getTotalPrice()).isEqualTo(expectedPrice);
      assertThat(overview.getUnavailable()).containsEntry(book3, 1);

      verify(process).buyBook(book1, 5);
      verify(process).buyBook(book2, 10);
      verify(process).buyBook(book3, 21);
   }
}
