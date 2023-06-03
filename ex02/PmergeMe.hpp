#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <list>
#include <vector>
#include <sstream>
#include <sys/time.h>
#include <iterator>

#define MAX_PRINT 20
#define INSERT_BORDER 255

double	getTime();
int		putErr(std::string const &str);
void	parseArgv(char **argv, int args, int *arr);
void	doItFor1(int arr[], size_t size);
void	doItFor2(int arr[], size_t size);

class wrongArgs : public std::exception
{
	char const *what() const throw();
};

class getTimeFail : public std::exception
{
	char const *what() const throw();
};

#include "PmergeMe.tpp"

#endif