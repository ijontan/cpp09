#include "BitcoinExchange.hpp"
#include <iostream>
#include <ostream>

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr <<"Error: could not open file" << std::endl;
		return 1;
	}
	BitcoinExchange be;
	be.loadExchangeRate("./src/data.csv");
	string fname(av[1]);
	be.parse(fname);
	return 0;
}
