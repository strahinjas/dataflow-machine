#include "memory.h"

#include "exceptions.h"
#include "parser.h"

#include <fstream>

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

void Memory::log(const std::string& fileName) const
{
	std::ofstream file(fileName, std::ofstream::trunc);

	if (!file.is_open())
	{
		throw GenericException("Failed to create memory file '" + fileName + "'.");
	}

	for (const auto& variable : variables)
	{
		file << variable.first << " = " << doubleToString(variable.second) << '\n';
	}

	file.close();
}