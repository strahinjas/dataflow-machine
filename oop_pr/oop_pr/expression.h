#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Expression
{
public:
	using TokenPointer = std::shared_ptr<Expression>;

	enum class Operation : char
	{
		ASSIGN = '=',
		ADD = '+',
		MULTIPLY = '*',
		EXPONENTIATE = '^',
		NONE
	};

	Expression(Operation operation, TokenPointer left = nullptr, TokenPointer right = nullptr)
		: operation(operation), left(left), right(right) {}

	virtual ~Expression() {}
private:
	friend class SimpleCompilationStrategy;
	friend class AdvancedCompilationStrategy;

	Operation operation;

	TokenPointer left;
	TokenPointer right;
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