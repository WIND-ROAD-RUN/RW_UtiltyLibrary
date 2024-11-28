cmake_minimum_required(VERSION 3.27)

project(cdm VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CDM_PRIVATE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/private)

FIND_SOURCES_AND_HEADERS(SRC_LIST
	${CMAKE_CURRENT_SOURCE_DIR}/include 
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${CDM_PRIVATE_PATH}/include
	${CDM_PRIVATE_PATH}/src
)

add_library(${PROJECT_NAME}  STATIC ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/private/include)

target_link_libraries(${PROJECT_NAME} PRIVATE oso)

add_subdirectory(./test)



