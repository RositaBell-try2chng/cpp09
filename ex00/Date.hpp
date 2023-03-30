#ifndef DATE_HPP
#define DATE_HPP

#include "BitcoinExchange.hpp"

class Date
{
private:
	int year;
	int month;
	int maxDaysForMonth;
	int day;

	void	setMaxDays(int visFlg, int _month);
	void	changeIfFebr(int visFlg, int _month);
	bool	isDelimeter(char skip);
public:
	Date();
	Date(Date const &oth);
	Date(int _year, int _month, int _day);
	Date(std::string &str);
	~Date();

	int		getYear() const;
	int		getMonth() const;
	int		getDay() const;

	Date &operator--(int);
	Date &operator++(int);
	Date &operator=(Date const &oth);

	bool operator==(Date const &oth) const;
	bool operator>(Date const &oth) const;
	bool operator<(Date const &oth) const;
	bool operator>=(Date const &oth) const;
	bool operator<=(Date const &oth) const;

	class DateOutOfRange : public std::exception
	{
		char const *what() const throw();
	};
	class invalidStringDate : public std::exception
	{
		char const *what() const throw();
	};
};

std::ostream &operator<<(std::ostream &out, Date const &dt);
#endif