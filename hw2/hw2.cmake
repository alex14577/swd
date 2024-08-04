add_library(movement_meta  INTERFACE)
add_library(movement::meta ALIAS movement_meta)

target_include_directories(movement_meta
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)