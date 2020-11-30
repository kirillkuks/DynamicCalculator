#include "minus.h"

Parser* getParser() {
	return new MinusParser();
}

Minus::Minus() {
	left = nullptr;
	right = nullptr;
}

double Minus::calculate() {
	return left->calculate() - right->calculate();
}

int Minus::priority() {
	return 1;
}

MinusParser::MinusParser() : Parser("-") {}

Expression* MinusParser::parse() {
	return new Minus();
}