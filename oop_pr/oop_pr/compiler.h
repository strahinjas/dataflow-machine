#ifndef _COMPILER_H_
#define _COMPILER_H_

#include "compilation_strategy.h"
#include "configuration.h"
#include "parser.h"

#include <string>

class Compiler
{
public:
	Compiler() : strategy(nullptr) {}

	~Compiler() { delete strategy; }

	void setStrategy(CompilationStrategy* strategy)
	{
		if (this->strategy) delete this->strategy;
		this->strategy = strategy;
	}

	void compile(const std::string& configuration, const std::string& program)
	{
		Parser::readConfiguration(configuration);
		Parser::readProgram(program);

		const std::string simple = "simple";

		if (Configuration::getInstance().getStrategy() == simple)
			setStrategy(new SimpleCompilationStrategy());
		else
			setStrategy(new AdvancedCompilationStrategy());

		strategy->execute();
	}
private:
	CompilationStrategy* strategy;
};

#endif