#ifndef _COMPILER_H_
#define _COMPILER_H_

#include "compilation_strategy.h"

#include <algorithm>
#include <cctype>
#include <memory>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

constexpr int parameterCount = 5;

class Compiler
{
public:
	enum Parameter { Ta, Tm, Te, Tw, Nw, C };

	void readConfiguration(const std::string& fileName);
	void readProgram(const std::string& fileName);
private:
	static void trim(std::string& s);
	static void removeExtraSpaces(std::string& s);

	static inline void cleanUp(std::string& s)
	{
		trim(s);
		removeExtraSpaces(s);
	}

	void readParameter(const std::string& line);

	static std::unordered_map<Parameter, std::regex> parameterMatcher;

	std::vector<double> parameters;
	std::unique_ptr<CompilationStrategy> strategy;
};

inline void Compiler::trim(std::string& s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) { return !std::isspace(c); }));
	s.erase(std::find_if(s.rbegin(), s.rend(), [i = 0](int c) { return !std::isspace(c); }).base(), s.end());
}

inline void Compiler::removeExtraSpaces(std::string& s)
{
	auto iterator = std::unique(s.begin(), s.end(), [](char a, char b) { return std::isspace(a) && isspace(b); });

	s.resize(iterator - s.begin());
}

#endif