#include "globals.h"

namespace Global {
    HMODULE hModule = nullptr;
    std::atomic<bool> bRunning{ true };
    std::string g_ApiKey = "";
}