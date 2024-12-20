cmake_minimum_required(VERSION 3.15...3.29)
project(example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Python解释器和开发组件
find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

# 打印找到的Python版本
message(STATUS "Found Python: ${Python_EXECUTABLE} (version ${Python_VERSION})")

# 使用找到的Python解释器
pybind11_add_module(example main.cpp)
target_link_libraries(example PRIVATE Python::Python)

install(TARGETS example DESTINATION .)