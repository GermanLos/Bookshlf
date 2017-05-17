#include "bookshelf.h"

Bookshelf::Bookshelf(QObject *parent) :
    QObject(parent), m_sortByName(),
    m_sortByDate(), m_sortByAuthor(),
    m_sortByGenre()
{
    model = new BooksModel(m_sortByName, m_sortByDate);
    currentSort = &m_sortByName;
}



void Bookshelf::clearAll()
{
    m_bookList.clear();
    m_sortByName.clear();
    m_sortByAuthor.clear();
    m_sortByGenre.clear();
    m_sortByDate.clear();

    model->changeModel(currentSort);
}



void Bookshelf::save(QString path) const
{
    IoData file;
    file.write(path.toStdString().substr(8), &m_bookList);
    qDebug() << path.toStdString().substr(8).c_str();
}



void Bookshelf::load(QString path)
{
    IoData file;
    file.read(path.toStdString().substr(8), &m_bookList);
    m_sortByName.clear();
    m_sortByAuthor.clear();
    m_sortByGenre.clear();
    m_sortByDate.clear();

    for (auto iter = m_bookList.begin();
         iter != m_bookList.end(); ++iter)
    {
        m_sortByName.insert(dKey((*iter).m_name, (*iter).m_author), *iter);
        m_sortByAuthor.insert(dKey((*iter).m_author, (*iter).m_name), *iter);
        m_sortByGenre.insert(dKey((*iter).m_genre, (*iter).m_name), *iter);
        m_sortByDate.insert(tKey((*iter).m_date, (*iter).m_name, (*iter).m_author), *iter);
    }

    model->changeModel(currentSort);
}



void Bookshelf::addBookFromQml(QString name, QString author,
                        QString genre, QString date)
{
    addBook(name.toStdString(), author.toStdString(),
            genre.toStdString(), date.toStdString());
}



void Bookshelf::addBook(std::string name, std::string author,
                        std::string genre, std::string date)
{
    Date temp(date.c_str());
    Book book(name, author, genre, temp);

    m_bookList.push_back(book);
    m_sortByName.insert(dKey(name, author), book);
    m_sortByAuthor.insert(dKey(author, name), book);
    m_sortByGenre.insert(dKey(genre, name), book);
    m_sortByDate.insert(tKey(temp, name, author), book);

    model->changeModel(currentSort);
}



void Bookshelf::removeBook(int index)
{
    Book book(*Lib::at(currentSort->begin(), currentSort->end(), index));

    m_sortByName.remove(dKey(book.m_name, book.m_author));
    m_sortByAuthor.remove(dKey(book.m_author, book.m_name));
    m_sortByGenre.remove(dKey(book.m_genre, book.m_name));
    m_sortByDate.remove(tKey(book.m_date, book.m_name, book.m_author));

    for (auto iter = m_bookList.begin(); iter != m_bookList.end(); ++iter)
    {
        if (*iter == book)
        {
            m_bookList.remove(iter);
        }
    }

    model->changeModel(currentSort);
}



void Bookshelf::changeSortType(int type)
{
    qDebug() << "sorted by " << type;
    if (type == 3)
    {
        model->changeSbd();
        return;
    }
    else if(type == 4)
    {
        if (model->shouldSbd)
        {
            model->changeSbd();
        }
        model->changeReverse();
        return;
    }

    switch(type)
    {
    case 0:
    {
        if (model->shouldSbd)
        {
            model->changeSbd();
        }
        currentSort = &m_sortByName;
        break;
    }
    case 1:
    {
        if (model->shouldSbd)
        {
            model->changeSbd();
        }
        currentSort = &m_sortByAuthor;
        break;
    }
    case 2:
    {
        if (model->shouldSbd)
        {
            model->changeSbd();
        }
        currentSort = &m_sortByGenre;
        break;
    }
    }

    model->changeModel(currentSort);
}
