#pragma once
#include <sdbus-c++/sdbus-c++.h>

#include <string>

#include "sqlPermissionStorage.hpp"

enum Permissions { SystemTime = 0 };

class DbusPermissionManager {
 private:
  std::unique_ptr<SQLitePermissionStorage> permissionStorage;

  std::string serviceName;
  std::unique_ptr<sdbus::IConnection> dbusConnection;
  std::unique_ptr<sdbus::IObject> dbusObject;
  void registerMethods();
  void registerSignals();

  std::string getAppExecPathByPid(int pid);

 public:
  DbusPermissionManager(
      std::string serviceName, std::string objectPath,
      std::unique_ptr<SQLitePermissionStorage>&& permissonStorage);
  void requestPermission(Permissions permission);
  bool checkApplicationHasPermission(std::string applicationExecPath,
                                     Permissions permission);

  void start();
};