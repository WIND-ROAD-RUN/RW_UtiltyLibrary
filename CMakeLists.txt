cmake_minimum_required(VERSION 3.27)

project(RW_UtiltyLibrary VERSION 0.1 LANGUAGES CXX)

# 包含工具链文件
if(DEFINED CMAKE_TOOLCHAIN_FILE)
    include(${CMAKE_TOOLCHAIN_FILE})
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# 设置编译选项以确保使用UTF-8编码
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:GNU>:-finput-charset=UTF-8>")
add_compile_options("$<$<CXX_COMPILER_ID:GNU>:-fexec-charset=UTF-8>")
add_compile_options("$<$<CXX_COMPILER_ID:Clang>:-finput-charset=UTF-8>")
add_compile_options("$<$<CXX_COMPILER_ID:Clang>:-fexec-charset=UTF-8>")

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# 启用 /PROFILE 选项
if (MSVC)
    add_compile_options(/Zi)
    add_link_options(/PROFILE /DEBUG)
endif()

##

##在Windows额外构建
if(${CMAKE_SYSTEM_NAME}  STREQUAL "Windows")
    add_subdirectory(oulq)
endif()

add_subdirectory(cdm) #Common data models
add_subdirectory(oso) 
add_subdirectory(cfgr)
add_subdirectory(dsl)
add_subdirectory(tdp)
