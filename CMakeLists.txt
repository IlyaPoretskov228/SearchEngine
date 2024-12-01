cmake_minimum_required(VERSION 3.27)
project(SearchEngine)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/nlohmann_json/include)

set(JSON_BuildTests OFF CACHE INTERNAL "")

set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(source)
add_subdirectory("nlohmann json")

