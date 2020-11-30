#pragma once
#include "operations.h"
#include <cmath>

#ifdef DLLCOSINUS_EXPORTS
#define DLLCOSINUS_API __declspec(dllexport)
#else
#define DLLCOSINUS_API __declspec(dllimport)
#endif

using namespace operations;

extern "C" DLLCOSINUS_API Parser * getParser();

struct Cosinus : PrefixOperation {
	Cosinus();
	double calculate() override;
	int priority() override;

	void print() override;
};

struct CosinusParser : Parser {
	CosinusParser();
	Expression* parse() override;
};