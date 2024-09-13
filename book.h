#ifndef BOOK_H
#define BOOK_H

#include <QString>

class Book
{
public:
    int get_bookId();
    QString get_author();
    QString get_title();
    QString get_year();
    bool get_isAvailable();
    QString get_Available();
    void set_isAvailable(bool available);
private:
    friend class BookBuilder;
    int bookId;
    QString author;
    QString title;
    QString year;
    bool isAvailable;
};

#endif // BOOK_H
