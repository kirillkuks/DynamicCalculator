#pragma once
#include "operations.h"

#ifdef DLLSHARE_EXPORTS
#define DLLMINUS_API __declspec(dllexport)
#else
#define DLLMINUS_API __declspec(dllimport)
#endif

using namespace operations;

extern "C" DLLMINUS_API Parser * getParser();

struct Share : BinaryOperation {
	Share();
	double calculate() override;
	int priority() override;

	void print() override;
};

struct ShareParser : Parser {
	ShareParser();
	Expression* parse() override;
};