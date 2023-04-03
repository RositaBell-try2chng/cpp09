#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#define COURSES "./data.csv"

# include <iostream>
# include <string>
# include <map>
# include <fstream>
# include <sstream>

# define DB_HAT "date,exchange_rate"
# define INPUT_HAT "date|value"

class Date;

class NoDelimiterAtLine : public std::exception
{
	char const *what() const throw();
};

class invalidCharsInValue : public std::exception
{
	char const *what() const throw();
};

float	findClosestDateVal(std::map<Date, float> &src, Date dt);
void	putError(std::string &str);
int		die(char flg, std::ifstream *fileName);
void	mathValue(Date &dt, float value, std::map<Date, float> &src);
void	sepString(std::string &s, float &val, char del);
bool	readFile(std::ifstream &file, std::map<Date, float> &src, char del);
#endif