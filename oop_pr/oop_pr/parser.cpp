#include "parser.h"

#include "compilation_strategy.h"
#include "compiler.h"
#include "exceptions.h"
#include "program.h"

#include <fstream>
#include <memory>

const std::unordered_map<Configuration::Parameter, std::regex> Parser::parameterMatcher =
{
	{ Configuration::Parameter::Ta, std::regex("^Ta = (.+)$") },
	{ Configuration::Parameter::Tm, std::regex("^Tm = (.+)$") },
	{ Configuration::Parameter::Te, std::regex("^Te = (.+)$") },
	{ Configuration::Parameter::Tw, std::regex("^Tw = (.+)$") },
	{ Configuration::Parameter::Nw, std::regex("^Nw = (.+)$") },
	{ Configuration::Parameter::C,  std::regex("^compilation = (simple|advanced)$") }
};

void Parser::readParameter(const std::string& line)
{
	const std::string simpleStrategy = "simple";

	for (const auto& entry : parameterMatcher)
	{
		std::smatch match;

		if (std::regex_match(line, match, entry.second))
		{
			if (entry.first == Configuration::Parameter::C)
			{
				if (match[1] == simpleStrategy)
					Compiler::getInstance().setStrategy(std::make_unique<SimpleCompilationStrategy>());
				else
					Compiler::getInstance().setStrategy(std::make_unique<AdvancedCompilationStrategy>());
			}
			else
			{
				try
				{
					double value = std::stod(match[1]);
					Configuration::getInstance().setParameter(entry.first, value);
				}
				catch (const std::exception&)
				{
					throw ParsingException("Invalid parameter value (double expected): " + line + ".");
				}
			}

			return;
		}
	}

	throw ParsingException("Invalid configuration parameter: " + line + ".");
}

void Parser::readConfiguration(const std::string& fileName)
{
	std::ifstream file(fileName);
	Configuration::getInstance().resetParameters();

	if (!file.is_open())
	{
		throw ParsingException("Failed to open configuration file '" + fileName + "'.");
	}

	std::string line;

	while (std::getline(file, line))
	{
		trim(line);
		removeExtraSpaces(line);
		readParameter(line);
	}

	file.close();
}

void Parser::readProgram(const std::string& fileName)
{
	std::ifstream file(fileName);
	Program::getInstance().setName(fileName.substr(0, fileName.find_last_of('.')));

	if (!file.is_open())
	{
		throw ParsingException("Failed to open program file '" + fileName + "'.");
	}

	std::string line;

	while (std::getline(file, line))
	{
		cleanUp(line);
	}

	file.close();
}