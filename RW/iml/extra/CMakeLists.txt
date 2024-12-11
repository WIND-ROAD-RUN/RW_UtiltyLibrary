project(demo)

find_package(OpenVINO REQUIRED)
add_executable(demo main.cpp)
target_link_libraries(demo PRIVATE openvino::runtime)