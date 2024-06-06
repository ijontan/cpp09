#pragma once

#include <deque>
#include <exception>
#include <list>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class PmergeMe
{
public:
	PmergeMe(void);
	~PmergeMe(void);
	PmergeMe(const PmergeMe &src);
	PmergeMe	&operator=(const PmergeMe &rhs);

	typedef std::pair<int, int> PairInt;
	static int jacobsthal(int n);
	static std::list<int> buildInsertionSequence(int size);
	static std::vector<PairInt> createVectorPair(std::vector<int> &arr);
	static std::deque<PairInt> createDequePair(std::deque<int> &arr);
	static void mergesortVectorPair(std::vector<PairInt> &arr);
	static void mergeMPVector(std::vector<PairInt> &pairs,
							  std::vector<int> &out);
	static void mergeMPDeque(std::deque<PairInt> &pairs,
							  std::deque<int> &out);
	static void mergesortDequePair(std::deque<PairInt> &arr);
	static void sortVector(std::vector<int> &arr);
	static void sortDeque(std::deque<int> &arr);

	class Error : public std::exception
	{
		Error(std::string info, std::string extraInfo)
		{
			static const std::string error("Error: ");
			std::stringstream ss;
			ss << error << info << extraInfo;
			ss >> _error;
		};
		~Error() throw(){};
		const char *what() const throw()
		{
			return _error.c_str();
		}

	private:
		std::string _error;
	};

private:
	static int straggler;
	static bool is_odd;
};
