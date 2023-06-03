#include "PmergeMe.hpp"

double getTime()
{
	struct timeval ts;
	double s;
	double us;

	try
	{
		if (gettimeofday(&ts, NULL) < 0)
			throw getTimeFail();
		s = ts.tv_sec;
		us = ts.tv_usec;
		return (s * 1000 + us / 1000);
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		return (0);
	}
}

int putErr(std::string const &str)
{
	std::cout << str << std::endl;
	return (1);
}

char const *wrongArgs::what() const throw()
{
	return ("Exception: wrong number in input");
}

char const* getTimeFail::what() const throw()
{
	return ("Exception: getTime failed");
}