package edu.utfpr.bookstore;

public class Book {
   private final String isbn;
   private final double price;
   private final int amount;

   public Book(String isbn, double price, int amount) {
      this.isbn = isbn;
      this.price = price;
      this.amount = amount;
   }

   public String getIsbn() {
      return isbn;
   }

   public double getPrice() {
      return price;
   }

   public int getAmount() {
      return amount;
   }
}
