#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "exceptions.h"

#include <string>
#include <unordered_map>

class Token
{
public:
	explicit Token(double value) : value(value), operationID(0), ready(true) {}
	Token(const std::string& name, unsigned int operationID = 0);

	static Token* getToken(const std::string& name)
	{
		return tokens.at(name);
	}

	bool isReady() const { return ready; }

	const std::string& getName() const { return name; }

	double getValue() const { return value; }
	void setValue(double value)
	{
		ready = true;
		this->value = value;
	}

	unsigned int getOperationID() const { return operationID; }
	void setOperationID(unsigned int ID) { operationID = ID; }
private:
	static std::unordered_map<std::string, Token*> tokens;

	bool ready;

	std::string name;
	double value;
	unsigned int operationID;
};

#endif