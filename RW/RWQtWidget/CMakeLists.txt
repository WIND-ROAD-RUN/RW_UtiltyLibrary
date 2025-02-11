cmake_minimum_required(VERSION 3.27)

project(RWQtWidget VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(RWQtWidget_PRIVATE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/private)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(RWQtWidget main.cpp)

target_link_libraries(RWQtWidget PRIVATE Qt6::Core Qt6::Widgets)