#include "dbus-proxies.hpp"

#include <iostream>

DbusPermissionManagerProxy::DbusPermissionManagerProxy(std::string serviceName,
                                                       std::string objectPath) {
  std::cout << "start initializing permission manager proxy" << std::endl;

  this->serviceName = serviceName;
  sdbus::ServiceName permissionManagerName{serviceName};
  sdbus::ObjectPath permissionManagerObjPath{objectPath};
  auto dbusPrxyConn = sdbus::createSessionBusConnection();
  dbusPrxy = sdbus::createProxy(std::move(dbusPrxyConn), std::move(permissionManagerName),
                                std::move(permissionManagerObjPath));

  std::cout << "permission manager proxy initializing finished" << std::endl;
}

void DbusPermissionManagerProxy::requestPermission(Permissions permission) {
  dbusPrxy->callMethod("RequestPermission")
      .onInterface(serviceName)
      .withArguments(static_cast<int>(permission))
      .dontExpectReply();
}

DbusTimeServiceProxy::DbusTimeServiceProxy(std::string serviceName,
                                           std::string objectPath) {
  std::cout << "start initializing time service proxy" << std::endl;

  this->serviceName = serviceName;
  sdbus::ServiceName timeServiceProxyName{serviceName};
  sdbus::ObjectPath timeServiceObjPath{objectPath};
  auto dbusPrxyConn = sdbus::createSessionBusConnection();
  dbusPrxy = sdbus::createProxy(std::move(dbusPrxyConn) ,std::move(timeServiceProxyName),
                                std::move(timeServiceObjPath));

  std::cout << "time service proxy initializing finished" << std::endl;
}

uint64_t DbusTimeServiceProxy::getSystemTime() {
  uint64_t sysTimestemp;
  dbusPrxy->callMethod("GetSystemTime")
      .onInterface(serviceName)
      .storeResultsTo(sysTimestemp);
  return sysTimestemp;
}