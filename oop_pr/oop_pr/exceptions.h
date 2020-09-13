#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>
#include <string>

class CompilingException : public std::exception
{
public:
	CompilingException(const std::string& message) : message(message) {}

	const char* what() const noexcept override
	{
		return message.c_str();
	}
private:
	std::string message;
};

class VariableNotAvailableException : public std::exception
{
public:
	VariableNotAvailableException(const std::string& variableName)
		: message("Variable '" + variableName + "' does not exist in memory!") {}

	const char* what() const noexcept override
	{
		return message.c_str();
	}
private:
	std::string message;
};

class SSAViolationException : public std::exception
{
public:
	SSAViolationException(const std::string& variableName)
		: message("Write operation on variable '" + variableName + "' violates single assignment rule!") {}

	const char* what() const noexcept override
	{
		return message.c_str();
	}
private:
	std::string message;
};

#endif