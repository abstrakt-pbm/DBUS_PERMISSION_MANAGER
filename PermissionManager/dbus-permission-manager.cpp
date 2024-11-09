#include "dbus-permission-manager.hpp"
#include <iostream>
#include <format>

DbusPermissionManager::DbusPermissionManager(std::string serviceName, std::string objectPath, std::unique_ptr<SQLitePermissionStorage>&& permissionStoragePtr) : permissionStorage(std::move(permissionStoragePtr)) {
  std::cout << "start initilazing permission service" << std::endl;

  this->serviceName = serviceName;
  sdbus::ServiceName permissionManagerName{serviceName};
  dbusConnection = sdbus::createBusConnection(permissionManagerName);
  sdbus::ObjectPath permissionManagerPath{objectPath};
  dbusObject = sdbus::createObject(*dbusConnection, std::move(permissionManagerPath));
  registerMethods();
  registerSignals();

  std::cout << "permission service initialized" << std::endl;
}

void DbusPermissionManager::registerMethods() {
  dbusObject->addVTable(
    sdbus::registerMethod("CheckApplicationHasPermission")
    .withInputParamNames("applicationExecPath", "permissionEnumCode")
    .withOutputParamNames("isApplicationHasPermission")
    .implementedAs([this](std::string applicationExecPath, int permissionEnumCode) { return this->checkApplicationHasPermission(applicationExecPath, static_cast<Permissions>(permissionEnumCode));})
  ).forInterface(serviceName);
}

void DbusPermissionManager::registerSignals() {

}

bool DbusPermissionManager::checkApplicationHasPermission(std::string applicationExecPath, Permissions permission ) {
  if (applicationExecPath.length() == 0) {
    throw sdbus::Error( sdbus::Error::Name{"com.system.permission.InvalidArgument"}, "Path to application can't be empty");
  }else if (!permissionStorage->isPermissionExists(permission)) {
    throw sdbus::Error( sdbus::Error::Name{"com.system.permission.InvalidArgument"}, "Permission with such enum code not exists");
  }
  return permissionStorage->isApplicationHasPermition(applicationExecPath, permission);
}

void DbusPermissionManager::start() {
  std::cout << "dbus permission manager start handling connections" << std::endl;
  dbusConnection->enterEventLoop();
}

std::string DbusPermissionManager::getAppExecPathByPid(int pid) {
  char path[1024];
  std::snprintf(path, sizeof(path), "/proc/%d/exe", pid);
  ssize_t len = readlink(path, path, sizeof(path));
  return std::string(path, len);
}