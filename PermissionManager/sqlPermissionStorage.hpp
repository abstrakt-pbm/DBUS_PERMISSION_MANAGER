#pragma once
#include "sqlite3.h"
#include <string>

class SQLitePermissionStorage {
private:
    sqlite3* db;
    int initializeTable();
public:
    SQLitePermissionStorage( std::string dbName );

};