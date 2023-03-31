#include "PmergeMe.hpp"

void parseArgv(char **argv, int args, int *arr)
{
	std::string			str;
	int					val;
	char				skip;
	std::stringstream	sStream;

	for (int i = 0; i < args; i++)
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
}

int main(int args, char **argv)
{
	if (args < 2)
		return (putErr(std::string("Error: wrong number of args")));
	int *arr = new int[args - 1];
	try {
		parseArgv(++argv, args - 1, arr);
		//doItfor1(arr);
		//doItfor2(arr);
	}
	catch (std::exception &e) { putErr(std::string(e.what()));}
	delete [] arr;
	return (0);
}