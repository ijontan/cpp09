#pragma once

#include <exception>
#include <map>
#include <string>

using std::map;
using std::string;
class BitcoinExchange
{
public:
	BitcoinExchange(void);
	~BitcoinExchange(void);
	BitcoinExchange(const BitcoinExchange &src);
	BitcoinExchange &operator=(const BitcoinExchange &rhs);

	void parse(string fname);
	void loadExchangeRate(string fname);

	class Error : public std::exception
	{
	private:
		string _msg;

	public:
		Error(string msg) : _msg(msg)
		{
		}
		~Error() throw(){};
		const char *what() const throw()
		{
			return _msg.c_str();
		}
	};
private:
	map<int, double> _map;
};


