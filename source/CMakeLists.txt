cmake_minimum_required(VERSION 3.27)

add_executable(SearchEngine main.cpp ConverterJSON.cpp ${MY_INCLUDE_DIR}/ConverterJSON.h
        ${MY_INCLUDE_DIR}/InvertedIndex.h
        InvertedIndex.cpp
        ../include/SearchServer.h
        SearchServer.cpp
)
target_include_directories(SearchEngine PUBLIC ${MY_INCLUDE_DIR})