#include "parser.h"

#include "compilation_strategy.h"
#include "compiler.h"
#include "exceptions.h"
#include "program.h"
#include "token.h"

#include <fstream>
#include <memory>
#include <stack>

const std::unordered_map<Configuration::Parameter, std::regex> Parser::parameterMatcher =
{
	{ Configuration::Parameter::Ta, std::regex("^Ta = (.+)$") },
	{ Configuration::Parameter::Tm, std::regex("^Tm = (.+)$") },
	{ Configuration::Parameter::Te, std::regex("^Te = (.+)$") },
	{ Configuration::Parameter::Tw, std::regex("^Tw = (.+)$") },
	{ Configuration::Parameter::Nw, std::regex("^Nw = (.+)$") },
	{ Configuration::Parameter::C,  std::regex("^compilation = (simple|advanced)$") }
};

std::vector<std::string> Parser::split(const std::string& line, const char* delimiter, bool include)
{
	std::vector<std::string> tokens;
	std::size_t begin = line.find_first_not_of(delimiter);

	while (begin != std::string::npos)
	{
		std::size_t end = line.find_first_of(delimiter, begin);

		tokens.push_back(line.substr(begin, end - begin));
		if (include && end != std::string::npos) tokens.push_back({ line[end] });

		begin = line.find_first_not_of(delimiter, end);
	}

	return tokens;
}

void Parser::buildExpressionTree(const std::vector<std::string>& tokens)
{
	const std::string operations = "=+*^";

	const std::regex variable(R"(^[a-zA-Z]$)");
	const std::regex constant(R"(^-?(0|([1-9][0-9]*))(\.[0-9]+)?$)");

	std::stack<std::size_t> stack;
	std::stack<Expression*> nodes;

	auto leftToRight = [](const std::string& s) { return s != "=" && s != "^"; };

	for (const auto& token : tokens)
	{
		std::size_t index = operations.find(token);

		if (index == std::string::npos)
		{
			if (std::regex_match(token, variable))
			{
				nodes.push(new Variable(token[0]));
			}
			else if (std::regex_match(token, constant))
			{
				nodes.push(new Constant(std::stod(token)));
			}
			else
			{
				throw GenericException("Invalid token '" + token + "'.");
			}
		}
		else
		{
			while (!stack.empty() && (index < stack.top() || (index == stack.top() && leftToRight(token))))
			{
				Expression* right = nodes.top(); nodes.pop();
				Expression* left  = nodes.top(); nodes.pop();

				Expression::Operation operation(static_cast<Expression::Operation>(operations[stack.top()]));

				nodes.push(new Expression(operation, left, right));

				stack.pop();
			}

			stack.push(index);
		}
	}

	while (!stack.empty())
	{
		Expression* right = nodes.top(); nodes.pop();
		Expression* left  = nodes.top(); nodes.pop();

		Expression::Operation operation(static_cast<Expression::Operation>(operations[stack.top()]));

		nodes.push(new Expression(operation, left, right));

		stack.pop();
	}

	Program::getInstance().addExpression(nodes.top());
	nodes.pop();
}

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
				Configuration::getInstance().setStrategy(match[1]);
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
					throw GenericException("Invalid parameter value (double expected): " + line + ".");
				}
			}

			return;
		}
	}

	throw GenericException("Invalid configuration parameter: " + line + ".");
}

void Parser::readConfiguration(const std::string& fileName)
{
	std::ifstream file(fileName);
	Configuration::getInstance().resetParameters();

	if (!file.is_open())
	{
		throw GenericException("Failed to open configuration file '" + fileName + "'.");
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
		throw GenericException("Failed to open program file '" + fileName + "'.");
	}

	std::string line;

	while (std::getline(file, line))
	{
		removeSpaces(line);
		buildExpressionTree(split(line, "=+*^", true));
	}

	file.close();
}