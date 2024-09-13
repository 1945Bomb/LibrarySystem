    #ifndef TRANSACTIONBUILDER_H
    #define TRANSACTIONBUILDER_H

    #include "transaction.h"

    class Transaction;

    class TransactionBuilder
    {
        Transaction transaction;
    public:
        TransactionBuilder& setReaderId(int readerId)
        {
            transaction.readerId = readerId;
            return *this;
        }
        TransactionBuilder& setBookId(int bookId)
        {
            transaction.bookId = bookId;
            return *this;
        }
        TransactionBuilder& setIssueDate(QString issueDate)
        {
            transaction.issueDate = issueDate;
            return *this;
        }
        TransactionBuilder& setReturnDate(QString returnDate)
        {
            transaction.returnDate = returnDate;
            return *this;
        }

        Transaction build()
        {
            return transaction;
        }
    };

    #endif // TRANSACTIONBUILDER_H
