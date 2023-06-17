cmake_minimum_required(VERSION 3.12)
project(gravitysim VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(SFML 2.5 REQUIRED graphics window system)
include_directories(${SFML_INCLUDE_DIR})

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)



