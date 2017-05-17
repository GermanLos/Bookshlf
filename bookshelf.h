#ifndef BOOKSHELF_H
#define BOOKSHELF_H

#include <QObject>

#include "booksmodel.h"
#include "Lib/libalgorithm.h"
#include "iodata.h"

class Bookshelf : public QObject
{
    Q_OBJECT
public:
    typedef Lib::CompoundKey<std::string, std::string> dKey;
    typedef Lib::TripleCompoundKey<Date, std::string, std::string> tKey;

    explicit Bookshelf(QObject *parent = 0);



    // Data.
    BooksModel* model;

signals:

public slots:

    // File.
    void clearAll();
    void save(QString path) const;
    void load(QString path);

    // Book.
    void addBookFromQml(QString, QString, QString, QString);
    void removeBook(int index);

    // Sort.
    void changeSortType(int type);

private:
    void addBook(std::string, std::string, std::string, std::string);



    // Data.
    Lib::List<Book> m_bookList;
    Lib::AvlTree<dKey, Book> m_sortByName;
    Lib::AvlTree<dKey, Book> m_sortByAuthor;
    Lib::AvlTree<dKey, Book> m_sortByGenre;
    Lib::AvlTree<tKey, Book> m_sortByDate;

    Lib::AvlTree<dKey, Book>* currentSort;
};

#endif // BOOKSHELF_H
