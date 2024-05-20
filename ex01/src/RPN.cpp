#include "RPN.hpp"
#include <cstdio>
#include <sstream>
#include <stack>
#include <string>

std::stack<float> RPN::_numberStack;

static float atof(std::string s)
{
	std::stringstream ss(s);
	float ret;
	ss >> ret;
	return ret;
}

float RPN::calculate(std::string str)
{
	std::stringstream ss(str);
	std::string s;
	while (std::getline(ss, s, ' '))
	{
		if (s.length() > 1)
			throw Error("Error: more than one");
		if (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/')
		{
			if (_numberStack.size() < 2)
				throw Error("Error: wrong amount of number and operation");
			float val2 = _numberStack.top();
			_numberStack.pop();
			float val1 = _numberStack.top();
			_numberStack.pop();
			float newVal;
			switch (s[0])
			{
			case '+':
				newVal = val1 + val2;
				break;
			case '-':
				newVal = val1 - val2;
				break;
			case '*':
				newVal = val1 * val2;
				break;
			case '/':
				newVal = val1 / val2;
				if (val2 == 0)
					throw Error("Error: division by 0");
				break;
			}
			_numberStack.push(newVal);
		}
		else if (s[0] >= '0' && s[0] <= '9')
			_numberStack.push(atof(s));
		else
			throw Error("Error: invilid char");
	}
	if (_numberStack.size() != 1)
		throw Error("Error: wrong amount of number and operation");
	float result = _numberStack.top();
	_numberStack.pop();
	return result;
}
