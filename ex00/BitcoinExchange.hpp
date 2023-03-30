#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#define COURSES "./data.csv"

# include <iostream>
# include <string>
# include <map>
# include <fstream>
# include <sstream>

# define ISSPACE(c) ((c > 7 && c < 14) || c == 32) ? true : false

class Date;

class NoDelimiterAtLine : public std::exception
{
	char const *what() const throw();
};

class charsAfterValue : public std::exception
{
	char const *what() const throw();
};

//find
float	findClosestDateVal(std::map<Date, float> &src, Date dt);
void	putError(std::string &str);
int		die(char flg, std::ifstream *fileName);
void	skipHat(std::ifstream &data);
void	mathValue(Date &dt, float value, std::map<Date, float> &src);
void	sepString(std::string &s, float &val, char del);
//parse
bool	readFile(std::ifstream &file, std::map<Date, float> &src, char del);
#endif