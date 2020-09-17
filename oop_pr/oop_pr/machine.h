#ifndef _MACHINE_H_
#define _MACHINE_H_

#include "operation.h"

#include <set>
#include <string>
#include <vector>

class Machine
{
public:
	~Machine();

	void execute(const std::string& fileName);
private:
	void readIMF(const std::string& fileName);
	void buildFlowGraph(const std::vector<std::string>& tokens);

	Token* makeToken(const std::string& token) const;

	void transferReady();
	void transferCompleted();

	std::set<Operation*, OperationCompare> waiting;
	std::set<Operation*, OperationCompare> executing;
	std::set<Operation*, OperationCompare> completed;
};

#endif