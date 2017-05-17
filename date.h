
#ifndef _DATE_TYPE_
#define _DATE_TYPE_

#include <string>
#include <QDebug>                   // REMOVE


struct StrDate
{
	bool isChanged;
	std::string strDate;

	StrDate() : isChanged(true), strDate()
	{ }
};


class Date
{
public:
	static const char delimiter = '/';

	enum Mounth
	{
		jan = 1, feb,
		mar, apr, may,
		jun, jul, aug,
		sep, oct, nov,
		dec
	};



	Date() : m_day(1), m_month(jan),
             m_year(1), m_strDate()
	{ }

	Date(const Date& date);

    Date(const char* date);

    Date(const std::string);

	~Date()
	{ }



	// Setter.
	void setDate(unsigned char, unsigned char, short);

	// Getters:
	const char* getDate() const;
	int getYear() const;
	int getMonth() const;
	int getDay() const;



	// Overload operators:
	bool operator==(const Date& other) const;
	bool operator!=(const Date& other) const;
	bool operator<(const Date& other) const;
	bool operator>(const Date& other) const;



private:
	void setYear(short);
	void setMonth(unsigned char);
	void setDay(unsigned char);

	void computeStrDate() const;


	// Data:
	unsigned char m_day;
	unsigned char m_month;
	short m_year;

	mutable StrDate m_strDate;
};

#endif // !_DATE_TYPE_

