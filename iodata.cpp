#include "iodata.h"

IoData::IoData()
{
    m_dataList = new Lib::List<Book>();
}



void IoData::read(const std::string& name, Lib::List<Book>* list)
{
    std::string bookStr;
    std::ifstream dataFile;
    list->clear();

    dataFile.open(name);
    if (dataFile.is_open())
    {
        while (std::getline(dataFile, bookStr))
        {
            Book temp = convert(bookStr);
            list->push_back(temp);
        }
        dataFile.close();
    }
}



void IoData::write(const std::string& name,
                   const Lib::List<Book>* bookList)
{
    m_dataList = const_cast< Lib::List<Book>* >(bookList);
    std::ofstream dataFile;

    dataFile.open(name);

    if (dataFile.is_open())
    {
        for (auto iter = m_dataList->cBegin();
             iter != m_dataList->cEnd(); ++iter)
        {
            dataFile << iter.operator *().m_name.c_str() << ';';
            dataFile << iter.operator *().m_author.c_str() << ';';
            dataFile << iter.operator *().m_genre.c_str() << ';';
            dataFile << iter.operator *().m_date.getDate() << "\n";
        }
        dataFile.close();
    }
}



Lib::List<Book>* IoData::getList() const
{
    return m_dataList;
}



Book IoData::convert(std::string& book) const
{
    Book temp;
    std::string date;
    int positionBegin = 0;
    int positionEnd = 0;
    int len = 0;

    positionEnd = book.find(';');
    len = positionEnd - positionBegin;
    temp.m_name = book.substr(positionBegin, len);

    positionBegin = positionEnd + 1;
    positionEnd = book.find(';', positionBegin);
    len = positionEnd - positionBegin;
    temp.m_author = book.substr(positionBegin, len);

    positionBegin = positionEnd + 1;
    positionEnd = book.find(';', positionBegin);
    len = positionEnd - positionBegin;
    temp.m_genre = book.substr(positionBegin, len);

    positionBegin = positionEnd + 1;
    positionEnd = book.length();
    len = positionEnd - positionBegin;
    date = book.substr(positionBegin, len);
    Date tDate(date.c_str());
    temp.m_date = Date(tDate);

    return temp;
}











