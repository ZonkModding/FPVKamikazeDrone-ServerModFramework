#pragma once
#include <windows.h>
#include <cstdio>
#include <iostream>
#include <string>

enum class LogLevel {
	Info = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	Warning = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	Error = FOREGROUND_RED | FOREGROUND_INTENSITY
};

inline void Log(const std::string& moduleName, const std::string& message, LogLevel level = LogLevel::Info) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(level));

	std::cout << "[" << moduleName << "] " << message << std::endl;

	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
