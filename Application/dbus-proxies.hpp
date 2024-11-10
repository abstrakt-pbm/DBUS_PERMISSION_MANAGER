#pragma once
#include <sdbus-c++/sdbus-c++.h>

#include <string>

enum Permissions { SystemTime = 0 };

class DbusPermissionManagerProxy {
 private:
  std::string serviceName;
  std::unique_ptr<sdbus::IProxy> dbusPrxy;

 public:
  DbusPermissionManagerProxy(std::string serviceName, std::string pathToObject);
  void requestPermission(Permissions permission);
};

class DbusTimeServiceProxy {
 private:
  std::string serviceName;
  std::unique_ptr<sdbus::IProxy> dbusPrxy;

 public:
  DbusTimeServiceProxy(std::string serviceName, std::string pathToObject);
  uint64_t getSystemTime();
};