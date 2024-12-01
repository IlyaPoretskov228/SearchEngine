cmake_minimum_required(VERSION 3.27)

add_executable(SearchEngine main.cpp ConverterJSON.cpp ${MY_INCLUDE_DIR}/ConverterJSON.h
        ${MY_INCLUDE_DIR}/InvertedIndex.h
        InvertedIndex.cpp
        ../include/SearchServer.h
        SearchServer.cpp
)
target_include_directories(SearchEngine PUBLIC ${MY_INCLUDE_DIR})

target_link_libraries(SearchEngine PUBLIC nlohmann_json::nlohmann_json)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

target_link_libraries(SearchEngine PUBLIC gtest_main)
include(GoogleTest)
gtest_discover_tests(SearchEngine)