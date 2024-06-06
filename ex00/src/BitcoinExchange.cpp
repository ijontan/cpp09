#include "BitcoinExchange.hpp"
#include <cstddef>
#include <exception>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

/***********************************
 * Constructors
 ***********************************/

BitcoinExchange::BitcoinExchange(void)
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	*this = src;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
	this->_map = rhs._map;
	return *this;
}

/***********************************
 * Destructors
 ***********************************/

BitcoinExchange::~BitcoinExchange(void)
{
}

static std::pair<string, string> splitPair(string s, string del)
{
	size_t end = s.find(del);
	if (end == string::npos)
		throw BitcoinExchange::Error("Error: wrong format");
	return std::make_pair(s.substr(0, end), s.substr(end + del.length()));
}

// something like epoch time but didn't have precission to ms, since day is very
// sufficient also since this assumes all months have 31 days, so there will be
// "empty hole days" in for example 31th of feb these are wasted memory holes
static int toIntRepresent(int year, int month, int day)
{
	return ((year * 12) + month) * 31 + day;
}

static void validDay(int year, int month, int day)
{
	if (year < 2009 || year > 2024)
		throw BitcoinExchange::Error("Error: invalid year");
	if (month < 1 || month > 12)
		throw BitcoinExchange::Error("Error: invalid month");
	if ((day < 1 || day > 31) ||
		(day == 31 &&
		 (month == 4 || month == 6 || month == 9 || month == 11)) ||
		(month == 2 && (year % 4 == 0 ? day > 29 : day > 28)))
		throw BitcoinExchange::Error("Error: invalid day");
}

static int getDay(string date)
{
	int ymd[3] = {0}, i = 0;
	std::istringstream ss(date);
	string s;

	while (std::getline(ss, s, '-'))
	{
		if (i > 2)
			throw BitcoinExchange::Error("Error: invalid date");
		std::stringstream ss2(s);
		ss2 >> ymd[i++];
	}
	validDay(ymd[0], ymd[1], ymd[2]);
	return toIntRepresent(ymd[0], ymd[1], ymd[2]);
}

static double ft_stod(string str)
{
	std::stringstream ss(str);
	double value;
	ss >> value;
	return value;
}

static void validValue(double val)
{
	if (val > 1000 || val < 0)
		throw BitcoinExchange::Error("Error: value out of range");
}

void BitcoinExchange::parse(string fname)
{
	std::fstream data(fname.c_str());
	if (data.fail())
		throw Error("Error: missing txt file");
	string str;
	std::getline(data, str);
	while (std::getline(data, str))
	{
		try
		{
			if (str.length() == 0)
				continue;
			std::pair<string, string> vpair = splitPair(str, " | ");
			int dateInt = getDay(vpair.first);
			double value = ft_stod(vpair.second);
			validValue(value);
			map<int, double>::iterator it = _map.upper_bound(dateInt);
			if (it != _map.begin())
				it--;
			std::cout << vpair.first << " => " << value << " = "
					  << value * it->second << "\n";
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << " :: " << str << std::endl;
		}
	}
	std::cout << std::endl;
}

void BitcoinExchange::loadExchangeRate(string fname)
{
	std::fstream data(fname.c_str());
	if (data.fail())
		throw Error("Error: missing csv file");
	string str;
	std::getline(data, str);
	while (std::getline(data, str))
	{
		try
		{
			std::pair<string, string> vpair = splitPair(str, ",");
			std::pair<int, double> newPair =
				std::make_pair(getDay(vpair.first), ft_stod(vpair.second));
			if (_map.find(newPair.first) != _map.end())
				throw Error("Error: repeated value");
			_map.insert(newPair);
			// std::cout << "dateInt: " << newPair.first
			// 		  << ", value: " << newPair.second << "\n";
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl << str << std::endl;
		}
	}
	std::cout << std::endl;
}
