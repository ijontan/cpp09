#include "PmergeMe.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <deque>
#include <list>
#include <utility>
#include <vector>

int PmergeMe::straggler = 0;
bool PmergeMe::is_odd = false;

int PmergeMe::jacobsthal(int n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return jacobsthal(n - 1) + 2 * jacobsthal(n - 2);
}
std::list<int> PmergeMe::buildInsertionSequence(int size)
{
	std::list<int> ret;
	int i = 3;
	int jacobsthal_number = jacobsthal(i);
	while (jacobsthal_number < size - 1)
	{
		ret.push_back(jacobsthal_number);
		jacobsthal_number = jacobsthal(++i);
	}
	return ret;
}

/* vector */

static int bisect(std::vector<int> &arr, int item, int low, int high)
{
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (arr[mid] == item)
			return mid;
		else if (arr[mid] < item)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return low;
}

std::vector<PmergeMe::PairInt> PmergeMe::createVectorPair(std::vector<int> &arr)
{
	std::vector<PairInt> ret(arr.size() / 2);
	std::vector<int>::iterator it = arr.begin();
	int i = 0;
	while (it != arr.end())
	{
		int first = *it;
		*it++ = 0;
		if (it == arr.end())
		{
			straggler = first;
			is_odd = true;
			return ret;
		}
		int second = *it;
		*it++ = 0;
		if (first < second)
			ret[i] = std::make_pair(first, second);
		else
			ret[i] = std::make_pair(second, first);
		i++;
	}

	return ret;
}

void PmergeMe::mergesortVectorPair(std::vector<PairInt> &arr)
{
	if (arr.size() <= 1)
		return;

	std::vector<PmergeMe::PairInt> left(arr.size() / 2);
	std::vector<PmergeMe::PairInt> right(arr.size() / 2 + (arr.size() % 2));
	for (size_t j = 0; j < arr.size() / 2; j++)
	{
		left[j] = arr[j];
		right[j] = arr[arr.size() / 2 + j];
	}
	if (arr.size() % 2 == 1)
		right[arr.size() / 2] = arr[arr.size() - 1];

	mergesortVectorPair(left);
	mergesortVectorPair(right);
	std::vector<PairInt>::iterator itl = left.begin();
	std::vector<PairInt>::iterator itr = right.begin();
	for (size_t i = 0; i < arr.size(); i++)
	{
		if (itl == left.end())
			arr[i] = *itr++;
		else if (itr == right.end())
			arr[i] = *itl++;
		else if (itl != left.end() && itr != right.end())
		{
			if (itl->first < itr->first)
				arr[i] = *itl++;
			else
				arr[i] = *itr++;
		}
		else
			break;
	}
}

void PmergeMe::mergeMPVector(std::vector<PairInt> &pairs, std::vector<int> &out)
{
	std::vector<int> main(pairs.size());
	std::vector<int> pend(pairs.size());
	for (size_t i = 0; i < pairs.size(); i++)
	{
		main[i] = pairs[i].first;
		pend[i] = pairs[i].second;
	}
	// main.push_back(pend[pend.size() - 1]);
	// pend.pop_back();
	size_t i = 0, j = 0;
	std::list<int> used;
	std::list<int> insert_sequsnce = buildInsertionSequence(pend.size());
	while (i < pend.size())
	{
		int item;
		int pend_index;
		if (insert_sequsnce.size() != 0)
		{
			pend_index = insert_sequsnce.front() - 1;
			item = pend[pend_index];
			used.push_back(insert_sequsnce.front());
			insert_sequsnce.pop_front();
		}
		else
		{
			j = 0;
			while (std::find(used.begin(), used.end(), j) != used.end())
				j++;
			pend_index = j;
			item = pend[pend_index];
			used.push_back(j);
		}
		int index_insert = bisect(main, item, pend_index, main.size() - 1);
		main.insert(main.begin() + index_insert, item);
		i++;
	}
	if (is_odd)
	{
		int index_insert = bisect(main, straggler, 0, main.size() - 1);
		main.insert(main.begin() + index_insert, straggler);
	}
	for (size_t j = 0; j < main.size(); j++)
		out[j] = main[j];
}

