#include <windows.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>

// Простой файловый логер
class Logger {
private:
	std::ofstream logFile;

public:
	Logger() {
		std::string logPath = "C:\\SteamLibrary\\steamapps\\common\\FPV Kamikaze Drone Dedicated Server\\FPVKamikazeDrone\\Binaries\\Win64\\modules\\logger_module.log";
		logFile.open(logPath, std::ios::app);
	}

	~Logger() {
		if (logFile.is_open()) {
			logFile.close();
		}
	}

	void Log(const std::string& message) {
		if (logFile.is_open()) {
			auto now = std::chrono::system_clock::now();
			auto time = std::chrono::system_clock::to_time_t(now);
			logFile << "[" << std::ctime(&time) << "] " << message << std::endl;
			logFile.flush();
		}
		OutputDebugStringA(("[LoggerModule] " + message + "\n").c_str());
	}
};

static Logger g_logger;

// Экспортируемая функция инициализации
extern "C" __declspec(dllexport) void __stdcall Init() {
	g_logger.Log("Logger Module Initialized Successfully!");
	g_logger.Log("Module can now log to file and debug output");
}

// DLL Entry Point
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_logger.Log("Logger Module DLL Process Attached");
		break;
	case DLL_PROCESS_DETACH:
		g_logger.Log("Logger Module DLL Process Detached");
		break;
	}
	return TRUE;
}
