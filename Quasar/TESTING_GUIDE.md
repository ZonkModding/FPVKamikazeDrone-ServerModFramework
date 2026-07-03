# Тестирование Quasar Framework

## 🧪 Быстрое Тестирование

### Шаг 1: Проверьте что все файлы на месте

```powershell
# Проверяем основные DLL
ls "C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64\*.dll"

# Проверяем модули
ls "C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64\modules\*.dll"
```

Должны быть:
- ✅ QuasarCoreLib.dll
- ✅ version.dll
- ✅ modules\QuasarModulesLib.dll
- ✅ modules\TestModule.dll

### Шаг 2: Запустите сервер

Просто запустите FPVKamikazeDrone Dedicated Server.

### Шаг 3: Проверьте Логи

**Что вы должны видеть:**
```
[ModuleManager] Manager initialized, starting scan...
[ModuleManager] Loading: modules\QuasarModulesLib.dll
[TestModule] Test Module Initialized!
```

**Если видите это - ✅ СИСТЕМА РАБОТАЕТ!**

## 🔍 Отладка

### Проблема: Сервер вылетает

**Решение:**
1. Откройте Event Viewer (Event Log) в Windows
2. Посмотрите System logs
3. Найдите ошибки связанные с DLL
4. Проверьте что все DLL в правильном месте

### Проблема: Модули не загружаются

**Решение:**
1. Проверьте что модули в папке `modules\`
2. Используйте Dependency Walker для проверки зависимостей
3. Убедитесь что модули x64 (не x86)

### Проблема: "Failed to load a module"

**Решение:**
1. Перекомпилируйте модуль
2. Проверьте что функция Init() экспортирована
3. Используйте `Dependency Walker` программу

## 📊 Тестовые Метрики

После успешного запуска:

```
✅ Сервер запускается без крашей
✅ ModuleManager инициализируется
✅ TestModule загружается
✅ Нет ошибок в Event Viewer
✅ Логи выводятся корректно
```

## 🎯 Примеры Модификаций (для продвинутых)

### Модуль 1: Счетчик Загрузок

Отредактируйте `TestModule\dllmain.cpp`:

```cpp
#include <windows.h>

static int loadCount = 0;

extern "C" __declspec(dllexport) void __stdcall Init() {
	loadCount++;
	char msg[256];
	sprintf_s(msg, "Test Module loaded %d times!", loadCount);
	OutputDebugStringA(("[TestModule] " + std::string(msg) + "\n").c_str());
}
```

### Модуль 2: Таймер Активности

```cpp
#include <windows.h>
#include <thread>

void MonitorThread() {
	while (true) {
		OutputDebugStringA("[ActivityMonitor] System is running\n");
		Sleep(10000);  // каждые 10 секунд
	}
}

extern "C" __declspec(dllexport) void __stdcall Init() {
	std::thread(MonitorThread).detach();
}
```

## 🚀 Автоматизированное Тестирование

Используйте скрипт (`build_and_deploy.ps1`):

```powershell
# Скомпилировать и развернуть
.\build_and_deploy.ps1 -Action all

# Только компиляция
.\build_and_deploy.ps1 -Action build

# Только развертывание
.\build_and_deploy.ps1 -Action deploy
```

## ✅ Чек-лист Перед Продакшеном

- [ ] Все DLL скопированы в Win64
- [ ] version.dll переименован правильно
- [ ] modules\ папка содержит QuasarModulesLib.dll
- [ ] Нет никаких ошибок при сборке
- [ ] Сервер запускается без крашей
- [ ] Модули загружаются (видно в логах)
- [ ] Нет ошибок в Event Viewer
- [ ] Тестовые модули работают

## 📝 Логирование Результатов

После запуска сервера, создайте файл с результатами:

```powershell
# Сохраняем информацию о системе
"=== Quasar Framework Test Report ===" | Out-File -FilePath "test_report.txt"
"Date: $(Get-Date)" | Add-Content -FilePath "test_report.txt"
"Files Deployed:" | Add-Content -FilePath "test_report.txt"
Get-ChildItem "C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64" -Filter "*.dll" | Add-Content -FilePath "test_report.txt"
"Modules:" | Add-Content -FilePath "test_report.txt"
Get-ChildItem "C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64\modules" -Filter "*.dll" | Add-Content -FilePath "test_report.txt"
```

---

**Готово к тестированию! Удачи! 🚀**