void PmergeMe::sortVector(std::vector<int> &arr)
{
	// create pairs and
	std::vector<PairInt> pairs = createVectorPair(arr);
	mergesortVectorPair(pairs);
	mergeMPVector(pairs, arr);
}

/* deque */
static int bisect(std::deque<int> &arr, int item, int low, int high)
{
	while (low <= high)
	{
		int mid = (low + high) / 2;
		if (arr[mid] == item)
			return mid;
		else if (arr[mid] < item)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return low;
}

std::deque<PmergeMe::PairInt> PmergeMe::createDequePair(std::deque<int> &arr)
{
	std::deque<PairInt> ret(arr.size() / 2);
	std::deque<int>::iterator it = arr.begin();
	int i = 0;
	while (it != arr.end())
	{
		int first = *it;
		*it++ = 0;
		if (it == arr.end())
		{
			straggler = first;
			is_odd = true;
			return ret;
		}
		int second = *it;
		*it++ = 0;
		if (first < second)
			ret[i] = std::make_pair(first, second);
		else
			ret[i] = std::make_pair(second, first);
		i++;
	}

	return ret;
}

void PmergeMe::mergesortDequePair(std::deque<PairInt> &arr)
{
	if (arr.size() <= 1)
		return;

	std::deque<PmergeMe::PairInt> left(arr.size() / 2);
	std::deque<PmergeMe::PairInt> right(arr.size() / 2 + (arr.size() % 2));
	for (size_t j = 0; j < arr.size() / 2; j++)
	{
		left[j] = arr[j];
		right[j] = arr[arr.size() / 2 + j];
	}
	if (arr.size() % 2 == 1)
		right[arr.size() / 2] = arr[arr.size() - 1];

	mergesortDequePair(left);
	mergesortDequePair(right);
	std::deque<PairInt>::iterator itl = left.begin();
	std::deque<PairInt>::iterator itr = right.begin();
	for (size_t i = 0; i < arr.size(); i++)
	{
		if (itl == left.end())
			arr[i] = *itr++;
		else if (itr == right.end())
			arr[i] = *itl++;
		else if (itl != left.end() && itr != right.end())
		{
			if (itl->first < itr->first)
				arr[i] = *itl++;
			else
				arr[i] = *itr++;
		}
		else
			break;
	}
}

void PmergeMe::mergeMPDeque(std::deque<PairInt> &pairs, std::deque<int> &out)
{
	std::deque<int> main(pairs.size());
	std::deque<int> pend(pairs.size());
	for (size_t i = 0; i < pairs.size(); i++)
	{
		main[i] = pairs[i].first;
		pend[i] = pairs[i].second;
	}
	// main.push_back(pend[pend.size() - 1]);
	// pend.pop_back();
	size_t i = 0, j = 0;
	std::list<int> used;
	std::list<int> insert_sequsnce = buildInsertionSequence(pend.size());
	while (i < pend.size())
	{
		int item;
		int pend_index;
		if (insert_sequsnce.size() != 0)
		{
			pend_index = insert_sequsnce.front() - 1;
			item = pend[pend_index];
			used.push_back(insert_sequsnce.front());
			insert_sequsnce.pop_front();
		}
		else
		{
			j = 0;
			while (std::find(used.begin(), used.end(), j) != used.end())
				j++;
			pend_index = j;
			item = pend[pend_index];
			used.push_back(j);
		}
		int index_insert = bisect(main, item, pend_index, main.size() - 1);
		main.insert(main.begin() + index_insert, item);
		i++;
	}
	if (is_odd)
	{
		int index_insert = bisect(main, straggler, 0, main.size() - 1);
		main.insert(main.begin() + index_insert, straggler);
	}
	for (size_t j = 0; j < main.size(); j++)
		out[j] = main[j];
}

void PmergeMe::sortDeque(std::deque<int> &arr)
{
	// create pairs and
	std::deque<PairInt> pairs = createDequePair(arr);
	mergesortDequePair(pairs);
	mergeMPDeque(pairs, arr);
}
