#include "compilation_strategy.h"

#include "exceptions.h"
#include "parser.h"
#include "program.h"

#include <stack>
#include <string>

unsigned int CompilationStrategy::operationID = 0;
unsigned int CompilationStrategy::temporaryCount = 0;

void SimpleCompilationStrategy::traversePostorder(std::ofstream& file, Node root) const
{
	std::stack<Node> stack;

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
			if (Variable* variable = dynamic_cast<Variable*>(root.get()))
			{
				right = std::string(1, variable->name);
			}
			else if (Constant* constant = dynamic_cast<Constant*>(root.get()))
			{
				right = doubleToString(constant->value);
			}
			else
			{
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

void AdvancedCompilationStrategy::execute() const
{
	// TODO: Advanced Compilation Strategy
}