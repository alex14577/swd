add_library(hw3_meta  INTERFACE)
add_library(hw3::meta ALIAS hw3_meta)

target_include_directories(hw3_meta
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)