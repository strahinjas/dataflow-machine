#include "compilation_strategy.h"

#include "exceptions.h"
#include "parser.h"
#include "program.h"

#include <cassert>
#include <stack>
#include <string>
#include <utility>

unsigned int CompilationStrategy::operationID = 0;
unsigned int CompilationStrategy::temporaryCount = 0;

void CompilationStrategy::traversePostorder(std::ofstream& file, Expression* root) const
{
	std::stack<Expression*> stack;

	std::stack<std::string> left;
	std::string right;

	while (!stack.empty() || root)
	{
		while (root)
		{
			if (root->right) stack.push(root->right);
			stack.push(root);
			root = root->left;
		}

		root = stack.top();
		stack.pop();

		if (root->right && !stack.empty() && stack.top() == root->right)
		{
			left.push(right);

			stack.pop();
			stack.push(root);
			root = root->right;
		}
		else
		{
			if (Variable* variable = dynamic_cast<Variable*>(root))
			{
				right = std::string(1, variable->name);
			}
			else if (Constant* constant = dynamic_cast<Constant*>(root))
			{
				right = doubleToString(constant->value);
			}
			else
			{
				assert(root != nullptr);
				file << '[' << ++operationID << "] " << root->operation << ' ';

				if (root->operation == Expression::Operation::ASSIGN)
				{
					file << left.top() << ' ' << right << '\n';
				}
				else
				{
					std::string result = "t" + std::to_string(++temporaryCount);

					file << result << ' ' << left.top() << ' ' << right << '\n';

					right = result;
				}

				left.pop();
			}

			root = nullptr;
		}
	}
}

void SimpleCompilationStrategy::execute() const
{
	Program& program = Program::getInstance();
	std::ofstream file(program.imf(), std::ofstream::trunc);

	if (!file.is_open())
	{
		throw GenericException("Failed to create intermediate form file '" + program.imf() + "'.");
	}

	for (const auto& expression : program.expressions)
	{
		traversePostorder(file, expression);
	}

	file.close();
}

void AdvancedCompilationStrategy::optimize(Expression* root) const
{
	auto commutative = [](Expression::Operation operation)
	{
		return operation == Expression::Operation::ADD || operation == Expression::Operation::MULTIPLY;
	};

	Expression::Operation operation = root->operation;

	auto check = [&operation](Expression* node)
	{
		return node && node->getOperation() == operation;
	};

	if (commutative(operation))
	{
		if (check(root->left))
		{
			if (check(root->left->left)) std::swap(root->right, root->left->left);
			else if (check(root->left->right)) std::swap(root->right, root->left->right);
		}

		if (check(root->right))
		{
			if (check(root->right->left)) std::swap(root->left, root->right->left);
			else if (check(root->right->right)) std::swap(root->left, root->right->right);
		}
	}

	if (root->left)  optimize(root->left);
	if (root->right) optimize(root->right);
}

void AdvancedCompilationStrategy::execute() const
{
	Program& program = Program::getInstance();
	std::ofstream file(program.imf(), std::ofstream::trunc);

	if (!file.is_open())
	{
		throw GenericException("Failed to create intermediate form file '" + program.imf() + "'.");
	}

	for (const auto& expression : program.expressions)
	{
		optimize(expression);
		traversePostorder(file, expression);
	}

	file.close();
}