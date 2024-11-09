#include "dbus-time-service.hpp"
#include <iostream>

DbusTimeService::DbusTimeService(std::string serviceName, std::string objectPath) {
    std::cout << "start initilazing time service" << std::endl;

    this->serviceName = serviceName;
    sdbus::ServiceName timeServiceName{serviceName};
    dbusConnection = sdbus::createBusConnection(timeServiceName);
    sdbus::ObjectPath timeServicePath{objectPath};
    dbusObject = sdbus::createObject(*dbusConnection, std::move(timeServicePath));
    registerMethods();
    registerSignals();
    std::cout << "time service initialized" << std::endl;
}

void DbusTimeService::registerMethods() {

}

void DbusTimeService::registerSignals() {

}