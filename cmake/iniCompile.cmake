message(STATUS "Setting compiler")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/utf-8 /MP)

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(/ZI /RTC1)
        add_link_options(/INCREMENTAL)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(/O2) # 优化代码
        add_link_options(/PROFILE /DEBUG)
    endif()

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
    add_compile_options(-j) # 启用多线程编译
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)
    add_compile_options(-j) # 启用多线程编译
endif()


# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()