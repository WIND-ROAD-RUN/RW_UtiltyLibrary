cmake_minimum_required(VERSION 3.27)

project(dsl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FIND_SOURCES_AND_HEADERS(SRC_LIST
	${CMAKE_CURRENT_SOURCE_DIR}/include 
	${CMAKE_CURRENT_SOURCE_DIR}/include/Cache
	${CMAKE_CURRENT_SOURCE_DIR}/include/DataStructure
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/src/Cache
	${CMAKE_CURRENT_SOURCE_DIR}/include/DataStructure
)

group_interface_sources_and_headers(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/include/Cache
	${CMAKE_CURRENT_SOURCE_DIR}/include/DataStructure
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CMAKE_CURRENT_SOURCE_DIR}/src/Cache
	${CMAKE_CURRENT_SOURCE_DIR}/src/DataStructure
)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST} )
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC include/Cache)
target_include_directories(${PROJECT_NAME} PUBLIC include/DataStructure)

add_subdirectory(./test)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${PROJECT_NAME}/include/)
install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION ${PROJECT_NAME}/lib/)