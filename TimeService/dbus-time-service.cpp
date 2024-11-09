#include "dbus-time-service.hpp"
#include <iostream>
#include <chrono>

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

bool DbusPermissionManagerProxy::checkApplicationHasPermission(std::string pathToApplication, Permissions permission){
    bool isAppHasPermission = false;
    dbusPrxy->callMethod("CheckApplicationHasPermission")
    .onInterface(serviceName)
    .withArguments(pathToApplication, static_cast<int>(permission))
    .storeResultsTo(isAppHasPermission);
    return isAppHasPermission;
}

uint64_t DbusTimeService::getSystemTime() {
    int dbusClientPid = dbusObject->getCurrentlyProcessedMessage().getCredsPid();
    std::string dbusClientExecPath = getAppExecPathByPid(dbusClientPid);
    if (!permissionManagerProxy->checkApplicationHasPermission(dbusClientExecPath, Permissions::SystemTime)){
        throw sdbus::Error(sdbus::Error::Name{"com.system.time.UnauthorizedAccess"},"Access is denied");
    };

    auto currentTime = std::chrono::system_clock::now();
    uint64_t timestampInSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime.time_since_epoch()).count();

    return timestampInSeconds;
}


std::string DbusTimeService::getAppExecPathByPid(int pid) {
  char path[1024];
  std::snprintf(path, sizeof(path), "/proc/%d/exe", pid);
  ssize_t len = readlink(path, path, sizeof(path));
  return std::string(path, len);
}