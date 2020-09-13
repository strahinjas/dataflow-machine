#include "compiler.h"
#include "exceptions.h"

#include <fstream>

std::unordered_map<Compiler::Parameter, std::regex> Compiler::parameterMatcher =
{
	{ Compiler::Ta, std::regex("^Ta = (.+)$") },
	{ Compiler::Tm, std::regex("^Tm = (.+)$") },
	{ Compiler::Te, std::regex("^Te = (.+)$") },
	{ Compiler::Tw, std::regex("^Tw = (.+)$") },
	{ Compiler::Nw, std::regex("^Nw = (.+)$") },
	{ Compiler::C,  std::regex("^compilation = (simple|advanced)$") }
};

void Compiler::readParameter(const std::string& line)
{
	const std::string simpleStrategy = "simple";

	for (const auto& entry : parameterMatcher)
	{
		std::smatch match;

		if (std::regex_match(line, match, entry.second))
		{
			if (entry.first == C)
			{
				if (match[1] == simpleStrategy)
					strategy = std::unique_ptr<CompilationStrategy>(new SimpleCompilationStrategy());
				else
					strategy = std::unique_ptr<CompilationStrategy>(new AdvancedCompilationStrategy());
			}
			else
			{
				try
				{
					double value = std::stod(match[1]);
					parameters[entry.first] = value;
				}
				catch (const std::exception&)
				{
					throw CompilingException("Invalid parameter value (double expected): " + line + ".");
				}
			}

			return;
		}
	}

	throw CompilingException("Invalid configuration parameter: " + line + ".");
}

void Compiler::readConfiguration(const std::string& fileName)
{
	std::ifstream file(fileName);
	parameters = std::vector<double>(parameterCount, 0.0);

	if (!file.is_open())
	{
		throw CompilingException("Failed to open configuration file '" + fileName + "'.");
	}

	std::string line;

	while (std::getline(file, line))
	{
		cleanUp(line);
		readParameter(line);
	}
}

void Compiler::readProgram(const std::string& fileName)
{
}