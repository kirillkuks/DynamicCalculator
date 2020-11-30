#pragma once
#include "operations.h"

using namespace operations;

struct Stack {
	Stack();
	void push(Expression*);
	Expression* pop();
	Expression* top();
	int size();
private:
	std::vector<Expression*> stack;
};


struct Calculator {
	Calculator(std::vector<Parser*>&);
	double calculate(std::string const&);
	~Calculator();
private:
	std::vector<Expression*> make_polish();
	double calculate_polish(std::vector<Expression*>&);
	Expression* next_expression();
	std::string read_number();
	std::string read_operation();
	std::string read_bracket();
private:
	std::string expression;
	std::vector<Parser*> parsers;
	Stack stack;
	size_t cur_index;
};