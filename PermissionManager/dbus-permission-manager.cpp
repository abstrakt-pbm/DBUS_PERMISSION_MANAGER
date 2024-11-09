#include "dbus-permission-manager.hpp"
#include <iostream>

DbusPermissionManager::DbusPermissionManager(std::string serviceName, std::string objectPath) {
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
}

void DbusPermissionManager::registerSignals() {

}
