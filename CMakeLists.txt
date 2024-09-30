cmake_minimum_required(VERSION 3.5)

project(RW_UtiltyLibrary VERSION 0.1 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_subdirectory(oso)