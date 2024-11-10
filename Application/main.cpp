#include "dbus-proxies.hpp"
#include <iostream>
int main(int argc, char *argv[]) {
   DbusPermissionManagerProxy permissionManagerProxy("com.system.permissions", "/com/system/permissions");
   DbusTimeServiceProxy timeServiceProxy("com.system.time", "/com/system/time");
}