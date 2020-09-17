#include "machine.h"

#include "exceptions.h"
#include "logger.h"
#include "memory.h"
#include "parser.h"
#include "program.h"

#include "Event.h"
#include "Sched.h"

#include <fstream>
#include <regex>

Machine::~Machine()
{
	for (auto& operation : completed) delete operation;
}

void Machine::execute(const std::string& fileName)
{
	readIMF(fileName);

	Memory::getInstance();
	Logger::getInstance().open(Program::getInstance().log());

	while (!waiting.empty() || !executing.empty())
	{
		transferReady();

		Scheduler::Instance()->processNow();

		transferCompleted();
	}

	Memory::getInstance().log(Program::getInstance().mem());
	Logger::getInstance().close();
}

void Machine::readIMF(const std::string& fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
	{
		throw GenericException("Failed to open intermediate form file '" + fileName + "'.");
	}

	std::string line;

	while (std::getline(file, line))
	{
		buildFlowGraph(Parser::split(line, "[ ]", false));
	}

	file.close();
}

void Machine::buildFlowGraph(const std::vector<std::string>& tokens)
{
	unsigned int ID = std::stoi(tokens[0]);
	Token* result = new Token(tokens[2], ID);
	Operation* operation;

	switch (tokens[1][0])
	{
	case '=':
		operation = new Assignment(ID);
		break;
	case '+':
		operation = new Addition(ID);
		break;
	case '*':
		operation = new Multiplication(ID);
		break;
	default:
		operation = new Exponentiation(ID);
		break;
	}

	operation->addOperand(makeToken(tokens[3]));

	if (tokens[1][0] != '=')
		operation->addOperand(makeToken(tokens[4]));

	operation->setResult(result);
	waiting.insert(operation);
}

Token* Machine::makeToken(const std::string& token) const
{
	Token* pointer;
	const std::regex constant(R"(^-?(0|([1-9][0-9]*))(\.[0-9]+)?$)");

	if (std::regex_match(token, constant))
	{
		pointer = new Token(std::stod(token));
	}
	else
	{
		pointer = Token::getToken(token);
	}

	return pointer;
}

void Machine::transferReady()
{
	auto it = waiting.begin();

	while (it != waiting.end())
	{
		Operation* operation = *it;

		if (operation->isReady())
		{
			operation->setStartTime(Scheduler::Instance()->getCurTime());

			Event::create(operation, operation->getDelay());

			executing.insert(operation);
			it = waiting.erase(it);
		}
		else ++it;
	}
}

void Machine::transferCompleted()
{
	auto it = executing.begin();

	while (it != executing.end())
	{
		Operation* operation = *it;

		if (operation->isDone())
		{
			completed.insert(operation);
			it = executing.erase(it);
		}
		else ++it;
	}
}