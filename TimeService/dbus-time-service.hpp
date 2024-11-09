#pragma once
#include <string>
#include <cstdint>
#include <sdbus-c++/sdbus-c++.h>

enum Permissions {
    SystemTime = 0
};

class DbusPermissionManagerProxy {
    private:
    std::string serviceName;
    std::unique_ptr<sdbus::IProxy> dbusPrxy;

    public:
    DbusPermissionManagerProxy(std::string serviceName, std::string objectPath);
    bool checkApplicationHasPermission(std::string pathToApplication, Permissions permission);
};

class DbusTimeService {
    private:
    std::string serviceName;
    std::unique_ptr<sdbus::IConnection> dbusConnection;
    std::unique_ptr<sdbus::IObject> dbusObject;

    std::unique_ptr<DbusPermissionManagerProxy> permissionManagerProxy;

    void registerMethods();

    std::string getAppExecPathByPid(int pid);

    public:
    DbusTimeService(std::string serviceName, std::string objectPath);
    uint64_t getSystemTime(); 
    void start();
};

