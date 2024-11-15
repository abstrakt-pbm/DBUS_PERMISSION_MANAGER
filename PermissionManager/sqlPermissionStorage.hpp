#pragma once
#include <string>

#include "sqlite3.h"

class SQLitePermissionStorage {
 private:
  sqlite3* db;
  int initializeTable();
  int initializeDefaultValues();

 public:
  SQLitePermissionStorage(std::string dbName);
  int makePermission(std::string permissionName, int permissionEnumCode);
  int addPermissionToApplication(std::string pathToApplication,
                                 int permissionEnumCode);
  bool isApplicationHasPermition(std::string pathToApplication,
                                 int permissionEnumCode);
  bool isPermissionExists(int permissionEnumCode);
};