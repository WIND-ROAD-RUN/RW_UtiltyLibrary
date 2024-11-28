cmake_minimum_required(VERSION 3.27)

project(tdp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(pugixml CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

set(TDP_PRIVATE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/private)

FIND_SOURCES_AND_HEADERS(SRC_LIST
	${CMAKE_CURRENT_SOURCE_DIR}/include 
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${TDP_PRIVATE_PATH}/include
	${TDP_PRIVATE_PATH}/src
)
add_library(${PROJECT_NAME}  STATIC ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} 
	PRIVATE cdm
	PUBLIC oso
)
target_include_directories(${PROJECT_NAME} 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/private/include
)

add_subdirectory(./test)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)



