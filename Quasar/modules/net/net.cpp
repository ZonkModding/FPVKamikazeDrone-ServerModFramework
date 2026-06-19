#include "net.h"
#include <windows.h>
#include <wininet.h>
#include <iostream>

#pragma comment(lib, "wininet.lib")

void Modules::Net::SendStats(std::string playerName, int kills, int deaths, int adminLvl) {
    HINTERNET hSession = InternetOpenA("QuasarServerAgent", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hSession) return;

    std::string url = "http://127.0.0.1:3000/update?name=" + playerName +
        "&k=" + std::to_string(kills) +
        "&d=" + std::to_string(deaths) +
        "&a=" + std::to_string(adminLvl);

    HINTERNET hConnect = InternetOpenUrlA(hSession, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hConnect) {
        InternetCloseHandle(hConnect);
    }
    InternetCloseHandle(hSession);
}