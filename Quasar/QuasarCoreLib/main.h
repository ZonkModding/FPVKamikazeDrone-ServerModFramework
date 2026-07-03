#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>
#include <vector>
#include <string>

namespace Global {
    extern HMODULE hModule;
    extern std::atomic<bool> bRunning;
}

DWORD WINAPI MainThread(LPVOID lpReserved);