#include "program.h"

Program::~Program()
{
	for (auto& expression : expressions) delete expression;
}