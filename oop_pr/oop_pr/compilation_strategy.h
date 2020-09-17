#ifndef _COMPILATION_STRATEGY_H_
#define _COMPILATION_STRATEGY_H_

#include "expression.h"

#include <fstream>

class CompilationStrategy
{
public:
	virtual void execute() const = 0;
protected:
	static unsigned int operationID;
	static unsigned int temporaryCount;
};

class SimpleCompilationStrategy : public CompilationStrategy
{
public:
	void execute() const override;
private:
	void traversePostorder(std::ofstream& file, Expression* root) const;
};

class AdvancedCompilationStrategy : public CompilationStrategy
{
public:
	void execute() const override;
};

#endif