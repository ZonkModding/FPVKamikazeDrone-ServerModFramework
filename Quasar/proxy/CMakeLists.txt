add_library(proxy_version SHARED "proxy/version.cpp")

set_target_properties(proxy_version PROPERTIES 
    PREFIX "" 
    SUFFIX ".dll"
    OUTPUT_NAME "version"
    RUNTIME_OUTPUT_DIRECTORY "${GAME_DIR}"
)

target_link_libraries(proxy_version PRIVATE kernel32)