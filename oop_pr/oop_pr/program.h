#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include "compilation_strategy.h"
#include "expression.h"

#include <memory>
#include <string>
#include <vector>
#include <utility>

class Program
{
public:
	Program(const Program&) = delete;
	Program& operator=(const Program&) = delete;

	static Program& getInstance()
	{
		static Program instance;
		return instance;
	}

	void setName(const std::string& name) { this->name = name; }

	std::string imf() const { return name + ".imf"; }
	std::string log() const { return name + ".log"; }
	std::string mem() const { return name + ".mem"; }

	void addExpression(Expression::Pointer expression)
	{
		expressions.push_back(expression);
	}
private:
	Program() = default;

	friend class SimpleCompilationStrategy;
	friend class AdvancedCompilationStrategy;

	std::string name;
	std::vector<Expression::Pointer> expressions;
};

#endif