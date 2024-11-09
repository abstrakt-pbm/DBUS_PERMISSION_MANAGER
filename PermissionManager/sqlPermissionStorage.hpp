#pragma once
#include "sqlite3.h"
#include <string>

class SQLitePermissionStorage {
private:
    sqlite3* db;
public:
    SQLitePermissionStorage( std::string dbName );
    
};