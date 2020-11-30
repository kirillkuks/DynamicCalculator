#include "calculator.h"

Stack::Stack() {}

void Stack::push(Expression* expression) {
	stack.push_back(expression);
}

Expression* Stack::pop() {
	Expression* expression = stack[stack.size() - 1];
	stack.pop_back();
	return expression;
}

Expression* Stack::top() {
	return stack[stack.size() - 1];
}

int Stack::size() {
	return stack.size();
}

Calculator::Calculator(std::vector<Parser*>& parsers_) : parsers{ parsers_ }, cur_index{ 0 } {}

Calculator::~Calculator() {}

double Calculator::calculate(std::string const& expression_) {
	expression = expression_;
	std::vector<Expression*> polish = make_polish();
	double result = calculate_polish(polish);
	return result;
}

std::vector<Expression*> Calculator::make_polish() {
	cur_index = 0;
	std::vector<Expression*> polish;
	for (cur_index = 0; cur_index < expression.size();) {
		Expression* expr = next_expression();
		switch (expr->type()) {
		case OperationType::OPERATION_NUMBER:
		case OperationType::OPEARTION_POSTFIX: {
			polish.push_back(expr);
		}
			break;
		case OperationType::OPERATION_PREFIX:
		case OperationType::OPERATION_OPENBRACKET: {
			stack.push(expr);
		}
			break;
		case OperationType::OPERATION_CLOSEBRACKET: {
			Expression* e = stack.pop();
			while (e->type() != OperationType::OPERATION_OPENBRACKET) {
				polish.push_back(e);
				e = stack.pop();
			}
			delete e;
		}
			break;
		case OperationType::OPERATION_BINARY: {
			if (stack.size() > 0) {
				Expression* e = stack.top();
				while (e->type() == OperationType::OPERATION_PREFIX || e->priority() > expr->priority()) {
					polish.push_back(e);
					stack.pop();
					if (stack.size() <= 0) {
						break;
					}
					e = stack.top();
				}
			}
			stack.push(expr);
		}
			break;
		}
	}
	if (stack.size() > 0) {
		do {
			polish.push_back(stack.pop());
		} while (stack.size() > 0);
	}
	return polish;
}

Expression* Calculator::next_expression() {
	std::string token;
	Expression* next_expr = nullptr;
	token = read_number();
	if (token.empty()) {
		token = read_operation();
		if (token.empty()) {
			token = read_bracket();
			if (token.empty()) {
				std::cout << "Error\n";
			}
			else {
				if (token == "(") {
					next_expr = new OpenBracket();
				}
				else {
					next_expr = new CloseBracket();
				}
			}
		}
		else {
			for (auto parser : parsers) {
				if (parser->getLexeme() == token) {
					next_expr = parser->parse();
					break;
				}
			}
		}
	}
	else {
		next_expr = new Number(std::stod(token));
	}
	return next_expr;
}

std::string Calculator::read_number() {
	std::string number;
	size_t i = cur_index;
	while ((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '.' && i < expression.size()) {
		++i;
	}
	if (i - cur_index) {
		number = expression.substr(cur_index, i - cur_index);
		cur_index = i;
	}
	return number;
}

std::string Calculator::read_operation() {
	std::string operation;
	size_t i = cur_index;
	while (((expression[i] < '0' || expression[i] > '9') && expression[i] != ')' && expression[i] != '(') && i < expression.size()) {
		++i;
		operation = expression.substr(cur_index, i - cur_index);
		for (auto parser : parsers) {
			if (operation == parser->getLexeme()) {
				cur_index = i;
				return operation;
			}
		}
	}
	return operation;
}

std::string Calculator::read_bracket() {
	std::string bracket;
	if (expression[cur_index] == '(' || expression[cur_index] == ')') {
		bracket = expression[cur_index];
		++cur_index;
		return bracket;
	}
	return bracket;
}

double Calculator::calculate_polish(std::vector<Expression*>& polish) {
	for (auto expr : polish) {
		switch (expr->type()) {
		case OperationType::OPERATION_NUMBER:
			stack.push(expr);
			break;
		case OperationType::OPEARTION_POSTFIX:
		case OperationType::OPERATION_PREFIX: {
			std::vector<Expression*> args;
			args.push_back(stack.pop());
			expr->set_arguments(args);
			stack.push(new Number(expr->calculate()));
		}
			break;
		case OperationType::OPERATION_BINARY: {
			std::vector<Expression*> args;
			args.push_back(stack.pop());
			args.push_back(stack.pop());
			expr->set_arguments(args);
			stack.push(new Number(expr->calculate()));
		}
			break;
		}
	}
	double result = stack.pop()->calculate();
	for (auto expr : polish) {
		delete expr;
	}
	return result;
}