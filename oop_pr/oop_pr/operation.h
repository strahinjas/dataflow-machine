#ifndef _OPERATION_H_
#define _OPERATION_H_

#include "token.h"

#include <vector>

class Operation
{
public:
protected:
	Operation(unsigned int ID, unsigned int operandCount, double delay)
		: ID(ID), operandCount(operandCount), delay(delay) {}
private:
	unsigned int ID;
	unsigned int operandCount;

	double delay;

	std::vector<Token> operands;
};

#endif