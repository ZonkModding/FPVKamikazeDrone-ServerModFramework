#include "user.h"
#include "../../main.h"
#include "../net/net.h"
#include "../roles/roles.h"
#include "../admin/admin.h"
#include <iostream>
#include <map>

static std::map<void*, std::string> originalNames;
static std::map<void*, std::pair<int, int>> lastStats;

void Modules::User::Update() {
    auto World = SDK::UWorld::GetWorld();
    if (!World || !World->GameState) return;


    auto& PlayerArray = World->GameState->PlayerArray;

    if (PlayerArray.Num() < originalNames.size()) {
        originalNames.clear();
        lastStats.clear();
    }

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        COORD coord = { 0, 0 };
        SetConsoleCursorPosition(hOut, coord);
    }

    std::cout << "[QuasarServer] Players: " << PlayerArray.Num() << "          " << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    for (int i = 0; i < PlayerArray.Num(); ++i) {
        if (!PlayerArray.IsValidIndex(i)) break;

        auto PS = (SDK::ABP_PlayerState_C*)PlayerArray[i];
        if (!PS || !PS->IsA(SDK::ABP_PlayerState_C::StaticClass())) continue;

        void* psAddr = (void*)PS;
        std::string currentInGameName = "";

        if (PS->PlayerNamePrivate.IsValid()) {
            currentInGameName = PS->PlayerNamePrivate.ToString();
        }

        if (originalNames.find(psAddr) == originalNames.end() || currentInGameName.find("[") == std::string::npos) {
            if (!currentInGameName.empty() && currentInGameName.find("[") == std::string::npos) {
                originalNames[psAddr] = currentInGameName;
            }
        }

        std::string baseName = originalNames.count(psAddr) ? originalNames[psAddr] : currentInGameName;

        Modules::Roles::Apply(PS, baseName);

        std::cout << "Player: " << baseName
            << (baseName.length() < 15 ? "\t" : " ")
            << "| K: " << (int)PS->Kills
            << " | D: " << (int)PS->Death << "      " << std::endl;

        int k = (int)PS->Kills;
        int d = (int)PS->Death;
        if (k != lastStats[psAddr].first || d != lastStats[psAddr].second) {
            Net::SendStats(baseName, k, d, (int)PS->AdminLevel);
            lastStats[psAddr] = { k, d };
        }
    }
}