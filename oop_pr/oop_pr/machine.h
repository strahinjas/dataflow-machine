#ifndef _MACHINE_H_
#define _MACHINE_H_

#include "operation.h"

#include <string>
#include <unordered_set>
#include <vector>

class Machine
{
public:
	void execute(const std::string& fileName);
private:
	void readIMF(const std::string& fileName);
	void buildFlowGraph(const std::vector<std::string>& tokens);

	TokenPointer makeToken(const std::string& token) const;

	std::unordered_set<OperationPointer> waiting;
	std::unordered_set<OperationPointer> executing;
};

#endif