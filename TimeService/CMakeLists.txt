cmake_minimum_required(VERSION 3.10)
project(DBUS_TIME_SERVICE)

set(CMAKE_CXX_STANDARD 20)

set ( TIME_SERVICE_HEADERS 
    "dbus-time-service.hpp"
)

set ( TIME_SERVICE_SRC
    "dbus-time-service.cpp"
    "main.cpp"
)

find_package(sdbus-c++ REQUIRED)

add_executable(com.system.time
    ${TIME_SERVICE_HEADERS}
    ${TIME_SERVICE_SRC}
)

target_link_libraries(com.system.time SDBusCpp::sdbus-c++)