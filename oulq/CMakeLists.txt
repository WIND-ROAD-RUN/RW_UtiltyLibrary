cmake_minimum_required(VERSION 3.5)

project(oulq VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/Zc:__cplusplus)
    add_compile_options(/Zc:__cplusplus /permissive-)
endif()

list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "ui")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

file(GLOB UI_FILES "io/*.ui")
qt_wrap_ui(UIS_HDRS ${UI_FILES})

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include UIS_HDRS  UI_FILES)

add_library(${PROJECT_NAME}  STATIC ${SRC_LIST} ${UI_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)




