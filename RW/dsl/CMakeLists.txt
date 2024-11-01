cmake_minimum_required(VERSION 3.27)

project(dsl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

message(${CMAKE_CURRENT_SOURCE_DIR})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src source_file)

add_library(${PROJECT_NAME} STATIC ${source_file} )
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(./test)
