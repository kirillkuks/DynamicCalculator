#include "share.h"

Parser* getParser() {
	return new ShareParser();
}

Share::Share() {
	left = nullptr;
	right = nullptr;
}

double Share::calculate() {
	return left->calculate() / right->calculate();
}

int Share::priority() {
	return 2;
}

ShareParser::ShareParser() : Parser("/") {}

Expression* ShareParser::parse() {
	return new Share();
}


void Share::print() {
	std::cout << "/" << ' ';
}