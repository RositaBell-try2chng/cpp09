#include "RPN.hpp"

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