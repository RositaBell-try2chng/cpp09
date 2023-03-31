#include "PmergeMe.hpp"

char const *wrongArgs::what() const throw()
{
	return ("Exception: wrong number in input");
};

int putErr(std::string const &str)
{
	std::cout << str << std::endl;
	return (1);
}