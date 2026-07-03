#include "main.h"

extern "C" __declspec(dllexport) void SetModuleHandle(HMODULE hMod) {
    Global::hModule = hMod;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        Global::hModule = hModule;
        CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);



    }
    return TRUE;
}