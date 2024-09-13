#ifndef BOOKBUILDER_H
#define BOOKBUILDER_H

#include "Book.h"

class Book;

class BookBuilder {
    Book book;
public:
    BookBuilder& setBookId(int id) {
        book.bookId = id;
        return *this;
    }

    BookBuilder& setAuthor(const QString& author) {
        book.author = author;
        return *this;
    }

    BookBuilder& setTitle(const QString& title) {
        book.title = title;
        return *this;
    }

    BookBuilder& setYear(QString year) {
        book.year = year;
        return *this;
    }

    BookBuilder& setIsAvailable(bool isAvailable) {
        book.isAvailable = isAvailable;
        return *this;
    }

    Book build() {
        return book;
    }
};

#endif // BOOKBUILDER_H
