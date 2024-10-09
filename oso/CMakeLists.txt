cmake_minimum_required(VERSION 3.5)

project(oso VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

find_package(pugixml CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME}  STATIC ${SRC_LIST})
target_link_libraries(${PROJECT_NAME}  PRIVATE pugixml::pugixml)
target_link_libraries(${PROJECT_NAME}   PRIVATE JsonCpp::JsonCpp)

add_subdirectory(./test)



