#include "RPN.hpp"

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

int main(int args, char **argv)
{
	std::stack<float> st;
	std::string		input;

	if (args != 2)
	{
		putError(std::string("Error: wrong numbers of args"));
		return (1);
	}
	input = argv[1];
	try {
		fillStack(input, st);
		std::cout << st.top() << std::endl;
	}
	catch (std::exception &e) {putError(std::string(e.what()));}
	return (0);
}