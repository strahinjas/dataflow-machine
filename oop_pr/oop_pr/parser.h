#ifndef _PARSER_H_
#define _PARSER_H_

#include "configuration.h"

#include <algorithm>
#include <cctype>
#include <regex>
#include <string>
#include <unordered_map>

class Parser
{
public:
	Parser(const Parser&) = delete;
	Parser& operator=(const Parser&) = delete;

	static Parser& getInstance()
	{
		static Parser instance;
		return instance;
	}

	void readConfiguration(const std::string& fileName);
	void readProgram(const std::string& fileName);
private:
	Parser() = default;

	static void trim(std::string& s);
	static void removeSpaces(std::string& s);
	static void removeExtraSpaces(std::string& s);

	static void cleanUp(std::string& s)
	{
		trim(s);
		removeSpaces(s);
	}

	void readParameter(const std::string& line);

	static const std::unordered_map<Configuration::Parameter, std::regex> parameterMatcher;
};

inline void Parser::trim(std::string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) { return !std::isspace(c); }));
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int c) { return !std::isspace(c); }).base(), s.end());
}

inline void Parser::removeSpaces(std::string& s)
{
	s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
}

inline void Parser::removeExtraSpaces(std::string& s)
{
	s.erase(std::unique(s.begin(), s.end(), [](char a, char b) { return std::isspace(a) && std::isspace(b); }), s.end());
}

#endif