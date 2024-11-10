cmake_minimum_required(VERSION 3.20)

project(DBUS_TEST_TASK)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/PermissionManager)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/TimeService)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Application)

add_custom_target(DBUS_TEST_TASK)
add_dependencies(DBUS_TEST_TASK com.system.permissions com.system.time application)

