#pragma once

#include <string>

class Logger
{
public:
	static void Log(const char* str);
	static void Log(std::string& str);
};