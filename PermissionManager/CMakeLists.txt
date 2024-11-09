cmake_minimum_required(VERSION 3.10)
project(DBUS_PERMISSION_MANAGER)

set(CMAKE_CXX_STANDARD 20)

set (PERMISSION_MANAGER_HEADERS
    "dbus-permission-manager.hpp"
)

set (PERMISSION_MANAGER_SRC
    "dbus-permission-manager.cpp"
    "main.cpp"
)

add_executable(com.system.permissions ${PERMISSION_MANAGER_HEADERS} ${PERMISSION_MANAGER_SRC})
