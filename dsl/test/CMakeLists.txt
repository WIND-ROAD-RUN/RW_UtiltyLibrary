cmake_minimum_required(VERSION 3.5)

project(dsl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

find_package(GTest CONFIG REQUIRED)
enable_testing()
add_executable(MyTests "test1.cc")

target_link_libraries(MyTests PRIVATE GTest::gtest GTest::gtest_main)

add_test(NAME MyTests COMMAND MyTests)

include(GoogleTest)
gtest_discover_tests(MyTests)