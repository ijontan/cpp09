#include "RPN.hpp"
#include <exception>
#include <iostream>
#include <ostream>
int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Error: wrong amount of args" << std::endl;
		return 1;
	}
	try
	{
		std::cout << RPN::calculate(av[1]) << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
