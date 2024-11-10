cmake_minimum_required(VERSION 3.10)
project(APPLICATION)

set(CMAKE_CXX_STANDARD 20)

set( APPLICATION_HEADERS
    "dbus-proxies.hpp"
)

set ( APPLICATION_SRC
    "dbus-proxies.cpp"
    "main.cpp"
)

find_package(sdbus-c++ REQUIRED)

add_executable( application 
    ${APPLICATION_HEADERS}
    ${APPLICATION_SRC}
)

target_link_libraries( application
    SDBusCpp::sdbus-c++
)