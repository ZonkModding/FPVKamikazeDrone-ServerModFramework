#include <windows.h>
#include <iostream>
#include <fstream>

// Простой логер для модулей
void ModuleLog(const char* message) {
	// Выводим в Debug Output
	OutputDebugStringA("[TestModule] ");
	OutputDebugStringA(message);
	OutputDebugStringA("\n");

	// Также пишем в консоль если она есть
	std::cout << "[TestModule] " << message << std::endl;

	// И пишем в файл
	try {
		std::ofstream logFile("C:\\Temp\\TestModule.log", std::ios::app);
		if (logFile.is_open()) {
			logFile << "[TestModule] " << message << std::endl;
			logFile.close();
		}
	} catch (...) {
		// Игнорируем ошибки файла
	}
}

// Основная функция инициализации модуля
// Именно эту функцию ищет QuasarModulesLib::LoadModule()
extern "C" __declspec(dllexport) void __stdcall Init() {
	ModuleLog("===== TEST MODULE INITIALIZING =====");
	ModuleLog("Test Module Initialized Successfully!");
	ModuleLog("This is a simple test module for the Quasar Framework");
	ModuleLog("If you see this - module is working!");
	ModuleLog("===== TEST MODULE READY ====");
}

// DLL Entry Point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModuleLog("Test Module DLL attached");
		break;
	case DLL_PROCESS_DETACH:
		ModuleLog("Test Module DLL detached");
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}
