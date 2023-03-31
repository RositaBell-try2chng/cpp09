#include "RPN.hpp"

bool isSign(char c)
{
	return (c == PLUS || c == MINUS || c == MULTI || c == DIV);
}

int isCorrect(char c)
{
	if (std::isspace(c))
		return (1);
	if (std::isdigit(c))
		return (2);
	if (isSign(c))
		return (3);
	return (0);
}

void putError(std::string const &str)
{
	std::cout << str << std::endl;
}

const char *invalidInput::what() const throw()
{
	return ("Exception: Invalid string representation");
}

const char *divByZero::what() const throw()
{
	return ("Exception: div by zero");
}

void printStack(std::stack<int> st)
{
	std::cout << "============= start stack =============\n";
	while (!st.empty())
	{
		std::cout << st.top() << std::endl;
		st.pop();
	}
	std::cout << "============= end stack =============\n";
}