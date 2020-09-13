#ifndef _COMPILATION_STRATEGY_H_
#define _COMPILATION_STRATEGY_H_

class CompilationStrategy
{
public:
	virtual void execute() const = 0;
};

class SimpleCompilationStrategy : public CompilationStrategy
{
public:
	void execute() const override;
};

class AdvancedCompilationStrategy : public CompilationStrategy
{
public:
	void execute() const override;
};

#endif