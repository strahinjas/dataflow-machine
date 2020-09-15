#ifndef _COMPILATION_STRATEGY_H_
#define _COMPILATION_STRATEGY_H_

#include "expression.h"

#include <fstream>
#include <iomanip>
#include <sstream>

class CompilationStrategy
{
public:
	virtual ~CompilationStrategy() {}

	virtual void execute() const = 0;
protected:
	using Node = Expression::Pointer;

	static std::string doubleToString(double value)
	{
		std::stringstream ss;
		ss << std::setprecision(0) << value;
		return ss.str();
	}

	static int operationID;
	static int temporaryCount;
};

class SimpleCompilationStrategy : public CompilationStrategy
{
public:
	void execute() const override;
private:
	void traversePostorder(std::ofstream& file, Node root) const;
};

class AdvancedCompilationStrategy : public CompilationStrategy
{
public:
	void execute() const override;
};

#endif