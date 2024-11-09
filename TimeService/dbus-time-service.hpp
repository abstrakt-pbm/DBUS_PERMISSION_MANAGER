#pragma once
#include <string>
#include <cstdint>
#include <sdbus-c++/sdbus-c++.h>

enum Permissions {
    SystemTime = 0
};

class DbusTimeService {
    private:
    std::string serviceName;
    std::unique_ptr<sdbus::IConnection> dbusConnection;
    std::unique_ptr<sdbus::IObject> dbusObject;

    void registerMethods();
    void registerSignals();

    public:
    DbusTimeService(std::string serviceName, std::string objectPath);
    uint64_t getSystemTime(); 
};
