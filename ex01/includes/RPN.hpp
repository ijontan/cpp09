#pragma once

#include <exception>
#include <stack>
#include <string>
class RPN
{
public:
	static float calculate(std::string str);

	class Error : public std::exception
	{
	private:
		std::string _str;

	public:
		Error(std::string str) : _str(str){};
		~Error() throw(){};
		const char *what() const throw()
		{
			return _str.c_str();
		}
	};
	static std::stack<float> _numberStack;

private:
};