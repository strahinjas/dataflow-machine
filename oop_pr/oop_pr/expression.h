#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <string>

class Expression
{
public:
	enum class Operation
	{
		ASSIGNMENT,
		ADDITION,
		MULTIPLICATION,
		EXPONENTIATION
	};

	Expression(Operation operation, Expression* left = nullptr, Expression* right = nullptr)
		: operation(operation), left(left), right(right) {}
private:
	Expression* left;
	Expression* right;

	Operation operation;
};

class Constant : public Expression
{
public:

private:
	double value;
};

class Variable : public Expression
{
public:

private:
	?td::string name;
};

#endif