#include "operation.h"

#include <cmath>

void Operation::notify(unsigned int ID)
{
}

void Addition::execute()
{
	double result = operands[LEFT]->getValue() + operands[RIGHT]->getValue();
	this->result->setValue(result);
}

void Multiplication::execute()
{
	double result = operands[LEFT]->getValue() * operands[RIGHT]->getValue();
	this->result->setValue(result);
}

void Exponentiation::execute()
{
	double result = std::pow(operands[LEFT]->getValue(), operands[RIGHT]->getValue());
	this->result->setValue(result);
}

void Assignment::execute()
{
	
}