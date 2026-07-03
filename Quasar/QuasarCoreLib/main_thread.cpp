#include "main.h"
#include "globals.h"
#include "license.h"
#include "console.h"
#include <windows.h>
#include <thread>
#include <chrono>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;



void SetupEnvironment() {
    try {
        Sleep(500);

        char dllPath[MAX_PATH] = { 0 };

        // Проверяем что hModule не NULL
        if (!Global::hModule) {
            return;
        }

        GetModuleFileNameA(Global::hModule, dllPath, MAX_PATH);
        std::string path(dllPath);

        size_t pos = path.find_last_of("\\/");
        if (pos != std::string::npos) {
            path = path.substr(0, pos);
        }

        std::string configDir = path + "\\config";
        std::string iniPath = configDir + "\\settings.ini";

        if (!fs::exists(configDir)) {
            try {
                fs::create_directory(configDir);
            } catch (...) {
            }
        }

        if (!fs::exists("modules")) {
            try {
                fs::create_directory("modules");
            } catch (...) {
            }
        }

        // Создаем конфиг если не существует
        if (!fs::exists(iniPath)) {
            WritePrivateProfileStringA("License", "ApiKey", "DEFAULT_KEY", iniPath.c_str());
            WritePrivateProfileStringA("Settings", "Console", "1", iniPath.c_str());
        }

        char apiKey[256] = { 0 };
        GetPrivateProfileStringA("License", "ApiKey", "NONE", apiKey, sizeof(apiKey), iniPath.c_str());

        Global::g_ApiKey = std::string(apiKey);
    }
    catch (...) {
        // Ошибка при инициализации - продолжаем нормально
    }
}

void LoadModuleManager() {
    try {
        std::wstring managerPath = L"modules\\QuasarModulesLib.dll";
        if (fs::exists(managerPath)) {
            HMODULE hManager = LoadLibraryW(managerPath.c_str());
            if (hManager) {
                typedef void(__stdcall* ManagerInit)();
                ManagerInit init = (ManagerInit)GetProcAddress(hManager, "Init");
                if (init) {
                    init();
                }
            }
        }
    }
    catch (...) {
        // Ошибка при загрузке модулей - игнорируем
    }
}

DWORD WINAPI MainThread(LPVOID lpReserved) {
    // 1. Создаем консоль СРАЗУ
    try {
        CreateConsole();
    } catch (...) {
        // Если ошибка при создании консоли, продолжаем без нее
    }

    // 2. Базовая инициализация (без сложных операций)
    try {
        SetupEnvironment();
    } catch (...) {
        // Ошибка при инициализации
    }

    // 3. Инициализируем фреймворк (без проверок)
    try {
        License::InitializeFramework(Global::g_ApiKey.c_str());
    } catch (...) {
        // Ошибка при инициализации
    }

    // 4. Попытка загрузить модули (некритично если не удастся)
    try {
        LoadModuleManager();
    } catch (...) {
        // Ошибка при загрузке модулей - не критично
    }

    // 5. Главный цикл
    while (Global::bRunning) {
        if (GetAsyncKeyState(VK_END) & 1) {
            Global::bRunning = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // 6. Закрываем консоль (без логирования)
    try {
        FreeConsole();
    } catch (...) {
    }

    FreeLibraryAndExitThread((HMODULE)lpReserved, 0);
    return TRUE;
}




//#include "main.h"
//#include "globals.h"
//#include <windows.h>
//#include "license.h"
//#include "console.h"
//#include "globals.h" // Только здесь, внутри ядра!
//#include <thread>
//#include <chrono>
//#include <filesystem>
//#include <string>
//
//namespace fs = std::filesystem;
//
//namespace Global {
//    extern HMODULE hModule;
//    extern std::atomic<bool> bRunning;
//    extern std::string g_ApiKey;
//}
//
//extern HMODULE hModule;
//
//void SetupEnvironment() {
//    char dllPath[MAX_PATH];
//    // Используй Global::hModule, так как он инициализируется в dllmain.cpp
//    GetModuleFileNameA(Global::hModule, dllPath, MAX_PATH);
//    // ... остальной код
//    std::string path(dllPath);
//    path = path.substr(0, path.find_last_of("\\/"));
//
//    std::string configDir = path + "\\config";
//    std::string iniPath = configDir + "\\settings.ini";
//
//    if (!fs::exists(configDir)) fs::create_directory(configDir);
//    if (!fs::exists("modules")) fs::create_directory("modules");
//
//    if (!fs::exists(iniPath)) {
//        WritePrivateProfileStringA("License", "ApiKey", "DEFAULT_KEY", iniPath.c_str());
//        WritePrivateProfileStringA("Settings", "Console", "1", iniPath.c_str());
//    }
//
//    // Читаем ключ, используя АБСОЛЮТНЫЙ путь
//    char apiKey[256] = { 0 };
//    GetPrivateProfileStringA("License", "ApiKey", "NONE", apiKey, sizeof(apiKey), iniPath.c_str());
//
//    Global::g_ApiKey = std::string(apiKey);
//
//    // ЛОГ ДЛЯ ОТЛАДКИ (смотри в свою консоль!)
//    std::cout << "[DEBUG] INI Path: " << iniPath << std::endl;
//    std::cout << "[DEBUG] Loaded Key: " << Global::g_ApiKey << std::endl;
//}
//
//void LoadModuleManager() {
//    std::wstring managerPath = L"modules\\QuasarModulesLib.dll";
//    if (fs::exists(managerPath)) {
//        HMODULE hManager = LoadLibraryW(managerPath.c_str());
//        if (hManager) {
//            typedef void(__stdcall* ManagerInit)();
//            ManagerInit init = (ManagerInit)GetProcAddress(hManager, "Init");
//            if (init) init();
//        }
//    }
//}
//
//DWORD WINAPI MainThread(LPVOID lpReserved) {
//    std::this_thread::sleep_for(std::chrono::seconds(2));
//
//    SetupEnvironment(); // Заполняет Global::g_ApiKey
//    CreateConsole();
//
//    void __stdcall InitializeFramework(const char* apiKey = "");
//
//    // Теперь используем переменную из глобального пространства
//    License::StartMonitor(Global::g_ApiKey);
//
//    LoadModuleManager();
//
//    while (Global::bRunning) {
//        if (GetAsyncKeyState(VK_END) & 1) {
//            Global::bRunning = false;
//        }
//        std::this_thread::sleep_for(std::chrono::milliseconds(500));
//    }
//
//    CloseConsole();
//    FreeLibraryAndExitThread((HMODULE)lpReserved, 0);
//    return TRUE;
//}