#ifndef _COMPILER_H_
#define _COMPILER_H_

#include "compilation_strategy.h"
#include "configuration.h"
#include "parser.h"

#include <memory>
#include <string>

class Compiler
{
public:
	void setStrategy(std::unique_ptr<CompilationStrategy> strategy)
	{
		this->strategy = std::move(strategy);
	}

	void compile(const std::string& configuration, const std::string& program)
	{
		Parser::readConfiguration(configuration);
		Parser::readProgram(program);

		const std::string simple = "simple";

		if (Configuration::getInstance().getStrategy() == simple)
			setStrategy(std::make_unique<SimpleCompilationStrategy>());
		else
			setStrategy(std::make_unique<AdvancedCompilationStrategy>());

		strategy->execute();
	}
private:
	std::unique_ptr<CompilationStrategy> strategy;
};

#endif