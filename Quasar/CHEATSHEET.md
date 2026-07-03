# 📖 БЫСТРАЯ ШПАРГАЛКА - Quasar Framework

## ✅ Система Полностью Настроена!

```
Статус: ✅ РАБОТАЕТ И ГОТОВА К ИСПОЛЬЗОВАНИЮ
Дата: 03.07.2026
Версия: 1.0
```

## 🎯 Основные Компоненты

| Компонент | Файл | Расположение | Статус |
|-----------|------|--------------|--------|
| Core Framework | QuasarCoreLib.dll | `Win64\` | ✅ |
| Loader | version.dll | `Win64\` | ✅ |
| Module Manager | QuasarModulesLib.dll | `Win64\modules\` | ✅ |
| Test Module | TestModule.dll | `Win64\modules\` | ✅ |

## 🚀 Быстрые Команды

### Компиляция
```powershell
# Всё сразу (build + deploy)
.\build_and_deploy.ps1 -Action all

# Только компиляция
msbuild
```

### Развертывание  
```powershell
$t="C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64"
cp "x64\Release\QuasarCoreLib.dll" $t
cp "x64\Release\QuasarProxyLib.dll" "$t\version.dll"
cp "x64\Release\QuasarModulesLib.dll" "$t\modules\"
```

### Проверка
```powershell
ls "$t\*.dll"
ls "$t\modules\*.dll"
```

## 📚 Документация

| Файл | Назначение |
|------|-----------|
| **README_FINAL.md** | Полное резюме (ЧИТАЙТЕ ПЕРВЫМ) |
| **QUICK_MODULE_GUIDE.md** | Быстрый старт для новых модулей |
| **MODULE_CREATION_GUIDE.md** | Подробное руководство |
| **TESTING_GUIDE.md** | Тестирование и отладка |
| **CHANGES_SUMMARY.md** | Что было изменено в коде |

## 🧪 Создание Модуля (30 сек)

```powershell
# 1. Скопируем TestModule
Copy-Item -Recurse "TestModule" "MyModule"

# 2. Отредактируем dllmain.cpp
code MyModule\dllmain.cpp

# 3. Скомпилируем
msbuild "MyModule\MyModule.vcxproj" /p:Configuration=Release /p:Platform=x64

# 4. Развернем
$dest = "C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64\modules\"
cp "MyModule\x64\Release\MyModule.dll" $dest
```

## 📋 Минимальный Модуль

```cpp
// dllmain.cpp
#include <windows.h>

extern "C" __declspec(dllexport) void __stdcall Init() {
	OutputDebugStringA("[MyModule] Hello!\n");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	return TRUE;
}
```

## ⚡ Структура Папок

```
D:\progects\Quasar_New\Quasar\
├── QuasarCoreLib\      ← основной код (исправлено)
├── QuasarProxyLib\     ← загрузчик (исправлено)
├── QuasarModulesLib\   ← менеджер (добавлено console.h)
├── TestModule\         ← пример модуля для копирования
├── build_and_deploy.ps1 ← автоматизация
├── README_FINAL.md     ← общая информация
├── QUICK_MODULE_GUIDE.md ← быстрый старт
├── MODULE_CREATION_GUIDE.md ← подробно
├── TESTING_GUIDE.md    ← тесты
└── CHANGES_SUMMARY.md  ← что изменилось
```

## 🔧 Требования К Модулям

✅ Обязательна функция **Init()** с экспортом
✅ Только **x64** (не x86)
✅ Использовать **__stdcall** соглашение
✅ Находятся в папке **/modules/**
✅ Расширение только **.dll**

## ❌ Если Что-то Не Работает

| Проблема | Решение |
|----------|---------|
| Сервер вылетает | Проверьте Event Viewer (Windows) |
| Модули не загружаются | Убедитесь что они в `modules\` папке |
| "Init not found" | Добавьте `extern "C" __declspec(dllexport)` |
| x86 ошибка | Скомпилируйте только x64 |

## 📊 Проверка Развертывания

```powershell
$t = "C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64"

Write-Host "Main DLLs:" -ForegroundColor Green
Get-ChildItem $t -Filter "*.dll" -Depth 0

Write-Host "Modules:" -ForegroundColor Green  
Get-ChildItem "$t\modules" -Filter "*.dll"
```

## 🎓 Примеры Функциональности

### Пример 1: Простое Логирование
```cpp
extern "C" __declspec(dllexport) void __stdcall Init() {
	OutputDebugStringA("[MyModule] Initialized\n");
}
```

### Пример 2: С Параметрами
```cpp
static int counter = 0;

extern "C" __declspec(dllexport) int __stdcall GetCounter() {
	return ++counter;
}

extern "C" __declspec(dllexport) void __stdcall Init() {
	OutputDebugStringA("[MyModule] Ready\n");
}
```

### Пример 3: С Потоком
```cpp
#include <thread>

void WorkerProcess() {
	while (true) {
		Sleep(5000);
		OutputDebugStringA("[Worker] Running\n");
	}
}

extern "C" __declspec(dllexport) void __stdcall Init() {
	std::thread(WorkerProcess).detach();
}
```

## 🎯 Типичный Сценарий Разработки

```
1. Создам новый модуль (копирую TestModule)
   ↓
2. Пишу функциональность в dllmain.cpp
   ↓  
3. Компилирую (мне нужна Release x64)
   ↓
4. Копирую DLL в C:\...\modules\
   ↓
5. Перезапускаю сервер
   ↓
6. Проверяю логи
   ↓
7. ✅ Готово!
```

## 💾 Постоянная Ссылка На Версию

**Stable Version:** v1.0 | **Date:** 03.07.2026 | **Status:** ✅ PRODUCTION READY

---

## 📞 Нужна Помощь?

1. Прочитайте **README_FINAL.md** - общая информация
2. Посмотрите **QUICK_MODULE_GUIDE.md** - быстрый старт
3. Перейдите на **MODULE_CREATION_GUIDE.md** - подробно
4. Используйте **TESTING_GUIDE.md** - отладка

**Система готова! Начинайте разработку modов! 🚀**
