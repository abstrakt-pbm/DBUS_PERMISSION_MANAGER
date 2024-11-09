#include "dbus-permission-manager.hpp"
#include "sqlPermissionStorage.hpp"
#include <iostream>
int main (int argc, char *argv[]) {
    SQLitePermissionStorage storage("permissions.db");
}