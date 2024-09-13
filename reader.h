#ifndef READER_H
#define READER_H

#include <QString>

class Reader
{
public:
    int get_readerId();
    QString get_name();
    QString get_address();
    QString get_phone();
private:
    friend class ReaderBuilder;
    int readerId;
    QString name;
    QString address;
    QString phone;
};

#endif // READER_H
