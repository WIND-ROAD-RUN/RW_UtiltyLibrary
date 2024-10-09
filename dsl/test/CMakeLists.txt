cmake_minimum_required(VERSION 3.5)

project(dsl_test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

enable_testing()
find_package(GTest CONFIG REQUIRED)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gtest_main)
#set_target_properties(MyTests PROPERTIES EXCLUDE_FROM_ALL true)

#rw库
add_dependencies(${PROJECT_NAME} dsl)
target_link_libraries(${PROJECT_NAME} PRIVATE dsl)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

# GoogleTest integration
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})