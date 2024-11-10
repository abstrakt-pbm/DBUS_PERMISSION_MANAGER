#pragma once
#include <string>
#include <sdbus-c++/sdbus-c++.h>

class DbusPermissionManagerProxy {
    private:
    std::string serviceName;
    std::unique_ptr<sdbus::IProxy> dbusPrxy;

    public:
    DbusPermissionManagerProxy(std::string serviceName, std::string pathToObject);
};