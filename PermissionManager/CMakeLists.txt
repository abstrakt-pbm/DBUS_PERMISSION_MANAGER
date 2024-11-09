cmake_minimum_required(VERSION 3.10)
project(DBUS_PERMISSION_MANAGER)

set(CMAKE_CXX_STANDARD 20)

set (PERMISSION_MANAGER_HEADERS
    "dbus-permission-manager.hpp"
    "sqlPermissionStorage.hpp"
)

set (PERMISSION_MANAGER_SRC
    "dbus-permission-manager.cpp"
    "sqlPermissionStorage.cpp"
    "main.cpp"
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/dependencies/sqlite3)
find_package(sdbus-c++ REQUIRED)

add_executable(com.system.permissions 
    ${PERMISSION_MANAGER_HEADERS} 
    ${PERMISSION_MANAGER_SRC}
)

target_link_libraries(com.system.permissions 
    SDBusCpp::sdbus-c++
    sqlite3
)