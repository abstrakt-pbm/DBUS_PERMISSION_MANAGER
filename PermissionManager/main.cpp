#include "dbus-permission-manager.hpp"
#include "sqlPermissionStorage.hpp"
int main (int argc, char *argv[]) {
    SQLitePermissionStorage storage("permissions.db");
    //storage.makePermission("Camera", 1);
    storage.addPermissionToApplication("/usr/bin/gus", 0);
}