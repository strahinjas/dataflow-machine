#ifndef _COMPILER_H_
#define _COMPILER_H_

#include "compilation_strategy.h"
#include "configuration.h"
#include "parser.h"

#include <string>

class Compiler
{
public:
	Compiler(const Compiler&) = delete;
	Compiler& operator=(const Compiler&) = delete;

	static Compiler& getInstance()
	{
		static Compiler instance;
		return instance;
	}

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

		strategy->execute();
	}
private:
	Compiler() = default;

	CompilationStrategy* strategy;
};

#endif