#include "Date.hpp"

Date::Date() : year(1970), month(1), maxDaysForMonth(31), day(1) {}

Date::Date(Date const &oth) : year(oth.getYear()), month(oth.getMonth()), day(oth.getDay())
{
	this->maxDaysForMonth = oth.maxDaysForMonth;
}

Date::~Date() {}

Date &Date::operator=(Date const &oth)
{
	this->year = oth.getYear();
	this->month = oth.getMonth();
	this->day = oth.getDay();
	this->setMaxDays(this->year % 4, this->month);
	return (*this);
}

Date::Date(int _year, int _month, int _day)
{
	this->setMaxDays(_year % 4, _month);
	if (_year > 9999 || _year < 1970 || _day < 1 || _day > this->maxDaysForMonth || _month < 1 || _month > 12)
		throw Date::DateOutOfRange();
	this->year = _year;
	this->month = _month;
	this->day = _day;
}

bool Date::isDelimeter(char skip)
{
	if (skip == '-')
		return (true);
	return (false);
}

Date::Date(std::string &str)
{
	int					date[3];
	std::stringstream	strStream;
	char				skip;
	int					i;

	i = 0;
	strStream << str;
	while (strStream >> date[i] && strStream >> skip)
	{
		if (!isDelimeter(skip))
			throw Date::invalidStringDate();
		i++;
	}
	if (i != 2)
		throw Date::invalidStringDate();
	*this = Date(date[0], date[1], date[2]);
}

void Date::setMaxDays(int visFlg, int _month)
{
	int cond;

	cond = static_cast<int> ((_month <= 7 && _month % 2 == 1) || (_month > 7 && _month % 2 == 0));
	switch (cond)
	{
		case 1: {this->maxDaysForMonth = 31; break;}
		case 0: {this->maxDaysForMonth = 30; changeIfFebr(visFlg, _month); break;}
	}
}

void Date::changeIfFebr(int visFlg, int _month)
{
	if (_month != 2)
		return;
	this->maxDaysForMonth = 28;
	if (visFlg == 0)
		this->maxDaysForMonth++;
}

int Date::getDay() const {return this->day;}
int Date::getMonth() const {return this->month;}
int Date::getYear() const {return this->year;}

bool Date::operator==(const Date &oth) const
{
	return (this->getDay() == oth.getDay() && this->getMonth() == oth.getMonth() && this->getYear() == oth.getYear());
}

bool Date::operator<(const Date &oth) const
{
	if (this->getYear() < oth.getYear())
		return (true);
	if (this->getYear() == oth.getYear() && this->getMonth() < oth.getMonth())
		return (true);
	if (this->getYear() == oth.getYear() && this->getMonth() == oth.getMonth() && this->getDay() < oth.getDay())
		return (true);
	return (false);
}

bool Date::operator>(const Date &oth) const
{
	if (*this < oth || *this == oth)
		return (false);
	return (true);
}

bool Date::operator<=(const Date &oth) const
{
	return (*this < oth || *this == oth);
}

bool Date::operator>=(const Date &oth) const
{
	return (*this > oth || *this == oth);
}

Date &Date::operator++(int)
{
	Date maxDate(9999, 12, 31);

	if (*this == maxDate)
		throw Date::DateOutOfRange();
	if (this->getDay() < this->maxDaysForMonth)
	{
		this->day++;
		return (*this);
	}
	if (this->getMonth() < 12)
	{
		this->month++;
		this->day = 1;
	}
	else
	{
		this->year++;
		this->month = 1;
		this->day = 1;
	}
	this->setMaxDays(this->year % 4, this->month);
	return (*this);
}

Date &Date::operator--(int)
{
	Date minDate(1970, 1, 1);
	if (*this == minDate)
		throw Date::DateOutOfRange();
	if (this->day > 1)
	{
		this->day--;
		return *this;
	}
	if (this->month > 1)
	{
		this->month--;
		this->setMaxDays(this->year % 4, this->month);
		this->day = this->maxDaysForMonth;
		return *this;
	}
	this->year--;
	this->month = 12;
	this->day = 31;
	this->maxDaysForMonth = 31;
	return *this;
}

const char *Date::DateOutOfRange::what() const throw()
{
	return ("Date out of range exception!");
}

const char *Date::invalidStringDate::what() const throw()
{
	return ("Invalid string representation of date exception");
}

std::ostream &operator<<(std::ostream &out, const Date &dt)
{
	out << dt.getYear() << "-";
	if (dt.getMonth() / 10 < 1)
		out << "0";
	out << dt.getMonth() << "-";
	if (dt.getDay() / 10 < 1)
		out << "0";
	out << dt.getDay();
	return (out);
}