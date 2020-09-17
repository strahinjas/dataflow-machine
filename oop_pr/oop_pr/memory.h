#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "configuration.h"

#include <map>
#include <string>

class Memory
{
public:
	Memory(const Memory&) = delete;
	Memory& operator=(const Memory&) = delete;

	static Memory& getInstance()
	{
		int Nw = static_cast<int>(Configuration::getInstance().getParameter(Configuration::Parameter::Nw));
		static Memory instance(Nw);
		return instance;
	}

	double get(const std::string& variableName) const;
	bool   set(const std::string& variableName, double value);

	bool contains(const std::string& name) const
	{
		return variables.count(name) > 0;
	}

	bool isReady() const { return writeCount < Nw; }
	bool scheduleWrite()
	{
		if (isReady())
		{
			++writeCount;
			return true;
		}
		return false;
	}

	void log(const std::string& fileName) const;
private:
	explicit Memory(int Nw) : Nw(Nw), writeCount(0) {}

	int Nw;
	int writeCount;
	std::map<std::string, double> variables;
};

#endif