#include "dbus-time-service.hpp"

int main(int argc, char *argv[]) {
  DbusTimeService timeService("com.system.time", "/com/system/time");
  timeService.start();
}