add_library(cms_meta  INTERFACE)
add_library(cms::meta ALIAS cms_meta)

target_include_directories(cms_meta
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)