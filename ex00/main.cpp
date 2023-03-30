#include "BitcoinExchange.hpp"
#include "Date.hpp"

int main(int args, char **argv)
{
	if (args != 2)
		return (die(2, NULL));

	//parse DB
	std::ifstream			file("./data.csv");
	std::map<Date, float>	src;
	if (!readFile(file, src, ','))
		return (die(1, &file));
	file.close();

	//parse and execute input
	std::ifstream	input(argv[1]);
	if (!readFile(input, src, '|'))
		return (die(3, &input));
	input.close();
	return (0);
}