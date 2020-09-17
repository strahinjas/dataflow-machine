#ifndef _OPERATION_H_
#define _OPERATION_H_

#include "configuration.h"
#include "token.h"

#include "Interfaces.h"

#include <vector>

class Operation : public ITimedElement
{
public:
	virtual ~Operation();

	void notify(unsigned int) override;

	virtual bool isReady() const;

	bool addOperand(Token* operand)
	{
		if (operands.size() == operandCount) return false;

		operands.push_back(operand);
		return true;
	}

	unsigned int getID() const { return ID; }

	double getDelay() const { return delay; }
	void setStartTime(double time) { startTime = time; }

	bool isDone() const { return done; }

	void setResult(Token* result)
	{
		this->result = result;
	}

	virtual void execute() = 0;
protected:
	Operation(unsigned int ID, unsigned int operandCount, double delay)
		: ID(ID), operandCount(operandCount), delay(delay), startTime(0.0), done(false), result(nullptr) {}

	unsigned int ID;
	unsigned int operandCount;

	double delay;
	double startTime;

	bool done;

	Token* result;
	std::vector<Token*> operands;
};

class OperationCompare
{
public:
	bool operator()(const Operation* left, const Operation* right) const
	{
		return left->getID() < right->getID();
	}
};

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
		: Operation(ID, 1, Configuration::getInstance().getParameter(Configuration::Parameter::Tw)) {}

	bool isReady() const override;

	void execute() override;
};

#endif