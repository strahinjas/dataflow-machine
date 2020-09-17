#include "compiler.h"
#include "machine.h"
#include "program.h"

#include <exception>
#include <iostream>
#include <string>

int main(int argc, const char* argv[])
{
	constexpr int args = 3;
	constexpr int configurationIndex = 1;
	constexpr int programIndex = 2;

	if (argc != args)
	{
		std::cerr << "Invalid number of arguments!\n";
		std::cerr << "Program should be called with exactly two arguments: <configuration_file> <program_file>\n\n";
		return 1;
	}

	std::string configuration = argv[configurationIndex];
	std::string program = argv[programIndex];

	try
	{
		Compiler::getInstance().compile(configuration, program);
		Machine::getInstance().execute(Program::getInstance().imf());
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERROR: " << e.what() << "\n\n";
		return 1;
	}

	return 0;
}