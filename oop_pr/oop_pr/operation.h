#ifndef _OPERATION_H_
#define _OPERATION_H_

#include "configuration.h"
#include "token.h"

#include "Interfaces.h"

#include <memory>
#include <vector>

class Operation : public ITimedElement
{
public:
	void notify(unsigned int ID) override;

	virtual void execute() = 0;
protected:
	Operation(unsigned int ID, unsigned int operandCount, double delay)
		: ID(ID), operandCount(operandCount), delay(delay) {}

	unsigned int ID;
	unsigned int operandCount;

	double delay;

	TokenPointer result;
	std::vector<TokenPointer> operands;
};

using OperationPointer = std::unique_ptr<Operation>;

class ArithmeticOperation : public Operation
{
protected:
	ArithmeticOperation(unsigned int ID, double delay) : Operation(ID, 2, delay) {}

	const short LEFT  = 0;
	const short RIGHT = 1;
};

class Addition : public ArithmeticOperation
{
public:
	Addition(unsigned int ID)
		: ArithmeticOperation(ID, Configuration::getInstance().getParameter(Configuration::Parameter::Ta)) {}

	void execute() override;
};

class Multiplication : public ArithmeticOperation
{
public:
	Multiplication(unsigned int ID)
		: ArithmeticOperation(ID, Configuration::getInstance().getParameter(Configuration::Parameter::Tm)) {}

	void execute() override;
};

class Exponentiation : public ArithmeticOperation
{
public:
	Exponentiation(unsigned int ID)
		: ArithmeticOperation(ID, Configuration::getInstance().getParameter(Configuration::Parameter::Te)) {}

	void execute() override;
};

class Assignment : public Operation
{
public:
	Assignment(unsigned int ID)
		: Operation(ID, 2, Configuration::getInstance().getParameter(Configuration::Parameter::Tw)) {}

	void execute() override;
};

#endif