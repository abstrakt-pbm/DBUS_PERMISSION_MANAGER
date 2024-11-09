#include "sqlPermissionStorage.hpp"
#include <iostream>
#include <format>
#include <sstream>

SQLitePermissionStorage::SQLitePermissionStorage( std::string dbName) {
    std::cout << "start initializing database" << std::endl;
    int dbOpenRes = sqlite3_open(dbName.c_str(), &db);
    if ( dbOpenRes == SQLITE_OK ) {
        std::cout << std::format("database with name: {} sucessfully opened", dbName) << std::endl;
    } else {
        std::cout << std::format("error while opening database: {}", sqlite3_errmsg(db)) << std::endl;
        exit(0);
    }
    int initTableRes = initializeTable();
    if (initTableRes == 1) {
        std::cout << "error while initializing tables" << std::endl;
    }
    std::cout << "finishing initializing database" << std::endl;  
}

int SQLitePermissionStorage::initializeTable() {
    int err = 0;

    std::stringstream createPermissionsTableStatement;
    createPermissionsTableStatement << "CREATE TABLE IF NOT EXISTS permissions (";
    createPermissionsTableStatement << "\"name\" TEXT UNIQUE,";
    createPermissionsTableStatement << "\"enumCode\" INTEGER UNIQUE);";

    sqlite3_stmt* createPermTablePrepStatemente;
    sqlite3_prepare_v2(
        db,
        createPermissionsTableStatement.str().c_str(),
        createPermissionsTableStatement.str().length(),
        &createPermTablePrepStatemente,
        nullptr
    );

    char *err_msg = 0;
    int reqRes = 0;
    reqRes = sqlite3_step( createPermTablePrepStatemente );
    if (reqRes != SQLITE_DONE) {
        err = 1;
        std::cout << "error while initializing permissions table" << std::string(err_msg) << std::endl;
    }
    std::stringstream createApplicationPermissionTableStatement;
    createApplicationPermissionTableStatement << "CREATE TABLE IF NOT EXISTS application_permissions (";
    createApplicationPermissionTableStatement << "\"pathToExecutable\" TEXT NOT NULL UNIQUE,";
    createApplicationPermissionTableStatement << "\"permissionEnumCode\" INTEGER NOT NULL,";
    createApplicationPermissionTableStatement << "FOREIGN KEY(\"permissionEnumCode\") REFERENCES ""\"permissions\"(\"enumCode\"));";

    sqlite3_stmt* createAppPermTablePrepStatemente;
    sqlite3_prepare_v2(
        db,
        createApplicationPermissionTableStatement.str().c_str(),
        createApplicationPermissionTableStatement.str().length(),
        &createAppPermTablePrepStatemente,
        nullptr
    );

    
    reqRes = sqlite3_step( createAppPermTablePrepStatemente );

    if (reqRes != SQLITE_DONE) {
        err = 1;
        std::cout << std::string(err_msg) << std::endl;
    }

    return err;
}