#pragma once
#include "sqlite3.h"
#include <string>

class SQLitePermissionStorage {
private:
    sqlite3* db;
    int initializeTable();
    int initializeDefaultValues();
public:
    SQLitePermissionStorage( std::string dbName );
    int makePermission(std::string permissionName, int permissionEnumCode);
};