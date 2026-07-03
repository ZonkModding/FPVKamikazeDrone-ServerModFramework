# Инструкция: Создание Модулей для Quasar Framework

## ✅ Что уже готово:

1. **TestModule.dll** - тестовый модуль (находится в папке `modules\`)
2. **Структура для создания новых модулей** - готовая папка `TestModule\` в проекте

## 📋 Как Создать Свой Модуль (Метод 1 - Через Копирование)

### Шаг 1: Скопируйте TestModule

```powershell
Copy-Item -Path "TestModule" -Destination "MyModule" -Recurse
```

### Шаг 2: Переименуйте файлы

```powershell
cd MyModule
Rename-Item -Path "TestModule.vcxproj" -NewName "MyModule.vcxproj"
```

### Шаг 3: Отредактируйте файлы

**Файл: MyModule.vcxproj**
- Найдите `<RootNamespace>TestModule</RootNamespace>` 
- Замените на `<RootNamespace>MyModule</RootNamespace>`
- Найдите `<ProjectGuid>{a1b2c3d4-e5f6-4789-a0b1-c2d3e4f5a6b7}</ProjectGuid>`
- Замените на уникальный GUID (придумайте любой через онлайн генератор GUID)

**Файл: dllmain.cpp**
- Отредактируйте функцию `Init()` со своей логикой

### Шаг 4: Скомпилируйте

```powershell
msbuild "MyModule\MyModule.vcxproj" /p:Configuration=Release /p:Platform=x64
```

### Шаг 5: Скопируйте DLL в папку modules

```powershell
$source = "MyModule\x64\Release\MyModule.dll"
$dest = "C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64\modules\"
Copy-Item $source $dest -Force
```

## 🔧 Как Создать Свой Модуль (Метод 2 - С Нуля в Visual Studio)

### Шаг 1: Создайте новый проект
- **Тип:** Dynamic Library (DLL)
- **Язык:** C++
- **Платформа:** x64 только
- **Имя:** YourModuleName

### Шаг 2: Замените содержимое dllmain.cpp на:

```cpp
#include <windows.h>
#include <iostream>

extern "C" __declspec(dllexport) void __stdcall Init() {
	OutputDebugStringA("[YourModule] Module Initialized!\n");
	MessageBoxA(NULL, "Your Module Loaded!", "Success", MB_OK);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		// Ваш код при загрузке
	}
	return TRUE;
}
```

### Шаг 3: Установите свойства проекта
- **Configuration:** Release
- **Platform:** x64
- **Language Standard:** C++20
- **Character Set:** Unicode

### Шаг 4: Скомпилируйте (Ctrl+Shift+B)

### Шаг 5: Скопируйте DLL в `modules\` папку

## 📦 Текущие Модули в Системе

```
C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\
FPVKamikazeDrone\Binaries\Win64\modules\
├── QuasarModulesLib.dll  (основной загрузчик модулей)
└── TestModule.dll        (тестовый модуль)
```

## 🧪 Как Тестировать Свой Модуль

1. Скопируйте `YourModule.dll` в папку `modules\`
2. Перезапустите сервер
3. Проверьте:
   - Debug Output в Visual Studio (если отладка запущена)
   - Event Viewer в Windows (Система)
   - Логи сервера (если есть)

## ⚡ Примеры Функциональности

### Пример 1: Простой Вывод

```cpp
extern "C" __declspec(dllexport) void __stdcall Init() {
	OutputDebugStringA("[MyModule] Hello World!\n");
}
```

### Пример 2: С Параметрами

```cpp
#include <iostream>

int counter = 0;

extern "C" __declspec(dllexport) void __stdcall Init() {
	counter++;
	char buffer[256];
	sprintf_s(buffer, sizeof(buffer), "[MyModule] Module initialized %d times\n", counter);
	OutputDebugStringA(buffer);
}

extern "C" __declspec(dllexport) int __stdcall GetCounter() {
	return counter;
}
```

### Пример 3: С Потоком

```cpp
#include <thread>
#include <atomic>

std::atomic<bool> running = true;

void WorkerThread() {
	while (running) {
		OutputDebugStringA("[MyModule] Working...\n");
		Sleep(5000);  // каждые 5 секунд
	}
}

extern "C" __declspec(dllexport) void __stdcall Init() {
	std::thread(WorkerThread).detach();
}
```

## ❌ Типичные Ошибки

| Ошибка | Решение |
|--------|---------|
| Модуль не загружается | Проверьте что он x64, не x86 |
| "Failed to load a module" | Пересчитайте зависимости (Dependency Walker) |
| Нет функции Init | Убедитесь что функция экспортирована с `__stdcall` |
| Крах при запуске модуля | Добавьте try-catch в Init() |

## 📚 Больше Информации

Смотрите **MODULE_CREATION_GUIDE.md** для подробного руководства.

---

**Готово! Теперь вы можете создавать свои модули для Quasar Framework!** 🚀
