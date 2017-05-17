#include "booksmodel.h"

const int BooksModel::BName = Qt::UserRole + 1;
const int BooksModel::BAuthor = Qt::UserRole + 2;
const int BooksModel::BGenre = Qt::UserRole + 3;
const int BooksModel::BDate = Qt::UserRole + 4;

BooksModel::BooksModel(Lib::AvlTree<dKey, Book> &books,
                       Lib::AvlTree<tKey, Book> &booksD,
                       QObject *parent) :
    QAbstractListModel(parent), m_books(&books),
    m_booksD(&booksD)
{
    isReverse = false;
    shouldSbd = false;
}



QVariant BooksModel::data(const QModelIndex &index, int role) const
{
    // Check for errors.
    if (!index.isValid())
    {
        return QVariant();
    }
    int tSize = (shouldSbd ? m_booksD->size() : m_books->size());
    if (index.row() > (tSize - 1))
    {
        return QVariant();
    }

    // Get the right book.
    Book temp;

    if (shouldSbd)
    {
        temp = (isReverse ? Lib::at(m_booksD->rBegin(), m_booksD->rEnd(), index.row()).operator*() :
                            Lib::at(m_booksD->begin(), m_booksD->end(), index.row()).operator*());
    }
    else
    {
        temp = (isReverse ? *Lib::at(m_books->rBegin(), m_books->rEnd(), index.row()) :
                            *Lib::at(m_books->begin(), m_books->end(), index.row()));
    }

    // Get the right parameter.
    switch (role)
    {
    case Qt::DisplayRole:
    case BName:
    {
        QString name(temp.m_name.c_str());
        return QVariant::fromValue(name);
    }
    case BAuthor:
    {
        QString author(temp.m_author.c_str());
        return QVariant::fromValue(author);
    }
    case BGenre:
    {
        QString genre(temp.m_genre.c_str());
        return QVariant::fromValue(genre);
    }
    case BDate:
    {
        QString date(temp.m_date.getDate());
        return QVariant::fromValue(date);
    }
    default:
    {
        return QVariant();
    }
    }
}



int BooksModel::rowCount(const QModelIndex &parent) const
{
    return (shouldSbd ? m_booksD->size() : m_books->size());
}



QHash<int, QByteArray> BooksModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles.insert(BName, QByteArray("bName"));
    roles.insert(BAuthor, QByteArray("bAuthor"));
    roles.insert(BGenre, QByteArray("bGenre"));
    roles.insert(BDate, QByteArray("bDate"));

    return roles;
}



void BooksModel::changeModel(Lib::AvlTree<BooksModel::dKey, Book> *other)
{
    m_books = other;
    emit dataChanged(createIndex(0, 0), createIndex(m_books->size(), 0));
    emit layoutChanged();
}



void BooksModel::changeReverse()
{
    isReverse = (isReverse ? 0 : 1);
    emit dataChanged(createIndex(0, 0), createIndex(m_books->size(), 0));
    emit layoutChanged();
}



void BooksModel::changeSbd()
{
    shouldSbd = (shouldSbd ? 0 : 1);
    emit dataChanged(createIndex(0, 0), createIndex(m_books->size(), 0));
    emit layoutChanged();
}
