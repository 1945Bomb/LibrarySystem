#ifndef READERBUILDER_H
#define READERBUILDER_H

#include "Reader.h"

class Reader;

class ReaderBuilder
{
    Reader reader;
public:
    ReaderBuilder& setReaderId(int id)
    {
        reader.readerId = id;
        return *this;
    }
    ReaderBuilder& setName(QString name)
    {
        reader.name = name;
        return *this;
    }
    ReaderBuilder& setAddress(QString address)
    {
        reader.address = address;
        return *this;
    }
    ReaderBuilder& setPhone(QString phone)
    {
        reader.phone = phone;
        return *this;
    }

    Reader build()
    {
        return reader;
    }
};

#endif // READERBUILDER_H
