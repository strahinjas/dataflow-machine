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

void Machine::execute(const std::string& fileName)
{
	readIMF(fileName);

	Memory::getInstance();
	Logger::getInstance().open(Program::getInstance().log());

	while (!waiting.empty() || !executing.empty())
	{
		for (const auto& operation : waiting)
		{
			if (operation->isReady())
			{
				operation->setStartTime(Scheduler::Instance()->getCurTime());

				Event::create(operation.get(), operation->getDelay());

				executing.insert(operation);
				waiting.erase(operation);
			}
		}

		Scheduler::Instance()->processNow();
	}

	Memory::getInstance().log(Program::getInstance().mem());
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
	TokenPointer result = std::make_shared<Token>(tokens[2], ID);
	OperationPointer operation;

	switch (tokens[1][0])
	{
	case '=':
		operation = OperationPointer(new Assignment(ID));
		break;
	case '+':
		operation = OperationPointer(new Addition(ID));
		break;
	case '*':
		operation = OperationPointer(new Multiplication(ID));
		break;
	case '^':
		operation = OperationPointer(new Exponentiation(ID));
		break;
	}

	operation->addOperand(makeToken(tokens[3]));

	if (tokens[1][0] != '=')
		operation->addOperand(makeToken(tokens[4]));

	operation->setResult(result);
	waiting.insert(std::move(operation));
}

TokenPointer Machine::makeToken(const std::string& token) const
{
	TokenPointer pointer;
	const std::regex constant(R"(^-?(0|([1-9][0-9]*))(\.[0-9]+)?$)");

	if (std::regex_match(token, constant))
	{
		pointer = std::make_shared<Token>(std::stod(token));
	}
	else
	{
		pointer = Token::getToken(token);
	}

	return pointer;
}