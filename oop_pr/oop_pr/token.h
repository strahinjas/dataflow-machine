#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "exceptions.h"

#include <string>
#include <unordered_map>

class Token
{
public:
	Token(const std::string& name, double value, int operationID);
private:
	static std::unordered_map<std::string, Token> tokens;

	std::string name;
	double value;
	int operationID;
};

#endif