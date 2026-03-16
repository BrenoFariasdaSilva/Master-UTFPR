package edu.utfpr.bookstore;

public interface BookRepository {
   Book findByISBN(String isbn);
}
