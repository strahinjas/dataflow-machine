#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <memory>
#include <string>
#include <utility>

class Expression
{
public:
	using Pointer = std::unique_ptr<Expression>;

	Expression(const std::string& value, Pointer left = nullptr, Pointer right = nullptr)
		: value(value), left(std::move(left)), right(std::move(right)) {}
private:
	std::string value;

	Pointer left;
	Pointer right;
};

#endif