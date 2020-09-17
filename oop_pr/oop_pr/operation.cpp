#include "operation.h"

#include "logger.h"
#include "memory.h"

#include <cmath>
#include <iomanip>
#include <sstream>

void Operation::notify(unsigned int)
{
	execute();
	
	constexpr short WIDTH = 6;

	std::stringstream ss;
	ss << std::left << std::setw(WIDTH) << "[" + std::to_string(ID) + "]";
	ss << '(' << startTime << '-' << startTime + delay << ")ns";

	Logger::getInstance().log(ss.str());
}

bool Operation::isReady() const
{
	for (const auto& operand : operands)
	{
		if (!operand->isReady()) return false;
	}

	return true;
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

bool Assignment::isReady() const
{
	return Operation::isReady() && Memory::getInstance().scheduleWrite();
}

void Assignment::execute()
{
	result->setValue(operands[0]->getValue());
	Memory::getInstance().set(result->getName(), result->getValue());
}