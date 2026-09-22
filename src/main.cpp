#include <Arduino.h>
#include "can/canController.hpp"

void setup() {
  canController::initCANBus();
}

void loop() {
  canController::pollCANBus();
}