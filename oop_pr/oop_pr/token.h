#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "exceptions.h"

#include <memory>
#include <string>
#include <unordered_map>

class Token
{
public:
	Token(const std::string& name, unsigned int operationID = 0);

	bool isReady() const { return ready; }

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

	bool ready;

	std::string name;
	double value;
	unsigned int operationID;
};

using TokenPointer = std::shared_ptr<Token>;

#endif