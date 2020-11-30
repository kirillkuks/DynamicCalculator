#pragma once
#include "operations.h"

#ifdef DLLMINUS_EXPORTS
#define DLLMINUS_API __declspec(dllexport)
#else
#define DLLMINUS_API __declspec(dllimport)
#endif

using namespace operations;

extern "C" DLLMINUS_API Parser * getParser();

struct Minus : BinaryOperation {
	Minus();
	double calculate() override;
	int priority() override;
};

struct MinusParser : Parser {
	MinusParser();
	Expression* parse() override;
};