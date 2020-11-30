#include "calculator.h"
#include <Windows.h>
#include <filesystem>
#include <string>
#include <iostream>

namespace fs = std::filesystem;

using namespace operations;

int main(int argc, char* argv[]) {
	std::vector<HMODULE> libs;
	std::vector<Parser*> parsers;
	std::string path = "D:\\Kuksenko\\Cpp\\5 семестр\\Calc\\DynamicCalc\\Debug\\Plugins";

	for (auto const& entry : fs::directory_iterator(path)) {
		HMODULE hLib = LoadLibrary(entry.path().c_str());
		if (hLib) {
			libs.push_back(hLib);
		}
	}

	parsers.push_back(new PlusParser());
	parsers.push_back(new MultyParser());

	for (HMODULE hLib : libs) {
		Parser* (*pFunc)();
		(FARPROC&)pFunc = GetProcAddress(hLib, "getParser");
		Parser* parser = pFunc();
		parsers.push_back(parser);
	}

	Calculator calculator(parsers);

	double result = calculator.calculate("12+43*cos(2+2*2)-123");
	std::cout << "Result: " << result << '\n';

	for (auto parser : parsers) {
		delete parser;
	}

	for (HMODULE hLib : libs) {
		FreeLibrary(hLib);
	}
	return 0;
}