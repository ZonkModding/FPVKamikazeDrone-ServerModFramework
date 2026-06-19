#pragma once
#include <string>
#include <map>
#include "../../../dump/CppSDK/SDK.hpp"

namespace Modules {
    struct UserConfig {
        int level;
        std::string prefix;
        int spaces;
    };

    class Roles {
    private:
        static std::map<std::string, UserConfig> userConfigs;
    public:
        static void Apply(SDK::ABP_PlayerState_C* PS, std::string name);
    };
}