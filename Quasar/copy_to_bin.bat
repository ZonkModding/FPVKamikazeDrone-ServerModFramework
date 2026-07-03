@echo off
REM Copy QuasarCoreLib.dll
copy "x64\Release\QuasarCoreLib.dll" "C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64\" /Y

REM Copy QuasarProxyLib.dll as version.dll
copy "x64\Release\QuasarProxyLib.dll" "C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64\version.dll" /Y

REM Create modules folder if not exists
if not exist "C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64\modules" mkdir "C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64\modules"

REM Copy QuasarModulesLib.dll to modules folder
copy "x64\Release\QuasarModulesLib.dll" "C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64\modules\" /Y

echo Build files copied successfully!
