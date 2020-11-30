#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <cassert>

namespace operations {
	enum class OperationType {
		OPERATION_NUMBER,
		OPEARTION_POSTFIX,
		OPERATION_PREFIX,
		OPERATION_BINARY,
		OPERATION_OPENBRACKET,
		OPERATION_CLOSEBRACKET
	};

	struct Expression {
		virtual double calculate() = 0;
		virtual int priority() = 0;
		virtual OperationType type() = 0;
		virtual void set_arguments(std::vector<Expression*>&) = 0;
	};

	struct Number : Expression {
		Number(double);
		double calculate() override;
		int priority() override;
		OperationType type() override;
		void set_arguments(std::vector<Expression*>&) override;
	private:
		double value;
	};

	struct PostfixOperation : Expression {
		virtual double calculate() = 0;
		virtual int priority() = 0;
		OperationType type() override;
		virtual void set_arguments(std::vector<Expression*>&) override;
	protected:
		Expression* value;
	};

	struct PrefixOperation : Expression {
		virtual double calculate() = 0;
		virtual int priority() = 0;
		OperationType type() override;
		virtual void set_arguments(std::vector<Expression*>&) override;
	protected:
		Expression* value;
	};

	struct BinaryOperation : Expression {
		virtual double calculate() = 0;
		virtual int priority() = 0;
		OperationType type() override;
		virtual void set_arguments(std::vector<Expression*>&) override;
	protected:
		Expression* left;
		Expression* right;
	};

	struct Bracket : Expression {
		double calculate() override;
		int priority() override;
		virtual OperationType type() = 0;
		void set_arguments(std::vector<Expression*>&) override;
	};

	struct OpenBracket : Bracket {
		OperationType type() override;
	};

	struct CloseBracket : Bracket {
		OperationType type() override;
	};

	struct Plus : BinaryOperation {
		Plus();
		double calculate() override;
		int priority() override;
	};

	struct Multy : BinaryOperation {
		Multy();
		double calculate() override;
		int priority() override;
	};

	struct Parser {
		Parser(std::string);
		virtual Expression* parse() = 0;
		virtual std::string const& getLexeme();
	protected:
		std::string token;
	};

	struct PlusParser : Parser {
		PlusParser();
		Expression* parse() override;
	};

	struct MultyParser : Parser {
		MultyParser();
		Expression* parse() override;
	};
}