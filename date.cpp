#include "date.h"



Date::Date(const Date& date)
{
	setYear(date.m_year);
	setMonth(date.m_month);
    setDay(date.m_day);
}



Date::Date(const char* date)
{
	std::string temp(date);
	unsigned char day = 0,
		          month = 0;
	short year = 0;
	int positionBegin = 0,
		positionEnd = 0,
		len = 0;

	positionEnd = temp.find(delimiter);
	len = positionEnd - positionBegin;
	day = atoi(temp.substr(positionBegin, len).c_str());

	positionBegin = positionEnd + 1;
	positionEnd = temp.find(delimiter, positionBegin);
	len = positionEnd - positionBegin;
	month = atoi(temp.substr(positionBegin, len).c_str());

	positionBegin = positionEnd + 1;
	positionEnd = temp.length();
	len = positionEnd - positionBegin;
	year = atoi(temp.substr(positionBegin, len).c_str());

	setYear(year);
	setMonth(month);
	setDay(day);
}



Date::Date(const std::string date)
{
    Date(date.c_str());
}

void Date::setDate(unsigned char day, unsigned char month, short year)
{
	setYear(year);
	setMonth(month);
	setDay(day);
}



const char* Date::getDate() const
{
	if (m_strDate.isChanged)
	{
		computeStrDate();
	}

	return m_strDate.strDate.c_str();
}



int Date::getYear() const
{
	return static_cast<int>(m_year);
}



int Date::getMonth() const
{
	return static_cast<int>(m_month);
}



int Date::getDay() const
{
	return static_cast<int>(m_day);
}



bool Date::operator==(const Date & other) const
{
	return (m_year == other.m_year &&
			m_month == other.m_month &&
			m_day == other.m_day);
}



bool Date::operator!=(const Date & other) const
{
	return !(this->operator==(other));
}



bool Date::operator<(const Date & other) const
{
	if (m_year != other.m_year)
	{
		return (m_year < other.m_year ? true : false);
	}
	else //if m_year == other.m_year
	{
		if (m_month != other.m_month)
		{
			return (m_month < other.m_month ? true : false);
		}
		else
		{
			return (m_day < other.m_day);
		}
	}
}



bool Date::operator>(const Date & other) const
{
	if (m_year != other.m_year)
	{
		return (m_year > other.m_year ? true : false);
	}
	else //if m_year == other.m_year
	{
		if (m_month != other.m_month)
		{
			return (m_month > other.m_month ? true : false);
		}
		else
		{
			return (m_day > other.m_day);
		}
	}
}



void Date::setYear(short year)
{
	m_year = year;
    m_strDate.isChanged = true;
}



void Date::setMonth(unsigned char month)
{
	if (month >= 1 && month <= 12)
	{
		m_month = month;
	}
	else
	{
		m_month = (month < 1 ? 1 : 12);
	}
    m_strDate.isChanged = true;
}



void Date::setDay(unsigned char day)
{
	int max;
	switch (m_month)
	{
	case apr: case jun: case sep: case nov:
		max = 30;
		break;
	case jan: case mar: case may: case jul:
	case aug: case oct: case dec:
		max = 31;
		break;
	case feb:
		max = 28 + (m_year % 4 ? 0 : 1);
		break;
	default:
		max = 28;
	}

	m_day = (day < 1 ? 1 : (day > max ? max : day));
    m_strDate.isChanged = true;
}



void Date::computeStrDate() const
{
	char buffer[5];
	m_strDate.strDate.clear();

	m_strDate.strDate += itoa(m_day, buffer, 10);
	m_strDate.strDate.push_back(delimiter);
	m_strDate.strDate += itoa(m_month, buffer, 10);
	m_strDate.strDate.push_back(delimiter);
	m_strDate.strDate += itoa(m_year, buffer, 10);

	m_strDate.isChanged = false;
}
