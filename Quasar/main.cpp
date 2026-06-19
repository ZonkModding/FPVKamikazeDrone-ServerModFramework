#include "main.h"
#include "modules/user/user.h"
#include "modules/net/net.h"
#include "modules/spawnobjects/spawnobjects.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        Global::hModule = hModule;
        HANDLE hThread = CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
        if (hThread) CloseHandle(hThread);
    }
    return TRUE;
}

void CreateConsole() {
    if (AllocConsole()) {
        FILE* f;
        freopen_s(&f, "CONOUT$", "w", stdout);
        freopen_s(&f, "CONIN$", "r", stdin);
        SetConsoleTitleA("Quasar Debug Console");
    }
}

DWORD WINAPI MainThread(LPVOID lpReserved) {
    std::this_thread::sleep_for(std::chrono::seconds(3));

    CreateConsole();
    std::cout << "[QuasarServer] Thread Init!" << std::endl;
    std::cout << "[QuasarServer] Thread Started!" << std::endl;

    while (Global::bRunning) {
        if (GetAsyncKeyState(VK_END) & 1) {
            Global::bRunning = false;
            break;
        }

        __try {
            Modules::User::Update();
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {

        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "[QuasarServer] Shutting down.." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    FreeConsole();
    FreeLibraryAndExitThread((HMODULE)lpReserved, 0);
    return TRUE;
}