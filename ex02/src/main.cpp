

#include "PmergeMe.hpp"
#include <ctime>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

static int atoi(std::string s)
{
	std::stringstream ss(s);
	int ret;
	ss >> ret;
	return ret;
}

int main(int ac, char **av)
{
	clock_t c;
	if (ac < 2)
	{
		std::cerr << "Error: Input not enough" << std::endl;
		return 1;
	}
	std::vector<int> vecInt(ac - 1);
	std::deque<int> deqInt(ac - 1);
	std::cout << "before: ";
	for (int i = 1; i < ac; i++)
	{
		int value = atoi(av[i]);
		vecInt[i - 1] = value;
		deqInt[i - 1] = value;
		std::cout << vecInt[i - 1] << " ";
	}
	std::cout << std::endl;

	c = clock();
	PmergeMe::sortVector(vecInt);
	c = clock() - c;

	std::cout << "after: ";
	for (int i = 1; i < ac; i++)
		std::cout << vecInt[i - 1] << " ";
	std::cout << std::endl;
	std::cout << (float)c / CLOCKS_PER_SEC << std::endl;

	return 0;
}
