add_library(hw8_meta  INTERFACE)
add_library(hw8::meta ALIAS hw8_meta)

target_include_directories(hw8_meta
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)