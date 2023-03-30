#include "BitcoinExchange.hpp"
#include "Date.hpp"

static float findClosestDateValRec(std::map<Date, float> &src, Date dt, bool flgPlus, int &res)
{
	res++;
	std::map<Date, float>::iterator f = src.find(dt);
	if (f != src.end())
		return (f->second);
	if (flgPlus)
		return (findClosestDateValRec(src, dt++, true, res));
	return (findClosestDateValRec(src, dt--, false, res));
}

float findClosestDateVal(std::map<Date, float> &src, Date dt)
{
	int		minusRes = 0;
	int		plusRes = 0;
	float	minusFRes;
	float	plusFRes;

	std::map<Date, float>::iterator st = src.begin();
	if (dt < st->first)
		return (st->second);

	std::map<Date, float>::iterator en = --src.end();
	if (dt > en->first)
		return (en->second);

	std::map<Date, float>::iterator f = src.find(dt);
	if (f != src.end())
		return (f->second);
	minusFRes = findClosestDateValRec(src, dt--, false, minusRes);
	plusFRes = findClosestDateValRec(src, (dt++)++, true, plusRes);
	if (plusRes < minusRes)
		return (plusFRes);
	return (minusFRes);
}

void putError(std::string &str)
{
	std::cerr << str << std::endl;
}

int die(char flg, std::ifstream *fileName)
{
	std::string s;
	if (flg == 0)
		return (0);
	if (flg == 1)
		s = "Error: Can't read or open file with courses";
	else if (flg == 2)
		s = "Error: invalid number of args";
	else if (flg == 3)
		s = "Error: Can't read or open input file";
	putError(s);
	if (fileName)
		fileName->close();
	return (1);
}

void skipHat(std::ifstream &data)
{
	std::string s;
	std::getline(data, s);
}

void mathValue(Date &dt, float value, std::map<Date, float> &src)
{
	std::string str;
	float		k;

	if (value < 0.0)
	{
		str = "Error: not positive value";
		putError(str);
		return;
	}
	if (value > 1000.0)
	{
		str = "Error: too large value";
		putError(str);
		return;
	}
	k = findClosestDateVal(src, dt);
	std::cout << dt << " => " << value << " = " << k * value << std::endl;
}

void sepString(std::string &s, float &val, char del)
{
	ssize_t				ind = s.find(del);
	std::stringstream	sStream;
	char				skip;

	if (ind < 0)
		throw NoDelimiterAtLine();
	ind++;
	sStream << s.substr(ind, s.length() - ind);
	sStream >> val;
	if (sStream >> skip)
		throw charsAfterValue();
	s = s.substr(0, ind - 1);
	while (ISSPACE(s[s.length() - 1]))
		s = s.substr(0, s.length() - 1);
}

bool	readFile(std::ifstream &file, std::map<Date, float> &src, char del)
{
	std::string s;
	Date		dt;
	float		value;

	if (!file.is_open())
		return (false);
	skipHat(file);
	while (std::getline(file, s))
	{
		try
		{
			sepString(s, value, del);
			dt = Date(s);
			if (del == ',')
				src.insert(std::pair<Date, float>(dt, value));
			else
				mathValue(dt, value, src);
		}
		catch (std::exception &e)
		{
			std::string str;
			if (del == ',')
				str = "Error DB file: ";
			else
				str = "Error input file: ";
			str.append(e.what()).append(" => ").append(s);
			putError(str);
		}
	}
	return (true);
}

const char *NoDelimiterAtLine::what() const throw()
{
	return ("Exception: there is no delimiter at line");
}

char const *charsAfterValue::what() const throw()
{
	return ("Exception: there are one or more chars after value");
}