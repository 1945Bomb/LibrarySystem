#include "transaction.h"

int Transaction::get_bookId()
{
    return bookId;
}

int Transaction::get_readerId()
{
    return readerId;
}

QString Transaction::get_issueDate()
{
    return issueDate;
}

QString Transaction::get_returnDate()
{
    return returnDate;
}

void Transaction::set_returnDate(QString rtnDate)
{
    returnDate = rtnDate;
}
