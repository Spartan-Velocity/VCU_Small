#include <Arduino.h>
#include "can/canController.hpp"
#include "wheelController/wheelController.hpp"

void setup() {
  canController::initCANBus();
  wheelController::initWheelController();
}

void loop() {
  canController::pollCANBus();
  wheelController::pollWheelController();
}