#include "console.h"

void CreateConsole() {
	if (AllocConsole()) {
		FILE* f;
		freopen_s(&f, "CONOUT$", "w", stdout);
		freopen_s(&f, "CONIN$", "r", stdin);
		SetConsoleTitleA("Quasar Debug Console");
	}
}

void CloseConsole() {
	FreeConsole();
}