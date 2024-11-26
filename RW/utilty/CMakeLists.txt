cmake_minimum_required(VERSION 3.27)

project(utilty VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(utilty_PRIVATE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/private)

set(SRC_LIST)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

set(SRC_PRIVATE_LIST)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST} ${SRC_PRIVATE_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(test)





