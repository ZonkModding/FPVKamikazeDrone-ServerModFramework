#include "roles.h"
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

std::map<std::string, Modules::UserConfig> Modules::Roles::userConfigs = {
    {"Zear", {3, "[DEV]", 2}}
};

static std::map<void*, std::vector<wchar_t>> persistentBuffers;

void Modules::Roles::Apply(SDK::ABP_PlayerState_C* PS, std::string name) {
    Sleep(5000);

    if (!PS || !PS->PlayerNamePrivate.IsValid()) return;

    auto it = userConfigs.find(name);
    if (it == userConfigs.end()) return;

    auto& config = it->second;

    if ((unsigned char)PS->AdminLevel != (unsigned char)config.level) {
        PS->AdminLevel = static_cast<SDK::EAdminLevel>(config.level);
    }

    std::string spaces(config.spaces * 2, ' ');
    std::string fullNick = config.prefix + spaces + name;

    if (PS->PlayerNamePrivate.ToString() != fullNick) {
        int wlen = MultiByteToWideChar(CP_UTF8, 0, fullNick.c_str(), -1, NULL, 0);
        if (wlen > 0) {
            auto& buffer = persistentBuffers[PS];
            buffer.assign(wlen, 0);
            MultiByteToWideChar(CP_UTF8, 0, fullNick.c_str(), -1, buffer.data(), wlen);

            SDK::FString newFString(buffer.data());
            PS->PlayerNamePrivate = newFString;
        }
    }
}