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

    int initDefaultValuesRes = initializeDefaultValues();
    if (initDefaultValuesRes == 1) {
        std::cout << "error while initializing default values" << std::endl;
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

    int reqRes = 0;
    reqRes = sqlite3_step( createPermTablePrepStatemente );
    if (reqRes != SQLITE_DONE) {
        err = 1;
        std::cout << "error while initializing permissions table" << std::endl;
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
        std::cout << "error while create application_permissions table" << std::endl;
    }

    return err;
}

int SQLitePermissionStorage::initializeDefaultValues() {
    int err = 0;


    return err;
}


int SQLitePermissionStorage::makePermission(std::string permissionName, int permissionEnumCode) {
    int err = 0;
    
    std::string mkpermRequest = "INSERT INTO permissions (name, enumCode) VALUES (?1, ?2)";
    sqlite3_stmt* mkPerPrepStatement;
    int rc = sqlite3_prepare_v2(
        db,
        mkpermRequest.c_str(),
        mkpermRequest.length(),
        &mkPerPrepStatement,
        nullptr
    );


    sqlite3_bind_text(mkPerPrepStatement, 1, permissionName.c_str(), -1, SQLITE_TRANSIENT );
    sqlite3_bind_int(mkPerPrepStatement, 2, permissionEnumCode);

    int recRes = 0;
    recRes = sqlite3_step(mkPerPrepStatement);

    if(recRes != SQLITE_DONE) {
        err = 1;
        std::cout << std::format("error while making {}:{} permission", permissionName, permissionEnumCode) << std::endl;
        sqlite3_finalize(mkPerPrepStatement);
    }

    return err;
}

int SQLitePermissionStorage::addPermissionToApplication(std::string pathToApplication, int permissionEnumCode) {
    int err = 0;

    std::string mkAddPermToAppReq = "INSERT INTO application_permissions (pathToExecutable, permissionEnumCode) VALUES (?1, ?2)";
    sqlite3_stmt* mkAddPermToAppPrepStatement;
    
    int rc = sqlite3_prepare_v2(
        db,
        mkAddPermToAppReq.c_str(),
        mkAddPermToAppReq.length(),
        &mkAddPermToAppPrepStatement,
        nullptr
    );

    if ( rc != SQLITE_OK ) {
        std::cout <<"error while making prepare statement: " <<  rc << std::endl;
    }

    sqlite3_bind_text(mkAddPermToAppPrepStatement, 1, pathToApplication.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(mkAddPermToAppPrepStatement, 2, permissionEnumCode);

    int recRes = 0;
    recRes = sqlite3_step(mkAddPermToAppPrepStatement);
    if ( recRes != SQLITE_DONE ) {
        err = 1;
        std::cout << std::format("error while adding permission {} to {} | with code: {}", permissionEnumCode, pathToApplication, recRes) << std::endl;
        sqlite3_finalize(mkAddPermToAppPrepStatement);
    }

    

    return err;
};