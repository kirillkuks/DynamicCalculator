#include "cosinus.h"

Parser* getParser() {
	return new CosinusParser();
}

Cosinus::Cosinus() {
	value = nullptr;
}

double Cosinus::calculate() {
	return cos(value->calculate());
}

int Cosinus::priority() {
	return 3;
}

CosinusParser::CosinusParser() : Parser("cos") {}

Expression* CosinusParser::parse() {
	return new Cosinus();
}

void Cosinus::print() {
	std::cout << "cos" << ' ';
}