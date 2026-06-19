#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include "SDK/Basic.hpp"
#include "SDK/CoreUObject_classes.hpp"
#include "SDK/Engine_classes.hpp"
#include "SDK/FPVKamikazeDrone_classes.hpp"
#include "SDK/BP_PlayerState_classes.hpp"

namespace Global {
    inline HMODULE hModule = nullptr;
    inline bool bRunning = true;
}

DWORD WINAPI MainThread(LPVOID lpReserved);