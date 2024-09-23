add_library(hw5_meta  INTERFACE)
add_library(hw5::meta ALIAS hw5_meta)

target_include_directories(hw5_meta
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)