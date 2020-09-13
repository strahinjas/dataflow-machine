#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#include <cstddef>
#include <vector>

constexpr int parameterCount = 5;

class Configuration
{
public:
	Configuration(const Configuration&) = delete;
	Configuration& operator=(const Configuration&) = delete;

	enum class Parameter { Ta, Tm, Te, Tw, Nw, C };

	static Configuration& getInstance()
	{
		static Configuration instance;
		return instance;
	}

	double getParameter(Parameter index) const
	{
		return parameters[static_cast<std::size_t>(index)];
	}

	void setParameter(Parameter index, double value)
	{
		parameters[static_cast<std::size_t>(index)] = value;
	}

	void resetParameters()
	{
		parameters = std::vector<double>(parameterCount, 0.0);
	}
private:
	Configuration() = default;

	std::vector<double> parameters;
};

#endif