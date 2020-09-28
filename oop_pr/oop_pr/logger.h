#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <fstream>
#include <string>

class Logger
{
public:
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	static Logger& getInstance()
	{
		static Logger instance;
		return instance;
	}

	bool open(const std::string& fileName)
	{
		if (file.is_open()) file.close();
		file.open(fileName);
		return file.is_open();
	}

	void log(const std::string& text)
	{
		file << text << '\n';
	}

	void close()
	{
		file.close();
	}
private:
	Logger() = default;

	std::ofstream file;
};

#endif