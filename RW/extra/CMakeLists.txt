project(extra)

find_package(Boost REQUIRED COMPONENTS charconv)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(RTTR REQUIRED)

add_executable(extra main.cpp)

target_link_libraries(extra PRIVATE Boost::charconv Threads::Threads OpenSSL::Crypto OpenSSL::SSL)
target_link_libraries(extra PRIVATE RTTR::Core)