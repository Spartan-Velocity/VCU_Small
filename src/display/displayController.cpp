#include "display/displayController.hpp"

#include "config.hpp"
#include "elapsedMillis.h"
#include "usb_serial.h"

namespace displayController {

void writeEnd() {
  displayConfig::NEXTION.write(0xFF);
  displayConfig::NEXTION.write(0xFF);
  displayConfig::NEXTION.write(0xFF);
}

void writeVal(const char* obj, int32_t value) {
  displayConfig::NEXTION.print(obj);
  displayConfig::NEXTION.print(".val=");
  displayConfig::NEXTION.print(value);
  writeEnd();
}

void writeTxt(const char* obj, const char* text) {
  displayConfig::NEXTION.print(obj);
  displayConfig::NEXTION.print(".txt=\"");
  displayConfig::NEXTION.print(text);
  displayConfig::NEXTION.print("\"");
  writeEnd();
}

void writeCmd(const char* cmd) {
  displayConfig::NEXTION.print(cmd);
  writeEnd();
}

void init() {
  displayConfig::NEXTION.begin(displayConfig::DISPLAY_BAUD);

  // wait for nextion to connect
  auto timeout = elapsedMillis();

  while (displayConfig::NEXTION.available() != 0) {
    displayConfig::NEXTION.read();
  }
  while (displayConfig::NEXTION.available() != 1 && timeout < displayConfig::DISPLAY_TIMEOUT) {
    writeCmd("connect");
    delay(200);
  }
  while (displayConfig::NEXTION.available() != 0) {
    displayConfig::NEXTION.read();
  }

  if (timeout >= displayConfig::DISPLAY_TIMEOUT) {
    Serial.println("Nextion connected");
  }
}

}  // namespace displayController