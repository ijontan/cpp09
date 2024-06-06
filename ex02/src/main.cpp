

#include "PmergeMe.hpp"
#include <ctime>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

static int ft_atoi(std::string s)
{
	std::stringstream ss(s);
	int ret;
	ss >> ret;
	return ret;
}

int main(int ac, char **av)
{
	clock_t c;
	clock_t r1;
	clock_t r2;
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
		int value = ft_atoi(av[i]);
		vecInt[i - 1] = value;
		deqInt[i - 1] = value;
		std::cout << vecInt[i - 1] << " ";
	}
	std::cout << std::endl;

	c = clock();
	PmergeMe::sortVector(vecInt);
	r1 = clock() - c;
	c = clock();
	PmergeMe::sortDeque(deqInt);
	r2 = clock() - c;

	std::cout << "after: ";
	for (int i = 1; i < ac; i++)
		std::cout << vecInt[i - 1] << " ";
	std::cout << std::endl;

	std::cout << "time taken for std::vector: "
			  << (float)r1 / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;
	std::cout << "time taken for std::deque: "
			  << (float)r2 / CLOCKS_PER_SEC * 1000 << "ms" << std::endl;

	return 0;
}
