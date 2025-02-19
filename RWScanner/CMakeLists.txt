cmake_minimum_required(VERSION 3.27)

project(RWScanner VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(RWQtWidget_PRIVATE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/private)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

add_executable(demo src/main.cpp)




