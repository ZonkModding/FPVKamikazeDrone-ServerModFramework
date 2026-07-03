# Создание Модулей для Quasar Framework

## Структура Простого Модуля

Минимальный модуль должен содержать:

### 1. **dllmain.cpp** - основной файл модуля

```cpp
#include <windows.h>

// Обязательная функция инициализации
// Именно эту функцию вызывает ModuleManager при загрузке
extern "C" __declspec(dllexport) void __stdcall Init() {
	// Ваш код инициализации
	OutputDebugStringA("[YourModule] Initialized!\n");
}

// Entry Point DLL
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// Код при подгрузке DLL
		break;
	case DLL_PROCESS_DETACH:
		// Код при выгрузке DLL
		break;
	}
	return TRUE;
}
```

### 2. **framework.h** - заголовок

```cpp
#pragma once

// Экспортируем функцию инициализации
extern "C" __declspec(dllexport) void __stdcall Init();
```

### 3. **.vcxproj** - файл проекта

Скопируйте структуру из **TestModule.vcxproj** (уже готово)

## Как Модули Загружаются

1. **ModuleManager** сканирует папку `modules\`
2. Для каждого `.dll` файла:
   - Загружает DLL через `LoadLibraryW()`
   - Ищет функцию `Init`
   - Вызывает `Init()` если найдена
   - И всё! Модуль готов к использованию

## Требования к Модулю

✅ Должна быть функция: `extern "C" __declspec(dllexport) void __stdcall Init()`

✅ Платформа: **x64**

✅ Инструментарий: **v145** (Visual Studio 2019/2022)

✅ Стандарт C++: **C++20** или выше

## Примеры Функциональности

### Простой Логер

```cpp
extern "C" __declspec(dllexport) void __stdcall Init() {
	MessageBoxA(NULL, "My Module Loaded!", "Success", MB_OK);
}
```

### Функция Обратного Вызова (Callback)

```cpp
typedef void(__stdcall* LogFunction)(const char* message);

LogFunction g_pfnLog = nullptr;

extern "C" __declspec(dllexport) void __stdcall Init() {
	if (g_pfnLog) {
		g_pfnLog("[MyModule] Hello from module!");
	}
}

extern "C" __declspec(dllexport) void __stdcall SetLogFunction(LogFunction pfn) {
	g_pfnLog = pfn;
}
```

### Периодическая Задача

```cpp
#include <thread>
#include <atomic>

std::atomic<bool> g_bRunning = true;

void TaskThread() {
	while (g_bRunning) {
		// Ваша логика
		Sleep(1000);
	}
}

extern "C" __declspec(dllexport) void __stdcall Init() {
	std::thread(TaskThread).detach();
}
```

## Как Использовать TestModule

1. ✅ TestModule.dll уже скомпилирован и находится в `modules\`
2. При запуске сервера вы должны увидеть в логах: `[TestModule] Test Module Initialized!`
3. Это подтверждает что система загрузки модулей работает!

## Как Создать Свой Модуль

1. Скопируйте папку `TestModule` → `MyModule`
2. Переименуйте `TestModule.vcxproj` → `MyModule.vcxproj`
3. Отредактируйте содержимое:
   - В `MyModule.vcxproj`: измените `<RootNamespace>` и `<ProjectGuid>` на уникальные значения
   - В `dllmain.cpp`: напишите вашу логику
4. Скомпилируйте через MSBuild или Visual Studio
5. Скопируйте `MyModule.dll` в папку `modules\`
6. Перезапустите сервер

## Команда Компиляции

```powershell
cd MyModule
msbuild MyModule.vcxproj /p:Configuration=Release /p:Platform=x64
Copy-Item "x64\Release\MyModule.dll" "C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64\modules\"
```

## Отладка

Если модуль не загружается:
1. Проверьте что файл находится в папке `modules\`
2. Убедитесь что это результат компиляции x64 Release
3. Используйте `Dependency Walker` для проверки зависимостей
4. Проверьте Event Viewer в Windows на ошибки

---

**Теперь у вас есть рабочий TestModule! Запустите сервер и проверьте логи!** 🚀
