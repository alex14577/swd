add_library(hw7_meta  INTERFACE)
add_library(hw7::meta ALIAS hw7_meta)

target_include_directories(hw7_meta
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)