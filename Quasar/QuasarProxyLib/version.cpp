#include <windows.h>
#include <string>

HMODULE hCoreModule = nullptr;

DWORD WINAPI LoadCoreThread(LPVOID lpParam) {
    try {
        Sleep(2000);

        // Получаем путь к текущему модулю
        char dllPath[MAX_PATH] = { 0 };
        GetModuleFileNameA((HMODULE)lpParam, dllPath, MAX_PATH);

        // Получаем директорию
        std::string path(dllPath);
        size_t pos = path.find_last_of("\\/");
        if (pos != std::string::npos) {
            path = path.substr(0, pos);
        }

        std::string corePath = path + "\\QuasarCoreLib.dll";

        // Пытаемся загрузить Core Library
        hCoreModule = LoadLibraryA(corePath.c_str());

        if (!hCoreModule) {
            // Не удалось загрузить - просто выходим
            return 1;
        }

        // Передача хендла
        typedef void(__stdcall* SetModuleHandleFn)(HMODULE);
        SetModuleHandleFn setHandle = (SetModuleHandleFn)GetProcAddress(hCoreModule, "SetModuleHandle");
        if (setHandle) {
            setHandle((HMODULE)lpParam);
        }

        // Инициализация
        typedef void(__stdcall* CoreInit)(const char*);
        CoreInit init = (CoreInit)GetProcAddress(hCoreModule, "InitializeFramework");

        if (init) {
            init(nullptr);  // Передаем nullptr вместо API ключа
        }
    }
    catch (...) {
        // Обработка любых исключений
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);

        HANDLE hThread = CreateThread(nullptr, 0, LoadCoreThread, hModule, 0, nullptr);
        if (hThread) {
            CloseHandle(hThread);
        }
    }
    else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
        if (hCoreModule) {
            FreeLibrary(hCoreModule);
            hCoreModule = nullptr;
        }
    }
    return TRUE;
}