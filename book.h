
#ifndef _BOOK_
#define _BOOK_

#include "date.h"

struct Book
{
	std::string m_name;
	std::string m_author;
	std::string m_genre;
	Date m_date;

	Book() : m_name(), m_author(),
		m_genre(), m_date()
	{ }

	Book(const std::string& name, const std::string& author,
		const std::string& genre, const Date& date) :
		m_name(name), m_author(author),
		m_genre(genre), m_date(date)
	{ }

	Book(const Book& other) :
		m_name(other.m_name), m_author(other.m_author),
		m_genre(other.m_genre), m_date(other.m_date)
	{ }

	~Book()
	{ }

    bool operator==(const Book& other) const
    {
        return (m_name == other.m_name &&
                m_author == other.m_author &&
                m_genre == other.m_genre &&
                m_date == other.m_date);
    }
};

#endif // !_BOOK_

