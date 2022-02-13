#include "Logger.h"
#include <iostream>

void Logger::Log(const char* str)
{
	std::cout << str << std::endl;
}

void Logger::Log(std::string& str)
{
	std::cout << str << std::endl;
}