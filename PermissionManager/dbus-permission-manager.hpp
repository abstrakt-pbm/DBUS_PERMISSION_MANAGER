#pragma once
#include <string>
#include <sdbus-c++/sdbus-c++.h>

enum Permissions { SystemTime = 0 };

class DbusPermissionManager {
    private:
    std::string serviceName;
    std::unique_ptr<sdbus::IConnection> dbusConnection;
    std::unique_ptr<sdbus::IObject> dbusObject;
    void registerMethods();
    void registerSignals();

    public:
    DbusPermissionManager(std::string serviceName, std::string objectPath);
}; 