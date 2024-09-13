#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>

class Transaction
{
public:
    int get_readerId();
    int get_bookId();
    QString get_issueDate();
    QString get_returnDate();
    void set_returnDate(QString rtnDate);
private:
    friend class TransactionBuilder;
    int readerId;
    int bookId;
    QString issueDate;
    QString returnDate;
};

#endif // TRANSACTION_H
