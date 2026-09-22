#include <Arduino.h>
#include "can/canController.hpp"
#include "wheelController/wheelController.hpp"

void setup() {
  Serial.begin(115200);

  canController::init();
  // wheelController::init();
}

void loop() {
  canController::poll();
  // wheelController::poll();
}