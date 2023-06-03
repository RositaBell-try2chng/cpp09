#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>

#define PLUS 43
#define MINUS 45
#define MULTI 42
#define DIV 47

class invalidInput : public std::exception
{
	char const *what() const throw();
};

class divByZero : public std::exception
{
	char const *what() const throw();
};

bool	isSign(char c);
void	putError(std::string const &str);
int		isCorrect(char c);
void	mathVal(std::stack<float> &st, char c);
void	fillStack(std::string &src, std::stack<float> &st);

//only for debug
//void	printStack(std::stack<int> st);

#endif