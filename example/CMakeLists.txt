cmake_minimum_required(VERSION 3.27)

project(demo VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE CXX_STANDARD 17)
set(CMAKE CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)

FIND_SOURCES_AND_HEADERS(SRC_LIST
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_executable(${PROJECT_NAME}  ${SRC_LIST} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE hoec)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE "C:/Users/14328/Desktop/RW_UnityLibrary/RW_UtiltyLibrary/RW/hoe/hoec/private/include")