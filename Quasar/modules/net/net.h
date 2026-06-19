#pragma once
#include <string>

namespace Modules {
    class Net {
    public:
        static void SendStats(std::string playerName, int kills, int deaths, int adminLvl);
    };
}