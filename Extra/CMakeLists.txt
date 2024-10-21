cmake_minimum_required(VERSION 3.27)

project(Extra VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")


add_executable(Extra main.cpp)

target_link_libraries(Extra PRIVATE oso)
target_include_directories(Extra PRIVATE ${CMAKE_SOURCE_DIR}/oso/include)

