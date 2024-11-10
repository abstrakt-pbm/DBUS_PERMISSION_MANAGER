#include "dbus-proxies.hpp"
#include <iostream>

DbusPermissionManagerProxy::DbusPermissionManagerProxy(std::string serviceName, std::string objectPath) {
    std::cout << "start initializing permission manager proxy" << std::endl;

    this->serviceName = serviceName;
    sdbus::ServiceName permissionManagerName{serviceName};
    sdbus::ObjectPath permissionManagerObjPath{objectPath};
    dbusPrxy = sdbus::createProxy(std::move(permissionManagerName), std::move(permissionManagerObjPath));
    
    std::cout << "permission manager initializing finished" << std::endl;
}