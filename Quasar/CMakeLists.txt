cmake_minimum_required(VERSION 3.10)
project(QuasarServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(GAME_DIR "C:/SteamLibrary/steamapps/common/FPV Kamikaze Drone Dedicated Server/FPVKamikazeDrone/Binaries/Win64")
set(COMMON_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/modules/net/net.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/modules/roles/roles.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/modules/admin/admin.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/modules/spawnobjects/spawnobjects.cpp"
)

add_library(CommonSources INTERFACE)
target_sources(CommonSources INTERFACE ${COMMON_SOURCES})

add_library(QuasarServer SHARED 
    "main.cpp"
    "modules/user/user.cpp"
    "../dump/CppSDK/SDK/Basic.cpp"
    "../dump/CppSDK/SDK/CoreUObject_functions.cpp"
    "../dump/CppSDK/SDK/Engine_functions.cpp"
    "../dump/CppSDK/SDK/FPVKamikazeDrone_functions.cpp"
    "../libs/minhook/src/hook.c"
    "../libs/minhook/src/buffer.c"
    "../libs/minhook/src/trampoline.c"
    "../libs/minhook/src/hde/hde32.c"
    "../libs/minhook/src/hde/hde64.c"
)

target_link_libraries(QuasarServer PRIVATE CommonSources kernel32 user32 wininet)
target_include_directories(QuasarServer PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}" 
    "../dump/CppSDK" 
    "../libs/minhook/include"
)

set_target_properties(QuasarServer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${GAME_DIR}")
add_library(proxy_version SHARED "proxy/version.cpp")
add_dependencies(proxy_version QuasarServer)

set_target_properties(proxy_version PROPERTIES 
    PREFIX "" 
    SUFFIX ".dll"
    OUTPUT_NAME "version"
    RUNTIME_OUTPUT_DIRECTORY "${GAME_DIR}"
)

target_link_libraries(proxy_version PRIVATE QuasarServer kernel32)