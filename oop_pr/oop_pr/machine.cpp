#include "machine.h"

#include "exceptions.h"
#include "parser.h"

void Machine::execute(const std::string& fileName)
{
	Parser::readIMF(fileName);
}