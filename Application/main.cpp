#include "dbus-proxies.hpp"

int main(int argc, char *argv[]) {
   DbusPermissionManagerProxy permissionManagerProxy("com.system.permissions", "/com/system/permissions"); 
   permissionManagerProxy.requestPermission(Permissions::SystemTime);
   sleep(5);
}