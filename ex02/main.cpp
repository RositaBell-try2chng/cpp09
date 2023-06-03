#include "PmergeMe.hpp"

int main(int args, char **argv)
{
	if (args < 2)
		return (putErr(std::string("Error: wrong number of args")));
	int *arr = new int[args - 1];
	try {
		parseArgv(++argv, args - 1, arr);
		doItFor1(arr, args - 1);
		std::cout << std::endl;
		doItFor2(arr, args - 1);
	}
	catch (std::exception &e) { putErr(std::string(e.what()));}
	delete [] arr;
	return (0);
}

void parseArgv(char **argv, int args, int *arr)
{
	std::string			str;
	int					val;
	char				skip;
	std::stringstream	sStream;
	int					i;

	for (i = 0; i < args; i++)
	{
		skip = 32;
		str = argv[i];
		sStream << str;
		sStream >> val;
		while (sStream >> skip && std::isspace(skip));
		if (!std::isspace(skip) || val <= 0)
			throw wrongArgs();
		arr[i] = val;
		sStream.clear();
	}
	std::cout << "Before:";
	for (i = 0; i < args && i < MAX_PRINT; i++)
		std::cout << " " << arr[i];
	if (i < args)
		std::cout << " [...]";
	std::cout << std::endl << std::endl;
}