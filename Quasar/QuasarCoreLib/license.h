#pragma once
#include <string>

namespace License {
    // Добавляем extern "C" для правильного экспорта
    extern "C" __declspec(dllexport) void __stdcall InitializeFramework(const char* apiKey);

    // Внутренние функции
    void InternalInit();
    bool CheckStatus(const std::string& apiKey);
    void StartMonitor(const std::string& apiKey);
}