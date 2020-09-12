#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "exceptions.h"

#include <map>
#include <string>

class Memory
{
public:
	Memory(const Memory&) = delete;
	Memory& operator=(const Memory&) = delete;

	static Memory& getInstance(int Nw)
	{
		static Memory instance(Nw);
		return instance;
	}

	double get(const std::string& variableName) const;
	bool   set(const std::string& variableName, double value);
private:
	explicit Memory(int Nw) : Nw(Nw) {}

	int Nw;
//	int writeCount = 0;
	std::map<std::string, double> variables;
};

#endif