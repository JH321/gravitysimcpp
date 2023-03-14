cmake_minimum_required(VERSION 3.12)
project(gravitysim VERSION 0.1.0)


add_subdirectory(src)


include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)



