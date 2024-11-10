#include <format>
#include <iostream>

#include "dbus-proxies.hpp"

std::string transferTimestamToReadableString(uint64_t timestamp) {
  std::chrono::system_clock::time_point representedTimePoint =
      std::chrono::system_clock::from_time_t(timestamp);
  auto timeValue = std::chrono::system_clock::to_time_t(representedTimePoint);
  std::tm *preReadableTime = std::localtime(&timeValue);
  char buffer[80];
  std::strftime(buffer, sizeof(buffer), "%F %T", preReadableTime);
  return std::string(buffer);
}

int main(int argc, char *argv[]) {
  DbusPermissionManagerProxy permissionManagerProxy("com.system.permissions",
                                                    "/com/system/permissions");
  DbusTimeServiceProxy timeServiceProxy("com.system.time", "/com/system/time");

  while (true) {
    try {
      uint64_t systemTimeStamp = timeServiceProxy.getSystemTime();
      std::string readableTime =
          transferTimestamToReadableString(systemTimeStamp);
      std::cout << std::format("Current system time: {}", readableTime)
                << std::endl;

      break;
    } catch (const sdbus::Error &e) {
      if (e.getName() == "com.system.time.UnauthorizedAccess") {
        std::cout << "get unauthorized access, trying to get permission.."
                  << std::endl;
        permissionManagerProxy.requestPermission(Permissions::SystemTime);
      } else {
        std::cout
            << std::format(
                   "get error while accessing dbus: Name: {} | Message: {}",
                   e.getName().c_str(), e.getMessage())
            << std::endl;
        break;
      }
    }
  }
}