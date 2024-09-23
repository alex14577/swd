add_library(hw4_meta  INTERFACE)
add_library(hw4::meta ALIAS hw4_meta)

target_include_directories(hw4_meta
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)