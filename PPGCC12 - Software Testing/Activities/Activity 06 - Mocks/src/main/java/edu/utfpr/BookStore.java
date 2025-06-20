package edu.utfpr.bookstore;

import java.util.Map;

public class BookStore {
   private final BookRepository bookRepository;
   private final BuyBookProcess process;

   public BookStore(BookRepository bookRepository, BuyBookProcess process) {
      this.bookRepository = bookRepository;
      this.process = process;
   }

   private void retrieveBook(String isbn, int amount, Overview overview) {
      Book book = bookRepository.findByISBN(isbn);

      if (book.getAmount() < amount) {
         overview.addUnavailable(book, amount - book.getAmount());
         amount = book.getAmount();
      }

      overview.addToTotalPrice(amount * book.getPrice());
      process.buyBook(book, amount);
   }

   public Overview getPriceForCart(Map<String, Integer> order) {
      if (order == null) return null;

      Overview overview = new Overview();

      for (String isbn : order.keySet()) {
         retrieveBook(isbn, order.get(isbn), overview);
      }

      return overview;
   }
}
