#include "expression.h"

std::ostream& operator<<(std::ostream& os, Expression::Operation operation)
{
	switch (operation)
	{
	case Expression::Operation::ASSIGN:
		return os << '=';
	case Expression::Operation::ADD:
		return os << '+';
	case Expression::Operation::MULTIPLY:
		return os << '*';
	case Expression::Operation::EXPONENTIATE:
		return os << '^';
	default:
		return os << '_';
	}
}