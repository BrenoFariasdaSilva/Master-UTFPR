package edu.utfpr.bookstore;

import java.util.HashMap;
import java.util.Map;

public class Overview {
   private double totalPrice = 0.0;
   private final Map<Book, Integer> unavailable = new HashMap<>();

   public void addToTotalPrice(double value) {
      totalPrice += value;
   }

   public void addUnavailable(Book book, int missingQuantity) {
      unavailable.put(book, missingQuantity);
   }

   public double getTotalPrice() {
      return totalPrice;
   }

   public Map<Book, Integer> getUnavailable() {
      return unavailable;
   }
}
