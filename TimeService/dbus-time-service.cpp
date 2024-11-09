#include "dbus-time-service.hpp"
#include <iostream>

DbusTimeService::DbusTimeService(std::string serviceName, std::string objectPath) {
    std::cout << "start initilazing time service" << std::endl;

    this->serviceName = serviceName;
    sdbus::ServiceName timeServiceName{serviceName};
    dbusConnection = sdbus::createBusConnection(timeServiceName);
    sdbus::ObjectPath timeServicePath{objectPath};
    dbusObject = sdbus::createObject(*dbusConnection, std::move(timeServicePath));
    permissionManagerProxy = std::unique_ptr<DbusPermissionManagerProxy>{new DbusPermissionManagerProxy("com.system.permissions", "/com/system/permissions")};
    registerMethods();

    std::cout << "time service initialized" << std::endl;
}

void DbusTimeService::registerMethods() {

}

DbusPermissionManagerProxy::DbusPermissionManagerProxy(std::string serviceName, std::string pathToObject) {
    std::cout << "start initilazing dbus permission manager proxy" << std::endl;

    this->serviceName = serviceName;
    sdbus::ServiceName permissionManagerProxy{serviceName};
    sdbus::ObjectPath objPath{pathToObject};
    dbusPrxy = sdbus::createProxy(std::move(permissionManagerProxy), std::move(objPath));

    std::cout << "dbus permission proxy initialized" << std::endl;
}
