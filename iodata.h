// IoData - Input output class.
// Read in text file List<Book>.
// Write in text gile List<Book>.
// Nothing more.


#ifndef IODATA_H
#define IODATA_H

#include <fstream>

#include "book.h"
#include "Lib/list.h"


class IoData
{
public:
    IoData();

    void read(const std::string& name, Lib::List<Book> *list);
    void write(const std::string& name, const Lib::List<Book> *bookList);
    Lib::List<Book>* getList() const;

private:
    Book convert(std::string &book) const;

    Lib::List<Book>* m_dataList;
};

#endif // IODATA_H
