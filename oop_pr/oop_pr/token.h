#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "exceptions.h"

#include <string>
#include <unordered_set>

class Token
{
public:
	Token(const std::string& name, double value, int operationID)
		: name(name), value(value), operationID(operationID)
	{
		if (tokens.insert(name).second == false)
		{
			throw TokenDefinedException(name);
		}
	}
private:
	static std::unordered_set<std::string> tokens;

	std::string name;
	double value;
	int operationID;
};

#endif