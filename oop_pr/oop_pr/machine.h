#ifndef _MACHINE_H_
#define _MACHINE_H_

#include <string>

class Machine
{
public:
	Machine(const Machine&) = delete;
	Machine& operator=(const Machine&) = delete;

	static Machine& getinstance()
	{
		static Machine instance;
		return instance;
	}

	void execute(const std::string& fileName);
private:
	Machine() = default;
};

#endif