#!/usr/bin/env powershell
# Build and Deploy Script for Quasar Framework
# Скрипт для компиляции и развертывания модулей

param(
	[ValidateSet("build", "deploy", "rebuild", "all")]
	[string]$Action = "all"
)

$ErrorActionPreference = "Stop"

# Пути
$TARGET_DIR = "C:\SteamLibrary\steamapps\common\FPV Kamikaze Drone Dedicated Server\FPVKamikazeDrone\Binaries\Win64"
$MODULES_DIR = "$TARGET_DIR\modules"

Write-Host "========== Quasar Framework Build Script ==========" -ForegroundColor Cyan

# Функция компиляции
function Build-Projects {
	Write-Host "`nBuilding projects..." -ForegroundColor Yellow

	$projects = @(
		"QuasarCoreLib\QuasarCoreLib.vcxproj",
		"QuasarProxyLib\Quasar.vcxproj",
		"QuasarModulesLib\QuasarModulesLib.vcxproj"
	)

	foreach ($project in $projects) {
		Write-Host "Building: $project" -ForegroundColor Cyan
		msbuild $project /p:Configuration=Release /p:Platform=x64 /v:minimal
		if ($LASTEXITCODE -ne 0) {
			Write-Host "❌ Build failed for $project" -ForegroundColor Red
			return $false
		}
	}

	Write-Host "✅ All projects built successfully!" -ForegroundColor Green
	return $true
}

# Функция развертывания
function Deploy-Files {
	Write-Host "`nDeploying files..." -ForegroundColor Yellow

	# Проверяем целевую папку
	if (-not (Test-Path $TARGET_DIR)) {
		Write-Host "❌ Target directory not found: $TARGET_DIR" -ForegroundColor Red
		return $false
	}

	# Создаем папку modules если не существует
	if (-not (Test-Path $MODULES_DIR)) {
		New-Item -ItemType Directory -Path $MODULES_DIR -Force | Out-Null
		Write-Host "Created modules directory: $MODULES_DIR" -ForegroundColor Cyan
	}

	# Копируем основные DLL
	$files = @(
		@{src = "x64\Release\QuasarCoreLib.dll"; dest = "$TARGET_DIR\QuasarCoreLib.dll"},
		@{src = "x64\Release\QuasarProxyLib.dll"; dest = "$TARGET_DIR\version.dll"},
		@{src = "x64\Release\QuasarModulesLib.dll"; dest = "$MODULES_DIR\QuasarModulesLib.dll"}
	)

	foreach ($file in $files) {
		if (Test-Path $file.src) {
			Copy-Item $file.src $file.dest -Force
			Write-Host "✅ Deployed: $(Split-Path $file.dest -Leaf)" -ForegroundColor Green
		} else {
			Write-Host "❌ Source not found: $($file.src)" -ForegroundColor Red
			return $false
		}
	}

	# Копируем доступные модули
	$moduleFiles = Get-ChildItem "TestModule\x64\Release\*.dll" -ErrorAction SilentlyContinue
	foreach ($module in $moduleFiles) {
		Copy-Item $module.FullName "$MODULES_DIR\" -Force
		Write-Host "✅ Module deployed: $($module.Name)" -ForegroundColor Green
	}

	Write-Host "`n✅ Deployment completed!" -ForegroundColor Green
	return $true
}

# Функция проверки развертывания
function Verify-Deployment {
	Write-Host "`nVerifying deployment..." -ForegroundColor Yellow

	Write-Host "Files in Win64:" -ForegroundColor Cyan
	Get-ChildItem $TARGET_DIR -Filter "*.dll" -Depth 0 | Select-Object Name, @{n="Size(KB)";e={[math]::Round($_.Length/1KB,2)}}

	Write-Host "`nModules:" -ForegroundColor Cyan
	Get-ChildItem $MODULES_DIR -Filter "*.dll" | Select-Object Name, @{n="Size(KB)";e={[math]::Round($_.Length/1KB,2)}}

	Write-Host "`n✅ Verification complete!" -ForegroundColor Green
}

# Главная логика
try {
	switch ($Action) {
		"build" {
			Build-Projects
		}
		"deploy" {
			Deploy-Files
			Verify-Deployment
		}
		"rebuild" {
			Build-Projects
			Deploy-Files
			Verify-Deployment
		}
		"all" {
			Build-Projects
			Deploy-Files
			Verify-Deployment
		}
	}

	Write-Host "`n========== Operation Completed Successfully ==========" -ForegroundColor Green
}
catch {
	Write-Host "`n❌ Error: $_" -ForegroundColor Red
	exit 1
}
