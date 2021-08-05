#include <iostream>

#include "IniConfig.h"

int main(int argc, char* argv[])
{
	IniConfig config("example.ini");
	std::string variable = config.GetVariable("some_variable").AsString();

	std::cout << variable << std::endl; // prints: 100
	return 0;
}