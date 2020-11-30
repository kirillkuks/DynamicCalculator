#include "operations.h"

namespace operations {
	void Number::print() {
		std::cout << value << ' ';
	}

	void OpenBracket::print() {
		std::cout << "(" << ' ';
	}

	void CloseBracket::print() {
		std::cout << ")" << ' ';
	}

	void Plus::print() {
		std::cout << "+" << ' ';
	}

	void Multy::print() {
		std::cout << "*" << ' ';
	}

	Number::Number(double value_) : value{ value_ } {}

	double Number::calculate() {
		return value;
	}

	int Number::priority() {
		return 0;
	}

	void Number::set_arguments(std::vector<Expression*>& args) {
		return;
	}

	OperationType Number::type() {
		return OperationType::OPERATION_NUMBER;
	}

	OperationType PostfixOperation::type() {
		return OperationType::OPEARTION_POSTFIX;
	}

	void PostfixOperation::set_arguments(std::vector<Expression*>& args) {
		assert(args.size() == 1);
		value = args[0];
	}

	OperationType PrefixOperation::type() {
		return OperationType::OPERATION_PREFIX;
	}

	void PrefixOperation::set_arguments(std::vector<Expression*>& args) {
		assert(args.size() == 1);
		value = args[0];
	}

	OperationType BinaryOperation::type() {
		return OperationType::OPERATION_BINARY;
	}

	void BinaryOperation::set_arguments(std::vector<Expression*>& args) {
		assert(args.size() == 2);
		left = args[1];
		right = args[0];
	}

	double Bracket::calculate() {
		return 0;
	}

	int Bracket::priority() {
		return 0;
	}

	void Bracket::set_arguments(std::vector<Expression*>& args) {
		return;
	}

	OperationType OpenBracket::type() {
		return OperationType::OPERATION_OPENBRACKET;
	}

	OperationType CloseBracket::type() {
		return OperationType::OPERATION_CLOSEBRACKET;
	}

	Plus::Plus() {
		left = nullptr;
		right = nullptr;
	}

	double Plus::calculate() {
		return left->calculate() + right->calculate();
	}

	int Plus::priority() {
		return 1;
	}

	Multy::Multy() {
		left = nullptr;
		right = nullptr;
	}

	double Multy::calculate() {
		return left->calculate() + right->calculate();
	}

	int Multy::priority() {
		return 2;
	}

	Parser::Parser(std::string token_) : token{ token_ } {}

	std::string const& Parser::getLexeme() {
		return token;
	}

	PlusParser::PlusParser() : Parser("+") {}

	Expression* PlusParser::parse() {
		return new Plus();
	}

	MultyParser::MultyParser() : Parser("*") {}

	Expression* MultyParser::parse() {
		return new Multy();
	}
}