#include "token.h"

std::unordered_map<std::string, Token> Token::tokens;

Token::Token(const std::string& name, double value, int operationID)
	: name(name), value(value), operationID(operationID)
{
	if (tokens.insert({ name, *this }).second == false)
	{
		throw TokenDefinedException(name);
	}
}