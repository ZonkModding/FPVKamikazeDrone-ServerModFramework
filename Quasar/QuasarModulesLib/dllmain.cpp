#include <windows.h>
#include <string>
#include <vector>
#include <filesystem>
#include "console.h" // Убедись, что этот файл в проекте

namespace fs = std::filesystem;
typedef void(__stdcall* ModuleInit)();

// Объявление функции, чтобы компилятор не ругался (forward declaration)
void InitializeModules(const std::string& path);

// Экспорт для лоадера
extern "C" __declspec(dllexport) void __stdcall Init() {
    Log("ModuleManager", "Manager initialized, starting scan...", LogLevel::Info);

    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    InitializeModules(std::string(buffer));
}

void InitializeModules(const std::string& path) {
    std::string modulesPath = path + "\\modules";

    if (!fs::exists(modulesPath)) {
        Log("ModuleManager", "Modules folder not found!", LogLevel::Error);
        return;
    }

    for (const auto& entry : fs::recursive_directory_iterator(modulesPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".dll") {

            // Важно: не грузить самого себя бесконечно
            if (entry.path().filename() == "QuasarModulesLib.dll") continue;

            Log("ModuleManager", ("Loading: " + entry.path().string()).c_str(), LogLevel::Info);
            HMODULE hMod = LoadLibraryW(entry.path().c_str());

            if (hMod) {
                ModuleInit init = (ModuleInit)GetProcAddress(hMod, "Init");
                if (init) {
                    init(); // Инициализируем найденный модуль
                }
            }
            else {
                Log("ModuleManager", "Failed to load a module.", LogLevel::Warning);
            }
        }
    }
}