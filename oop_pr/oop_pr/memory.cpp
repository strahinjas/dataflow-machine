#include "memory.h"

double Memory::get(const std::string& variableName) const
{
	if (variables.count(variableName) == 0)
	{
		throw VariableNotAvailableException(variableName);
	}

	return variables.at(variableName);
}

bool Memory::set(const std::string& variableName, double value)
{
	if (variables.insert({ variableName, value }).second == false)
	{
		throw SSAViolationException(variableName);
	}

	return true;
}