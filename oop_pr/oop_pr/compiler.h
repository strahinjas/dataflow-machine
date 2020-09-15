#ifndef _COMPILER_H_
#define _COMPILER_H_

#include "compilation_strategy.h"

#include <memory>

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

	void setStrategy(std::unique_ptr<CompilationStrategy> strategy)
	{
		this->strategy = std::move(strategy);
	}

	void compile() const { strategy->execute(); }
private:
	Compiler() = default;

	std::unique_ptr<CompilationStrategy> strategy;
};

#endif