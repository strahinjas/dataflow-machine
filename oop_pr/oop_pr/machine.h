#ifndef _MACHINE_H_
#define _MACHINE_H_

#include "operation.h"

#include <set>
#include <string>
#include <vector>

class Machine
{
public:
	static Machine& getInstance()
	{
		static Machine instance;
		return instance;
	}

	~Machine();

	void execute(const std::string& fileName);
private:
	Machine() = default;

	Machine(const Machine&) = delete;
	Machine& operator=(const Machine&) = delete;

	void readIMF(const std::string& fileName);
	void buildFlowGraph(const std::vector<std::string>& tokens);

	Token* makeToken(const std::string& token) const;

	void moveReady();
	void moveCompleted();

	std::set<Operation*, OperationCompare> waiting;
	std::set<Operation*, OperationCompare> executing;
	std::set<Operation*, OperationCompare> completed;
};

#endif