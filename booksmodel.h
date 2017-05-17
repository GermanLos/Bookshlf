#ifndef BOOKSMODEL_H
#define BOOKSMODEL_H

#include <QObject>
#include <QModelIndex>

#include "Lib/avltree.h"
#include "Lib/triplecompoundkey.h"
#include "Lib/libalgorithm.h"
#include "book.h"

class BooksModel : public QAbstractListModel
{
    Q_OBJECT
public:
    typedef Lib::CompoundKey<std::string, std::string> dKey;
    typedef Lib::TripleCompoundKey<Date, std::string, std::string> tKey;

    explicit BooksModel(Lib::AvlTree<dKey, Book>& books,
                        Lib::AvlTree<tKey, Book>& booksD,
                        QObject *parent = 0);

    QVariant data(const QModelIndex &index,
                  int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent =
                 QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;

    void changeModel(Lib::AvlTree<dKey, Book>* other);
    void changeReverse();
    void changeSbd();

private:
    Q_DISABLE_COPY(BooksModel)

    // Other sorts.
    Lib::AvlTree<dKey, Book> *m_books;

    // Sorted by date.
    Lib::AvlTree<tKey, Book> *m_booksD;

    // Variables for sorting.
    bool isReverse;
    bool shouldSbd;         // Should sort by date.

    // For access from qml.
    static const int BName;
    static const int BAuthor;
    static const int BGenre;
    static const int BDate;

    friend class Bookshelf;
};

#endif // BOOKSMODEL_H
