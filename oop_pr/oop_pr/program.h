#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <string>

class Program
{
public:
	Program(const Program&) = delete;
	Program& operator=(const Program&) = delete;

	static Program& getInstance()
	{
		static Program instance;
		return instance;
	}

	void setName(const std::string& name) { this->name = name; }

	std::string imf() const { return name + ".imf"; }
	std::string log() const { return name + ".log"; }
	std::string mem() const { return name + ".mem"; }
private:
	Program() = default;

	std::string name;
};

#endif