#include "dbus-proxies.hpp"

int main(int argc, char *argv[]) {
   DbusPermissionManagerProxy permissionManagerProxy("com.system.permissions", "/com/system/permissions");
   DbusTimeServiceProxy timeServiceProxy("com.system.time", "/com/system/time");
   
   permissionManagerProxy.requestPermission(Permissions::SystemTime);
   sleep(5);
}