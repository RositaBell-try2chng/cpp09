#include "BitcoinExchange.hpp"
#include "Date.hpp"

float findClosestDateVal(std::map<Date, float> &src, Date dt)
{
	std::map<Date, float>::iterator st = src.begin();
	if (dt < st->first)
		throw tooSmallDate();

	std::map<Date, float>::iterator en = --src.end();
	if (dt > en->first)
		return (en->second);

	std::map<Date, float>::iterator f = src.find(dt);
	while (f == src.end())
	{
		dt--;
		f = src.find(dt);
	}
	return (f->second);
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

static bool isInt(std::string &strVal)
{
	size_t	i;
	size_t	size = strVal.length();

	i = 0;
	if (i < size && (strVal[i] == '-' || strVal[i] == '+'))
		i++;
	while (i < size && std::isdigit(strVal[i]))
		i++;
	if (i != size)
		return false;
	return true;
}

static bool isFloat(std::string &strVal)
{
	size_t	i;
	size_t	size = strVal.length();
	size_t	tmpI;

	i = 0;
	if (i < size && (strVal[i] == '-' || strVal[i] == '+'))
		i++;
	while (i < size && std::isdigit(strVal[i]))
		i++;
	if (i < size && strVal[i] == '.')
		i++;
	while (i < size && std::isdigit(strVal[i]))
		i++;
	if (i < size && (strVal[i] == 'E' || strVal[i] == 'e'))
	{
		i++;
		if (i < size && (strVal[i] == '-' || strVal[i] == '+'))
			i++;
		tmpI = i;
		while (i < size && std::isdigit(strVal[i]))
			i++;
		if (i == tmpI)
			return false;
	}
	if (i != size)
		return false;
	return true;
}

void sepString(std::string &s, float &val, char del)
{
	ssize_t				ind = s.find(del);
	std::stringstream	sStream;
	std::string			strVal;

	if (ind < 0)
		throw NoDelimiterAtLine();
	ind++;
	strVal = s.substr(ind, s.length() - ind);
	if (!isInt(strVal) && !isFloat(strVal))
		throw invalidCharsInValue();
	sStream << strVal;
	sStream >> val;
	strVal.clear();
	sStream >> strVal;
	if (strVal.length() != 0)
		throw invalidCharsInValue();
	s = s.substr(0, ind - 1);
}

bool	readFile(std::ifstream &file, std::map<Date, float> &src, char del)
{
	std::string s;
	Date		dt;
	float		value;

	if (!file.is_open())
		return (false);
	std::getline(file, s);
	s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
	if ((del == ',' && s != DB_HAT) || (del == '|' && s != INPUT_HAT))
	{
		putError(s.append(" <= BAD HAT"));
		return (false);
	}
	while (std::getline(file, s))
	{
		try
		{
			s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
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

char const *invalidCharsInValue::what() const throw()
{
	return ("Exception: there are invalid chars in value");
}

char const* tooSmallDate::what() const throw()
{
	return ("Exception: Date is too early");
}