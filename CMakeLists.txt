cmake_minimum_required(VERSION 3.0.0)
project(hello_cmake VERSION 0.1.0)

add_executable(analytical_tool.out fulcrum_analytical_tool.cpp)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(json)

target_link_libraries(analytical_tool.out nlohmann_json)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
