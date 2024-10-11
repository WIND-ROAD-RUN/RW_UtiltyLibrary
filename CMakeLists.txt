cmake_minimum_required(VERSION 3.5)

project(RW_UtiltyLibrary VERSION 0.1 LANGUAGES CXX)

# 包含工具链文件
if(DEFINED CMAKE_TOOLCHAIN_FILE)
    include(${CMAKE_TOOLCHAIN_FILE})
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# 启用 /PROFILE 选项
if (MSVC)
    add_compile_options(/Zi)
    add_link_options(/PROFILE /DEBUG)
endif()

##
add_subdirectory(oso)
add_subdirectory(Extra)
add_subdirectory(cfgr)
add_subdirectory(oulq)
add_subdirectory(dsl)
