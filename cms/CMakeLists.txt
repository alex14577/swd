include(cms.cmake)

set(LIBS_PATH ${CMAKE_SOURCE_DIR}/build/libs)

make_directory(${LIBS_PATH})

add_subdirectory(command)
add_subdirectory(loader)
add_subdirectory(modules)
add_subdirectory(service)
add_subdirectory(worker)
add_subdirectory(transport)

add_subdirectory(test)


