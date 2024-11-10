#include <iostream>

#include "dbus-permission-manager.hpp"
#include "sqlPermissionStorage.hpp"

int main(int argc, char *argv[]) {
  std::unique_ptr<SQLitePermissionStorage> storage(
      new SQLitePermissionStorage("permissions.db"));
  DbusPermissionManager permissionManager(
      "com.system.permissions", "/com/system/permissions", std::move(storage));
  permissionManager.start();
}