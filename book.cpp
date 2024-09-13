#include "book.h"

int Book::get_bookId()
{
    return bookId;
}

QString Book::get_author()
{
    return author;
}

QString Book::get_title()
{
    return title;
}

QString Book::get_year()
{
    return year;
}

QString Book::get_Available()
{
    if(isAvailable)
    {
        return "В наличии";
    }
    else
    {
        return "Выдана";
    }
}

bool Book::get_isAvailable()
{
    return isAvailable;
}

void Book::set_isAvailable(bool available)
{
    isAvailable = available;
}
