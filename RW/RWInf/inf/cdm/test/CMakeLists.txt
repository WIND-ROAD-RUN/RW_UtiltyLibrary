cmake_minimum_required(VERSION 3.27)

project(cdm_test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()
find_package(GTest CONFIG REQUIRED)


FIND_SOURCES_AND_HEADERS(SRC_LIST
	${CMAKE_CURRENT_SOURCE_DIR}/include 
	${CMAKE_CURRENT_SOURCE_DIR}/src
)

# google test library
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME}  PRIVATE GTest::gtest GTest::gtest_main)

##test library
target_link_libraries(${PROJECT_NAME} 
	PRIVATE cdm
	PRIVATE oso
)
target_include_directories(${PROJECT_NAME} 
	PRIVATE ${CDM_PRIVATE_PATH}/include
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})


target_precompile_headers(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h)