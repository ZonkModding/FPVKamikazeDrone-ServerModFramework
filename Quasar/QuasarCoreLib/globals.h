#pragma once
#include <windows.h>
#include <atomic>
#include <string>

namespace Global {
    extern HMODULE hModule;
    extern std::atomic<bool> bRunning;
    extern std::string g_ApiKey;
}