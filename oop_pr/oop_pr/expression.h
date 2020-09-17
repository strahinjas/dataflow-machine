#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Expression
{
public:
	enum class Operation : char
	{
		ASSIGN = '=',
		ADD = '+',
		MULTIPLY = '*',
		EXPONENTIATE = '^',
		NONE
	};

	Expression(Operation operation, Expression* left = nullptr, Expression* right = nullptr)
		: operation(operation), left(left), right(right) {}

	virtual ~Expression()
	{
		if (left)  delete left;
		if (right) delete right;
	}
private:
	friend class SimpleCompilationStrategy;
	friend class AdvancedCompilationStrategy;

	Operation operation;

	Expression* left;
	Expression* right;
};

std::ostream& operator<<(std::ostream& os, Expression::Operation operation);

class Variable : public Expression
{
public:
	Variable(char name) : Expression(Operation::NONE), name(name) {}
private:
	friend class SimpleCompilationStrategy;
	friend class AdvancedCompilationStrategy;

	char name;
};

class Constant : public Expression
{
public:
	Constant(double value) : Expression(Operation::NONE), value(value) {}
private:
	friend class SimpleCompilationStrategy;
	friend class AdvancedCompilationStrategy;

	double value;
};

#endif