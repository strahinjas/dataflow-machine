#ifndef _MEMORY_H_
#define _MEMORY_H_

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

	bool ready() const { return writeCount < Nw; }

	void write(const std::string& fileName) const;
private:
	explicit Memory(int Nw) : Nw(Nw), writeCount(0) {}

	int Nw;
	int writeCount;
	std::map<std::string, double> variables;
};

#endif