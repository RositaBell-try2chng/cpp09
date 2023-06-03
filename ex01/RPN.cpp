#include "RPN.hpp"

bool isSign(char c)
{
	return (c == PLUS || c == MINUS || c == MULTI || c == DIV);
}


void putError(std::string const &str)
{
	std::cout << str << std::endl;
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

void mathVal(std::stack<float> &st, char c)
{
	float val1;
	float val2;

	if (st.size() < 2)
		throw invalidInput();
	val1 = st.top();
	st.pop();
	val2 = st.top();
	st.pop();
	switch (c)
	{
		case PLUS: {st.push(val2 + val1); break;}
		case MINUS: {st.push(val2 - val1); break;}
		case MULTI: {st.push(val2 * val1); break;}
		case DIV: {
			if (val1 == 0)
				throw divByZero();
			st.push(val2 / val1);
			break;
		}
	}
}


void fillStack(std::string &src, std::stack<float> &st)
{
	for (size_t i = 0; i < src.size(); i++)
	{
		switch (isCorrect(src[i]))
		{
			case 1: {break;}
			case 2:	{st.push(static_cast<float>(src[i] - 48)); break;}
			case 3: {mathVal(st, src[i]); break;}
			default: {throw invalidInput();}
		}
	}
	if (st.size() != 1)
		throw invalidInput();
}

//void printStack(std::stack<int> st)
//{
//	std::cout << "============= start stack =============\n";
//	while (!st.empty())
//	{
//		std::cout << st.top() << std::endl;
//		st.pop();
//	}
//	std::cout << "============= end stack =============\n";
//}

const char *invalidInput::what() const throw()
{
	return ("Exception: Invalid string representation");
}

const char *divByZero::what() const throw()
{
	return ("Exception: div by zero");
}