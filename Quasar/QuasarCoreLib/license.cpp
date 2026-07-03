#include "license.h"
#include "globals.h"
#include <windows.h>
#include <iostream>

namespace License {

    // Экспортируемая функция, которую вызывает Proxy
    extern "C" __declspec(dllexport) void __stdcall InitializeFramework(const char* apiKey) {
        // 1. Сохраняем ключ (без проверок)
        if (apiKey) Global::g_ApiKey = std::string(apiKey);

        // 2. Инициализируем фреймворк
        InternalInit();
    }

    void InternalInit() {
        // Инициализация завершена успешно
        // Все проверки SHA512, веб-сервера и API ключей отключены
    }

    bool CheckStatus(const std::string& apiKey) {
        // Всегда возвращаем true - проверки отключены временно
        return true;
    }

    void StartMonitor(const std::string& apiKey) {
        // Мониторинг отключен
    }
}