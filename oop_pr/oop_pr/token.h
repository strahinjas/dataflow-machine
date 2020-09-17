#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "exceptions.h"

#include <memory>
#include <string>
#include <unordered_map>

class Token
{
public:
	explicit Token(double value) : value(value), operationID(0), isReady(true) {}
	Token(const std::string& name, unsigned int operationID = 0);

	static std::shared_ptr<Token> getToken(const std::string& name)
	{
		return tokens.at(name);
	}

	bool isReady() const { return isReady; }

	const std::string& getName() const { return name; }

	double getValue() const { return value; }
	void setValue(double value)
	{
		this->value = value;
	}

	unsigned int getOperationID() const { return operationID; }
	void setOperationID(unsigned int ID) { operationID = ID; }
private:
	static std::unordered_map<std::string, std::shared_ptr<Token>> tokens;

	bool isReady;

	std::string name;
	double value;
	unsigned int operationID;
};

using TokenPointer = std::shared_ptr<Token>;

#endif