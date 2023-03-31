#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <list>
#include <vector>
#include <sstream>

int putErr(std::string const &str);

class wrongArgs : public std::exception
{
	char const *what() const throw();
};

#endif