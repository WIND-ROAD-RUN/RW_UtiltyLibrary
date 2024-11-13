cmake_minimum_required(VERSION 3.27)

project(RW_UtiltyLibrary VERSION 0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)# 生成编译命令

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(iniEnvironmet) # 初始化环境变量
include(iniSubModule)  # 初始化子模块
include(iniCompile)    # 初始化编译选项

# 包含工具链文件
if(DEFINED CMAKE_TOOLCHAIN_FILE)
    include(${CMAKE_TOOLCHAIN_FILE})
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(RW)
add_subdirectory(ThirdLibrary)