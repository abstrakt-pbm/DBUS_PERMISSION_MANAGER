#include "sqlPermissionStorage.hpp"
#include <iostream>
#include <format>

SQLitePermissionStorage::SQLitePermissionStorage( std::string dbName) {
    std::cout << "start initializing database" << std::endl;
    int dbOpenRes = sqlite3_open(dbName.c_str(), &db);
    if ( dbOpenRes != SQLITE_OK ) {
        std::cout << std::format("database with name: {} sucessfully opened", dbName) << std::endl;
    } else {
        std::cout << std::format("Error while opening database: {}", sqlite3_errmsg(db)) << std::endl;
    }

    std::cout << "finishing initializing database" << std::endl;  
}