cmake_minimum_required(VERSION 3.27)

project(sim VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SIM_PRIVATE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/private)

FIND_SOURCES_AND_HEADERS(SRC_LIST
	${CMAKE_CURRENT_SOURCE_DIR}/include 
	${CMAKE_CURRENT_SOURCE_DIR}/src
	${SIM_PRIVATE_PATH}/include
	${SIM_PRIVATE_PATH}/src
)

group_sources_and_headers(
	"Private"
	${SIM_PRIVATE_PATH}/include
	${SIM_PRIVATE_PATH}/src
)

group_interface_sources_and_headers(
	${CMAKE_CURRENT_SOURCE_DIR}/include 
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

message(${SRC_LIST})

add_library(${PROJECT_NAME}  STATIC ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} PUBLIC oso)

target_include_directories(${PROJECT_NAME} 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/private/include
)

add_subdirectory(./test)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${PROJECT_NAME}/include/)
install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION ${PROJECT_NAME}/lib/)



